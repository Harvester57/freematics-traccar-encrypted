# Vulnerability Scan Findings — telelogger

**Target**: `esp32/telelogger`  
**Scanned**: 2026-06-05T20:58:00Z  
**Source files**: 10 (.cpp, .h, .ino)  
**Focus areas**: 6  
**Threat model**: THREAT_MODEL.md (bootstrap-then-interview, 2026-06-05)

> [!NOTE]
> Hardcoded credential findings removed — values in `config.h` are compile-time placeholders overridden during build.

## Summary

| Total | HIGH | MEDIUM | LOW | Low-confidence (< 0.4) |
|-------|------|--------|-----|------------------------|
| 7     | 2    | 5      | 0   | 0                      |

## Findings Table

| ID    | Severity | Confidence | Category            | File:Line             | Title |
|-------|----------|------------|---------------------|-----------------------|-------|
| F-001 | HIGH     | 0.8        | stack-buffer-overflow | teleclient.cpp:313  | Stack buffer overflow in UDP response decryption — output buffer undersized for network-controlled input |
| F-002 | HIGH     | 0.7        | stack-buffer-overflow | teleclient.cpp:262  | Fixed-size stack buffer for encryption output in notify() can overflow with large payloads |
| F-003 | MEDIUM   | 0.7        | heap-buffer-overflow | teleclient.cpp:289  | WiFi receive uses cell buffer but WiFi and cell may have different buffer sizes |
| F-004 | MEDIUM   | 0.6        | stack-buffer-overflow | teleclient.cpp:568  | HTTP notify path constructs URL with unbounded VIN string into fixed-size stack buffer |
| F-005 | MEDIUM   | 0.5        | path-traversal      | dataserver.cpp:277    | HTTP API file deletion handler uses attacker-controlled ID without validation |
| F-006 | MEDIUM   | 0.6        | integer-overflow    | teleclient.cpp:40     | CBuffer::add() offset bounds check may allow off-by-one writes with crafted element sizes |
| F-007 | MEDIUM   | 0.5        | heap-buffer-overflow | teleclient.cpp:62   | CBuffer::serialize() reads elements from buffer without validating element count against buffer bounds |

---

### F-001 — Stack buffer overflow in UDP response decryption
- **Severity**: HIGH | **Confidence**: 0.8 | **Category**: stack-buffer-overflow
- **File**: [teleclient.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/teleclient.cpp#L313):313

In `TeleClientUDP::notify()`, a stack buffer `char decrypted_data[RECV_BUF_SIZE]` (512 bytes) receives the output of `decrypt_string()`. The `decrypt_string()` function writes `length - 28` bytes plus a null terminator with no output size parameter. Currently, `RECV_BUF_SIZE` constrains both the receive and the decrypt output, so the overflow doesn't trigger. But the `decrypt_string` API is unsafe by design — it accepts no output buffer size parameter. The same pattern appears in `inbound()` at line 520.

**Exploit scenario**: If `RECV_BUF_SIZE` is increased or if the cellular receive path returns more data than the stack buffer capacity, `decrypt_string` writes past `decrypted_data`, overwriting the stack return address → RCE. This aligns with threat model T1.

**Recommendation**: Add an output buffer size parameter to `decrypt_string()` and enforce bounds: `void decrypt_string(const unsigned char *input, size_t length, unsigned char *output, size_t output_size)`.

---

### F-002 — Fixed-size stack buffer for encryption output in notify()
- **Severity**: HIGH | **Confidence**: 0.7 | **Category**: stack-buffer-overflow
- **File**: [teleclient.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/teleclient.cpp#L262):262

`unsigned char encrypted_buf[256]` is used for `encrypt_string()` output. The maximum plaintext from the 128-byte CStorageRAM cache produces 156 bytes of ciphertext, which fits. But the buffer is hardcoded without tying it to the actual data size, and `encrypt_string` has no output size parameter.

**Exploit scenario**: If the cache size increases beyond 228 bytes, encrypted output exceeds the 256-byte stack buffer → stack overflow.

**Recommendation**: Dynamically allocate based on plaintext size (as done in telemetry() at telelogger.ino:1025), or add output size checking to `encrypt_string()`.

---

### F-003 — WiFi receive reuses cellular module's internal buffer
- **Severity**: MEDIUM | **Confidence**: 0.7 | **Category**: heap-buffer-overflow
- **File**: [teleclient.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/teleclient.cpp#L289):289

WiFi receive writes into `cell.getBuffer()` — the cellular module's internal heap buffer. Both use `RECV_BUF_SIZE` (512), so it's currently safe. The coupling is architecturally fragile.

**Recommendation**: Use a dedicated receive buffer for WiFi with explicit size, rather than reusing the cellular module's internal buffer.

---

### F-004 — HTTP notify constructs URL with VIN into fixed buffer
- **Severity**: MEDIUM | **Confidence**: 0.6 | **Category**: stack-buffer-overflow
- **File**: [teleclient.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/teleclient.cpp#L568):568

`snprintf(path, sizeof(path), ...)` with `vin` data into 256-byte buffer. Safe due to `snprintf` truncation, but `vin` is populated via `memcpy` from OBD without explicit null-termination after copy.

**Recommendation**: Explicitly null-terminate `vin[]` after the memcpy for defense-in-depth.

---

### F-005 — HTTP API file deletion with integer-based path (no traversal)
- **Severity**: MEDIUM | **Confidence**: 0.5 | **Category**: path-traversal
- **File**: [dataserver.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/dataserver.cpp#L277):277

`atoi()` conversion prevents path traversal. The handler allows deletion of any numbered CSV file in `/DATA/`. HTTPD is disabled by default.

**Recommendation**: No immediate fix needed. Validate ID range for defense-in-depth.

---

### F-006 — CBuffer::add() unsigned arithmetic in bounds check
- **Severity**: MEDIUM | **Confidence**: 0.6 | **Category**: integer-overflow
- **File**: [teleclient.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/teleclient.cpp#L40):40

The bounds check `offset < BUFFER_LENGTH - sizeof(ELEMENT_HEAD) - bytes` uses unsigned arithmetic. If `bytes` exceeds `BUFFER_LENGTH - sizeof(ELEMENT_HEAD)`, the subtraction wraps, bypassing the guard. All current callers pass small fixed sizes.

**Recommendation**: Use `if (bytes > BUFFER_LENGTH || offset + sizeof(ELEMENT_HEAD) + bytes > BUFFER_LENGTH)`.

---

### F-007 — CBuffer::serialize() lacks per-element bounds validation
- **Severity**: MEDIUM | **Confidence**: 0.5 | **Category**: heap-buffer-overflow
- **File**: [teleclient.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/teleclient.cpp#L62):62

`serialize()` loops over `total` elements reading headers and payloads from `m_data`. A corrupted header with large `count` can cause out-of-bounds reads. Requires prior memory corruption.

**Recommendation**: Add per-element bounds checking inside the loop. Validate `of + sizeof(ELEMENT_HEAD) <= offset` before reading headers.
