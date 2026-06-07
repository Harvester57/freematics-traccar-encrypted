# VULN-FINDINGS: FreematicsPlus Static Security Review

**Target:** `esp32/libraries/FreematicsPlus`
**Scanned at:** 2026-06-07T09:23:00+02:00
**Source files reviewed:** 15 (FreematicsNetwork.cpp/.h, FreematicsOBD.cpp/.h, FreematicsGPS.cpp/.h, FreematicsPlus.cpp/.h, FreematicsMEMS.cpp/.h, FreematicsBase.h, utility/ble_spp_server.c/.h, utility/OBD.h, utility/ICM_20948_C.h)
**Threat model:** THREAT_MODEL.md present and used for scoping

---

## Summary Table

| ID | Sev | Confidence | Category | Location | Title |
|----|-----|-----------|----------|----------|-------|
| F-001 | HIGH | 0.90 | heap-buffer-overflow | FreematicsOBD.cpp:327 | getVIN() writes decoded bytes with no upper-bound check |
| F-002 | HIGH | 0.85 | stack-buffer-overflow | FreematicsNetwork.cpp:309 | setup() sprintf APN/user/pass into 512-byte heap buffer |
| F-003 | HIGH | 0.85 | heap-buffer-overflow | FreematicsNetwork.cpp:924 | CellHTTP::receive() SIM7070 null write at modem-controlled offset |
| F-004 | MEDIUM | 0.80 | stack-buffer-overflow | FreematicsNetwork.cpp:531 | queryIP() sprintf host into m_buffer without length check |
| F-005 | MEDIUM | 0.75 | heap-buffer-overflow | FreematicsNetwork.cpp:943 | CellHTTP::receive() SIM7670 incorrect bounds guard on null write |
| F-006 | MEDIUM | 0.80 | heap-buffer-overflow | utility/ble_spp_server.c:277 | BLE GATT write: malloc with attacker-controlled len, no upper bound |
| F-007 | MEDIUM | 0.70 | stack-buffer-overflow | FreematicsNetwork.cpp:751 | CellUDP::receive() atoi-controlled null write, sign/offset issue |
| F-008 | MEDIUM | 0.65 | stack-buffer-overflow | FreematicsNetwork.cpp:875 | CellHTTP::send() SIM7670 sprintf host+path without length check |
| F-009 | LOW | 0.60 | stack-buffer-overflow | FreematicsPlus.cpp:593 | gpsBegin() GPS settings command built with unchecked sprintf loop |
| F-010 | LOW | 0.55 | out-of-bounds-read | FreematicsGPS.cpp:91 | NMEA _term[] silent truncation may cause incorrect GPS data parsing |

---

## F-001 — HIGH · 0.90 · heap-buffer-overflow
**File:** `FreematicsOBD.cpp:327`
**Title:** COBD::getVIN() writes decoded VIN bytes back into the same receive buffer without bounds checking

**Description:**
In `getVIN()` (lines 315–343), the caller passes a buffer of `bufsize` bytes. The function calls `link->sendCommand("0902\r", buffer, bufsize, ...)` to fill `buffer` with the raw co-processor response. It then decodes hex bytes **in-place**: the write pointer `q` starts at `buffer[0]` and advances via `*(q++) = hex2uint8(p)` (line 327) inside a loop that continues as long as `strchr` finds `:` continuation markers (line 332). There is **no check** that `q` stays below `buffer + bufsize`. A malicious or glitching OBD co-processor can send a response with many continuation lines, each yielding additional decoded bytes, causing `q` to overwrite heap memory past the end of the buffer.

**Exploit Scenario:**
A compromised/emulated OBD co-processor sends a VIN response with a large `len` value (from `hex2uint16` at line 319) and many `:` continuation markers. The inner decode loop advances `q` past `buffer + bufsize`, overwriting adjacent heap allocations, potentially leading to code execution on the ESP32.

**Recommendation:**
Add a bounds check before each write: `if (q < buffer + bufsize - 1) { *(q++) = hex2uint8(p); } else { break; }`. Also validate that `len = hex2uint16(buffer)` does not exceed `bufsize - 1` before entering the decode loop.

---

## F-002 — HIGH · 0.85 · stack-buffer-overflow
**File:** `FreematicsNetwork.cpp:309`
**Title:** CellSIMCOM::setup() builds AT commands into m_buffer (512 bytes) via sprintf with unbounded APN/username/password strings

