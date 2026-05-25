# Security Analysis: ChaCha20-Poly1305 Implementation

> [!NOTE]
> **Scope**: ESP32 crypto library (`esp32/libraries/crypto/`), caller code (`telecrypt.cpp`), and Go server (`server/src/encryption/`).
> **Standard**: [RFC 8439](https://tools.ietf.org/html/rfc8439) (ChaCha20-Poly1305 AEAD).
> **Library provenance**: The C++ code is from [Southern Storm Software's arduinolibs](https://github.com/rweather/arduinolibs) (© 2015), an established embedded crypto library.

---

## Executive Summary

| Severity | Count | Categories |
|----------|-------|------------|
| 🔴 **CRITICAL** | 3 | Decrypted data used before authentication; Encryption fallback bypasses all security; Key in config sample |
| 🟠 **HIGH** | 3 | Key not scrubbed after parsing; Potential `checkTag()` crash worked around; `dataSize` overflow |
| 🟡 **MEDIUM** | 3 | No nonce-reuse protection; No AAD usage; `setKey()` accepts weak key sizes |
| 🟢 **LOW / INFO** | 4 | Draft RFC reference; `clean()` guarantees; Server key validation; Test files with hardcoded keys |

---

## 1. Algorithmic Correctness of the Core Library

### 1.1 ChaCha20 Stream Cipher — [ChaCha.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaCha.cpp)

| Aspect | Assessment |
|--------|------------|
| **Quarter-round** (L226-239) | ✅ Correct — rotations 16, 12, 8, 7 match RFC 8439 §2.1 |
| **hashCore** (L253-281) | ✅ Correct — column rounds + diagonal rounds, final addition of input |
| **Counter increment** (L166-177) | ✅ Constant-time 8-byte counter increment (timing-safe) |
| **96-bit nonce support** (L121-125) | ✅ Correct — places 4 zero bytes as the counter, nonce in bytes 52-63 |
| **Rounds** | ✅ Default 20 rounds (RFC 8439 standard) |
| **Key expansion** (L87-109) | ✅ Correct use of "expand 32-byte k" / "expand 16-byte k" constants |

> [!TIP]
> The ChaCha20 core implementation is algorithmically sound and follows the reference specification faithfully.

### 1.2 Poly1305 MAC — [Poly1305.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/Poly1305.cpp)

| Aspect | Assessment |
|--------|------------|
| **Key clamping** ([L116-124](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/Poly1305.cpp#L116-L124)) | ✅ Correct — `r[3] &= 0x0F, r[4] &= 0xFC, ...` matches RFC 8439 §2.5 clamping |
| **Modular reduction** ([L317-339](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/Poly1305.cpp#L317-L339)) | ✅ Correct — reduces mod 2^130-5 via multiply-high-by-5 technique |
| **Final reduction** ([L198-232](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/Poly1305.cpp#L198-L232)) | ✅ Constant-time conditional subtraction via bitmask (no branches on secret data) |
| **Tag finalization** ([L234-246](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/Poly1305.cpp#L234-L246)) | ✅ Correct — adds encrypted nonce to hash value |

### 1.3 ChaChaPoly AEAD Construction — [ChaChaPoly.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaChaPoly.cpp)

| Aspect | Assessment |
|--------|------------|
| **Poly1305 key derivation** ([L91-95](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaChaPoly.cpp#L91-L95)) | ✅ Correct — first keystream block used for Poly1305 key (32 bytes from `data[0..7]`), nonce from `data[4..7]` |
| **Encrypt-then-MAC** ([L105-114](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaChaPoly.cpp#L105-L114)) | ✅ Correct — encrypts first, then feeds ciphertext to Poly1305 |
| **Decrypt order** ([L116-125](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaChaPoly.cpp#L116-L125)) | ✅ Correct — feeds ciphertext to Poly1305 before decrypting |
| **Tag computation** ([L135-148](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaChaPoly.cpp#L135-L148)) | ✅ Correct — pads, appends `le64(AAD_len) || le64(ciphertext_len)`, finalizes |
| **Tag verification** ([L150-162](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaChaPoly.cpp#L150-L162)) | ✅ Uses `secure_compare()` — constant-time comparison |

---

## 2. Critical Findings

### 🔴 CRITICAL-1: Decrypted Data Used Before Authentication Verified

**Location**: [telecrypt.cpp:67-77](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telecrypt.cpp#L67-L77)

```cpp
// Line 67: Decrypt FIRST
chachaPoly.decrypt(output, input + sizeof(nonce), decryptedLength);

// Line 75-77: Verify tag AFTER
const unsigned char *tagPtr = input + sizeof(nonce) + decryptedLength;
uint8_t computedTag[16];
chachaPoly.computeTag(computedTag, sizeof(computedTag));
```

> [!CAUTION]
> **The decrypted plaintext is written to the `output` buffer before the authentication tag is verified.** This is a textbook violation of the AEAD contract. If authentication fails (line 106-109), the output buffer is only NUL-terminated (`output[0] = '\0'`), but the remaining decrypted bytes remain in memory and may have already been read by a concurrent process or DMA.
>
> **Impact**: An attacker who can tamper with ciphertext can cause the ESP32 to process forged/manipulated plaintext. This is especially dangerous because the plaintext appears to be Traccar GPS telemetry protocol commands.
>
> **Note**: The API design forces this pattern — the library's `decrypt()` function performs decryption inline and doesn't internally verify the tag. This is a limitation of the library API, not a bug in the library itself.

**Remediation**:
- Decrypt into a **temporary buffer**
- Only copy to the real output buffer **after** `checkTag()` / `secure_compare()` succeeds
- On failure, `clean()` the temporary buffer

---

### 🔴 CRITICAL-2: Server Falls Back to Forwarding Raw (Unencrypted) Data

**Location**: [server.go:90-98](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/server/src/server.go#L90-L98)

```go
plaintext, err = encryption.Decrypt(key, buf[:n])
if err != nil {
    // ...
    plaintext = buf[:n] // Forward the raw message to the backend
    // ...
}
```

> [!CAUTION]
> **If decryption fails for any reason — including a tampered message — the server forwards the raw bytes directly to the Traccar backend.** This completely defeats the purpose of encryption:
>
> 1. An attacker can send **unencrypted** commands directly to the proxy, and they will be forwarded verbatim to Traccar
> 2. All authentication and integrity guarantees are nullified
> 3. The proxy becomes a transparent pass-through for any malicious input
>
> **Impact**: Complete bypass of the encryption layer. Any network attacker can inject arbitrary Traccar protocol messages.

**Remediation**:
- **Drop** messages that fail decryption — never forward raw data
- Log the failure and return without forwarding
- Consider rate-limiting to detect brute-force attacks

---

### 🔴 CRITICAL-3: Example Key in Configuration Sample

**Location**: [config.sample.yml:2](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/server/config.sample.yml#L2)

```yaml
chacha_key: example123
```

> [!WARNING]
> The sample config contains a plaintext key value `example123` which is:
> 1. Not 64 hex characters (only 10 characters) — would fail the server's length validation
> 2. A non-random, guessable value
> 3. Risk: users may try to use a similarly weak key format
>
> Additionally, the key is stored as **plaintext in a YAML file** on disk. While the [server validates](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/server/src/server.go#L48-L50) that the key is 64 characters long, it does **not** validate that it's valid hex — `hex.DecodeString` errors are [silently ignored](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/server/src/server.go#L59) with `key, _ := hex.DecodeString(...)`.

**Remediation**:
- Use a proper 64-character hex example: `chacha_key: "0000...use generate-key.sh to create a real key...0000"`
- Check the error from `hex.DecodeString()` and fail if invalid
- Consider supporting environment variable or file-based key injection instead of inline YAML

---

## 3. High Severity Findings

### 🟠 HIGH-1: Encryption Key Not Scrubbed After Hex Parsing (ESP32)

**Location**: [telecrypt.cpp:19-22](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telecrypt.cpp#L19-L22) and [telecrypt.cpp:46-49](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telecrypt.cpp#L46-L49)

```cpp
unsigned char key[32];
for (int i = 0; i < 32; ++i) {
    sscanf(CHACHA20_KEY + 2*i, "%02x", &key[i]);
}
chachaPoly.setKey(key, sizeof(key));
// key[] is NEVER cleaned — remains on the stack
```

> [!WARNING]
> The 32-byte key is parsed onto the stack and never zeroed after use. On an ESP32, stack memory is reused but never explicitly cleared, meaning the key material persists in RAM until overwritten by chance. An attacker with physical access or a memory-read vulnerability could extract the key.

**Remediation**:
```cpp
chachaPoly.setKey(key, sizeof(key));
clean(key); // <-- Add this line
```

---

### 🟠 HIGH-2: `checkTag()` Crash Workaround Suggests Underlying Bug

**Location**: [telecrypt.cpp:92-112](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telecrypt.cpp#L92-L112)

```cpp
///// BEGIN TAG VERIFY
// The crypto library implementation of tag verification crashes.
```

The caller has **reimplemented** `checkTag()` logic inline because the library's built-in `ChaChaPoly::checkTag()` crashes on ESP32. The root cause is likely that `checkTag()` internally calls `computeTag()`, which **mutates** the Poly1305 state (calls `pad()` and `finalize()`). If `computeTag()` was already called before `checkTag()`, the Poly1305 state is corrupted, causing a crash or incorrect result.

Looking at the caller code, this is exactly what happens:
1. Line 77: `chachaPoly.computeTag(computedTag, sizeof(computedTag))` — mutates state
2. If `checkTag()` were called after, it would call `computeTag()` again on already-finalized state

The workaround is functionally correct but introduces maintenance risk.

---

### 🟠 HIGH-3: `dataSize` Counter Overflow for Large Messages

**Location**: [ChaChaPoly.cpp:113](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaChaPoly.cpp#L113), [ChaChaPoly.h:59](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaChaPoly.h#L59)

`state.dataSize` is `uint64_t`, which won't overflow in practice, but `state.authSize` is also `uint64_t` and **neither has overflow checks**. More importantly:

The **ChaCha20 counter** in [ChaCha.cpp:170-177](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaCha.cpp#L170-L177) is only **8 bytes** (64-bit when using 64-bit nonce) or **4 bytes** (32-bit when using 96-bit nonce). With a 96-bit nonce (12-byte IV as used by the caller), the counter is only 32 bits, limiting encryption to **256 GB** per nonce. With a 4-byte counter and 64-byte blocks, the maximum is 2^32 × 64 = 256 GiB — not a practical concern for ESP32 UDP packets, but the API doesn't enforce this.

**Risk**: Low for current use case (small UDP telemetry packets), but architecturally unsound.

---

## 4. Medium Severity Findings

### 🟡 MEDIUM-1: No Nonce Reuse Prevention (ESP32)

**Location**: [telecrypt.cpp:26-27](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telecrypt.cpp#L26-L27)

```cpp
unsigned char nonce[12];
esp_fill_random(nonce, sizeof(nonce)); // Use the ESP-IDF random number generator
```

The nonce is generated randomly for each encryption call. With a 96-bit nonce space:
- Birthday bound collision after ~2^48 messages (~281 trillion) — practically safe
- **However**, `esp_fill_random()` quality depends on the ESP32's hardware RNG initialization. If Wi-Fi/BT radio is not active, the ESP32 may use a **pseudo-RNG** with limited entropy

> [!IMPORTANT]
> If the ESP32's hardware RNG is not properly seeded (e.g., during early boot before radio initialization), nonce collisions become more likely. A nonce reuse with ChaCha20-Poly1305 completely breaks both confidentiality and authenticity.

**Server side**: [encrypt.go](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/server/src/encryption/encrypt.go#L16-L18) uses `crypto/rand.Reader` — ✅ secure on server.

---

### 🟡 MEDIUM-2: No Associated Authenticated Data (AAD) Used

**Location**: Both [telecrypt.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telecrypt.cpp) and [encrypt.go](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/server/src/encryption/encrypt.go)

Neither side uses `addAuthData()` (ESP32) or passes AAD to `aead.Seal()` / `aead.Open()` (Go — `nil` AAD parameter).

**Risk**: No binding of contextual data (device ID, sequence number, timestamp) to the ciphertext. An attacker can **replay** or **redirect** valid encrypted messages between different devices or sessions without detection.

**Remediation**: Include device identifier and/or a monotonic counter as AAD.

---

### 🟡 MEDIUM-3: `setKey()` Accepts Weak Key Sizes Without Rejection

**Location**: [ChaCha.cpp:87-109](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaCha.cpp#L87-L109)

```cpp
bool ChaCha::setKey(const uint8_t *key, size_t len)
{
    if (len <= 16) {
        // Uses "expand 16-byte k" — 128-bit key, duplicated
    } else {
        if (len > 32)
            len = 32;  // Silently truncates
        // Uses "expand 32-byte k"
    }
    return true; // ALWAYS returns true — never rejects a key
}
```

> [!WARNING]
> - A **1-byte key** is accepted and zero-padded to 16 bytes, then duplicated
> - A **33+ byte key** is silently truncated to 32 bytes
> - `setKey()` never returns `false`
>
> The caller ([telecrypt.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telecrypt.cpp#L23)) always passes 32 bytes, so this is not currently exploitable, but the API is dangerous.

---

## 5. Low Severity / Informational Findings

### 🟢 INFO-1: Reference to Obsolete Draft RFC

**Location**: [ChaChaPoly.cpp:37](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaChaPoly.cpp#L37)

```
Reference: https://tools.ietf.org/html/draft-irtf-cfrg-chacha20-poly1305-10
```

This references an Internet-Draft that has since been published as **RFC 8439** (formerly RFC 7539). The implementation is compliant with the final RFC, but the reference should be updated.

---

### 🟢 INFO-2: `clean()` Memory Clearing May Be Optimized Away

**Location**: [Crypto.cpp:34-44](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/Crypto.cpp#L34-L44)

```cpp
void clean(void *dest, size_t size)
{
    volatile uint8_t *d = (volatile uint8_t *)dest;
    while (size > 0) {
        *d++ = 0;
        --size;
    }
}
```

Uses `volatile` to prevent optimization — this is the standard embedded technique and is **generally effective**. However:
- C/C++ `volatile` semantics don't guarantee the compiler won't optimize the *caller's* code around the call
- Modern best practice is `memset_s()` (C11 Annex K) or platform-specific `SecureZeroMemory()`
- On ESP32 with GCC, the `volatile` approach is sufficient in practice

---

### 🟢 INFO-3: Server Key Hex Decode Error Silently Ignored

**Location**: [server.go:59](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/server/src/server.go#L59)

```go
key, _ := hex.DecodeString(config.ChachaKey)
```

The error from `hex.DecodeString` is discarded. If the key contains non-hex characters, `key` will be a partial decode, leading to an incorrect or truncated key. The length check on line 48 validates character count (64) but not hex validity.

---

### 🟢 INFO-4: Test Files Contain Hardcoded Keys

**Location**: [test.py:16](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/server/test/test.py#L16), [test_raw.py:24](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/server/test/test_raw.py#L24)

```python
key = bytes.fromhex('d38a3b96a26d0b1139bd30c174884f5dbc8eaaf492493725633ecebfa4ab19e9')
```

Hardcoded test keys are acceptable for test files but should **never** be used in production. Ensure this key is not used in any deployed configuration.

---

## 6. Side-Channel Analysis

### 6.1 Timing Side-Channels

| Component | Assessment |
|-----------|------------|
| **ChaCha20 quarter-round** | ✅ All operations are adds, XORs, and rotations — constant-time on all platforms |
| **ChaCha20 counter increment** | ✅ Explicitly constant-time (iterates all bytes regardless of carry) |
| **Poly1305 modular reduction** | ✅ Constant-time — no secret-dependent branches |
| **Poly1305 final reduction** | ✅ Constant-time selection via bitmask (`mask` / `nmask` pattern) |
| **`secure_compare()`** | ✅ Constant-time — XOR-accumulate, no early exit |
| **`secure_compare()` return value** | ✅ Uses arithmetic (`0x0100 - result) >> 8`) instead of comparison to avoid branch |

> [!TIP]
> The timing side-channel posture of the core library is excellent. This is consistent with the library's origin (Southern Storm Software) which was explicitly designed for embedded constant-time crypto.

### 6.2 Power Analysis / Electromagnetic Emanation

On ESP32 hardware, the XOR operations in `encrypt()` ([ChaCha.cpp:184](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/crypto/ChaCha.cpp#L184)) process one byte at a time. This byte-by-byte loop may be vulnerable to power analysis on embedded platforms. This is a hardware-level concern beyond the scope of software mitigations.

---

## 7. Protocol-Level Security Assessment

### 7.1 Wire Format

```
ESP32 → Server:  [12-byte nonce] [ciphertext] [16-byte tag]
Server → ESP32:  [12-byte nonce] [ciphertext] [16-byte tag]
```

Both sides use the same format. ✅ Compatible.

### 7.2 Replay Attacks

> [!IMPORTANT]
> **No replay protection exists.** A captured encrypted packet can be re-sent at any time and will be accepted by the server (or ESP32). Since there is no sequence number, timestamp, or session binding:
> - An attacker can replay old GPS position reports
> - An attacker can replay old server commands to the ESP32
> - The random nonce prevents nonce-reuse but does NOT prevent replay

### 7.3 Bidirectional Key Reuse

The same key is used for both directions (ESP32→Server and Server→ESP32). While ChaCha20-Poly1305 with unique nonces is safe under same-key bidirectional use, best practice is to derive **direction-specific keys** from a master key.

---

## 8. Comparison: ESP32 Library vs. Go `x/crypto`

| Feature | ESP32 (arduinolibs) | Go (`x/crypto/chacha20poly1305`) |
|---------|---------------------|----------------------------------|
| RFC compliance | ✅ RFC 8439 | ✅ RFC 8439 |
| Nonce size | 8 or 12 bytes | 12 bytes (standard) or 24 bytes (XChaCha) |
| Key size | Any ≤32 (padded) | Exactly 32 bytes (enforced) |
| Tag size | 1-16 bytes | 16 bytes (fixed) |
| AAD support | Yes (unused) | Yes (unused) |
| Constant-time | ✅ Manual implementation | ✅ Uses assembly-optimized Go stdlib |
| Interoperability | ✅ Compatible with 12-byte nonce | ✅ Standard |

**Interoperability is confirmed**: Both sides use 12-byte nonces, 32-byte keys, and 16-byte tags. The wire format `nonce || ciphertext || tag` is consistent.

---

## 9. Remediation Priority Matrix

| Priority | Finding | Effort | Impact |
|----------|---------|--------|--------|
| **P0** | CRITICAL-2: Remove raw fallback forwarding in server | Low | Eliminates complete security bypass |
| **P0** | CRITICAL-1: Verify tag before exposing plaintext | Medium | Prevents forged message processing |
| **P1** | HIGH-1: Clean key from stack after use | Low | Prevents key leakage via memory |
| **P1** | INFO-3: Check `hex.DecodeString` error | Low | Prevents silent key corruption |
| **P2** | MEDIUM-2: Add AAD with device/session context | Medium | Prevents replay/redirect attacks |
| **P2** | MEDIUM-1: Verify RNG quality at boot | Low | Ensures nonce uniqueness |
| **P3** | CRITICAL-3: Improve config sample and key storage | Low | Reduces misconfiguration risk |
| **P3** | MEDIUM-3: Reject weak key sizes in `setKey()` | Low | Defense in depth |

---

## 10. Summary Verdict

> [!IMPORTANT]
> **The core cryptographic primitives (ChaCha20, Poly1305, ChaChaPoly AEAD) are correctly implemented** and follow the RFC 8439 specification. The Southern Storm Software library is well-engineered with proper constant-time operations and memory cleaning.
>
> **The security vulnerabilities are in the integration layer**, not the crypto library itself:
> 1. The server's fallback-to-raw behavior creates a complete bypass
> 2. The ESP32 caller decrypts before authenticating
> 3. No replay protection exists at the protocol level
>
> These are application-level issues that should be addressed independently of the underlying crypto implementation.