**Description:**
At lines 309–311 and 362–371, APN configuration strings are `sprintf`'d into `m_buffer` (heap-allocated, 512 bytes) with no length cap:
- L309: `sprintf(m_buffer, "AT+CNCFG=0,0,\"%s\",\"%s\",\"%s\",3\r", apn, username, password)`
- L311: `sprintf(m_buffer, "AT+CNCFG=0,0,\"%s\"\r", apn)`
- L362/367/370: similar patterns for CGDCONT, CGSOCKCONT, CSOCKAUTH

If the combined string length exceeds ~490 characters, the heap buffer overflows. The APN/credentials may be sourced from NVS flash, which is modifiable by a physical attacker (T7).

**Exploit Scenario:**
Attacker with flash access sets an oversized APN string (500+ chars) in NVS. On next boot, `setup()` overflows `m_buffer` on the heap, corrupting adjacent FreeRTOS heap metadata.

**Recommendation:**
Replace all `sprintf(m_buffer, ...)` calls that embed external strings with `snprintf(m_buffer, RECV_BUF_SIZE, ...)`.

---

## F-003 — HIGH · 0.85 · heap-buffer-overflow
**File:** `FreematicsNetwork.cpp:924`
**Title:** CellHTTP::receive() SIM7070 path writes null terminator at modem-controlled byte offset without bounds check

**Description:**
In the SIM7070 branch (lines 918–926):
```c
int bytes = atoi(p += 9);      // value comes from modem AT response
p = strchr(p, '\n');
if (p++) {
    *(p + bytes) = 0;          // no bounds check on bytes
    return p;
}
```
`bytes` is read directly from the modem `+SHREAD: N` response via `atoi()` with no maximum cap. If the modem sends `+SHREAD: 1000`, the null write at `*(p + 1000) = 0` is 488+ bytes past the end of the 512-byte `m_buffer`, corrupting heap metadata.

**Exploit Scenario:**
A rogue cellular base station sends a crafted HTTP response whose `+SHREAD:` AT indication reports 2000 bytes. The ESP32 writes a null byte 2000 bytes past the payload pointer inside the 512-byte `m_buffer`, corrupting adjacent heap structures.

**Recommendation:**
Add: `if (bytes > 0 && p + bytes < m_buffer + RECV_BUF_SIZE - 1) { *(p + bytes) = 0; }` Apply the same fix to the SIM7670 path (line 943, F-005).

---

## F-004 — MEDIUM · 0.80 · stack-buffer-overflow
**File:** `FreematicsNetwork.cpp:531`
**Title:** CellSIMCOM::queryIP() passes unbounded host string into sprintf targeting m_buffer (512 bytes)

**Description:**
Lines 531 and 545 use `sprintf(m_buffer, "AT+CDNSGIP=\"%s\"...", host)` with no length check on `host`. If host exceeds ~488 chars, the 512-byte `m_buffer` heap allocation overflows. Same class as F-002.

**Exploit Scenario:**
NVS flash manipulation sets server hostname to 500+ chars; `queryIP()` overflows `m_buffer`.

**Recommendation:** Replace with `snprintf(m_buffer, RECV_BUF_SIZE, ...)` at lines 531 and 545.

---

## F-005 — MEDIUM · 0.75 · heap-buffer-overflow
**File:** `FreematicsNetwork.cpp:943`
**Title:** CellHTTP::receive() SIM7670 path incorrect bounds guard on null write

**Description:**
Line 943: `if (bytes < RECV_BUF_SIZE - 32) *(p + bytes) = 0;`
The guard checks an absolute value but does not account for `p`'s position within `m_buffer`. If `p` is at offset ≥33 in `m_buffer` and `bytes = 479`, the guard passes but `p + 479` writes past the 512-byte allocation boundary.

**Recommendation:**
Change to: `if (p + bytes < m_buffer + RECV_BUF_SIZE - 1) *(p + bytes) = 0;`

---

## F-006 — MEDIUM · 0.80 · heap-buffer-overflow
**File:** `utility/ble_spp_server.c:277`
**Title:** BLE GATT write handler: malloc with attacker-controlled length, no upper-bound validation; unauthenticated peer access

**Description:**
In the GATT write handler (lines 276–288) for the SPP command characteristic (0xFFE1):
```c
uint8_t *spp_cmd_buff = (uint8_t *)malloc(p_data->write.len + 1);
memcpy(spp_cmd_buff, p_data->write.value, p_data->write.len);
```
`p_data->write.len` is attacker-controlled (comes from the BLE peer). No maximum length check exists before the allocation. The BLE advertisement policy is `ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY` (line 72) — **no pairing or bonding is required** to connect and write. While the data characteristic is compiled out (`#if 0`), the command characteristic remains active.

**Exploit Scenario:**
An unauthenticated BLE device within ~10m connects and sends repeated large GATT writes to 0xFFE1. Each write triggers an uncapped malloc, fragmenting and exhausting the FreeRTOS heap, causing firmware crashes or inability to allocate critical structures.

**Recommendation:**
1. Add: `if (p_data->write.len > SPP_CMD_MAX_LEN) break;` before the malloc.
2. Enable BLE pairing/bonding.
3. If BLE is truly disabled, remove the `ble_init()` call entirely.

---

## F-007 — MEDIUM · 0.70 · stack-buffer-overflow
**File:** `FreematicsNetwork.cpp:751`
**Title:** CellUDP::receive() atoi-controlled null write: sign and offset edge cases

**Description:**
Lines 751–756 (SIM7600 path): `int len = atoi(p + 4);` reads the data length from the `+IPD` modem URC. The guard `if (strlen(++p) > len) *(p + len) = 0` may malfunction if `len` is negative (from `atoi("-1")`), producing an always-true comparison (unsigned coercion) and writing at `p - 1`. If `len` is larger than actual data, the buffer is returned unterminated.

**Recommendation:**
Validate `len >= 0 && p + len < m_buffer + RECV_BUF_SIZE` before the null write.

---

## F-008 — MEDIUM · 0.65 · stack-buffer-overflow
**File:** `FreematicsNetwork.cpp:875`
**Title:** CellHTTP::send() SIM7670 path: sprintf host+path into m_buffer without length check

**Description:**
Line 875: `sprintf(m_buffer, "AT+HTTPPARA=\"URL\",\"https://%s:%u%s\"\r", host, port, path)` — `host` and `path` are unbounded caller-supplied strings. If host + path exceeds ~480 chars, the 512-byte `m_buffer` overflows. Similar patterns at lines 786, 790, 816, 855.

**Recommendation:** Replace all `sprintf(m_buffer, ...)` with `snprintf(m_buffer, RECV_BUF_SIZE, ...)`.

---

## F-009 — LOW · 0.60 · stack-buffer-overflow
**File:** `FreematicsPlus.cpp:593`
**Title:** gpsBegin() GPS settings command built with unchecked repeated sprintf into 256-byte stack buffer

**Description:**
Lines 592–594 build an `ATGDS` command by appending each byte of `gpsSettings` as hex via `sprintf(buf + n, "%02X ", ...)`. Current `gpsSettings` is 27 bytes (total ~86 chars), safely within `buf[256]`. However, there is no bounds check in the loop — a future expansion of `gpsSettings` beyond 83 bytes would overflow the stack buffer with no compile-time or runtime warning.

**Recommendation:** Use `snprintf` with size tracking: `n += snprintf(buf + n, sizeof(buf) - n, "%02X ", gpsSettings[i]); if (n >= sizeof(buf)) break;`

---

## F-010 — LOW · 0.55 · out-of-bounds-read
**File:** `FreematicsGPS.cpp:91`
**Title:** NMEA _term[] silent truncation at 14 chars may produce incorrect GPS data while checksum still validates

**Description:**
The `_term[15]` buffer (FreematicsGPS.h:113) stores NMEA field content one character at a time. Characters beyond offset 13 are silently dropped (line 90 guard). The XOR parity checksum still accumulates all characters (line 93). For abnormally long data fields (which a GPS spoofer could craft), the truncated value is parsed while the full checksum validates — producing accepted but wrong GPS data. No memory safety issue exists (buffer is correctly guarded).

**Recommendation:** Flag or discard sentences where term length truncation is detected. This is a data-integrity defense against GPS spoofing (T5), not a memory safety fix.

---

## Next Steps

```
/triage esp32/libraries/FreematicsPlus/VULN-FINDINGS.json --repo esp32/libraries/FreematicsPlus
```

> **Note:** These are **static candidates**, not verified exploits. For execution-verified crashes and PoC reproduction, use `vuln-pipeline run <target>` (README Step 2).
