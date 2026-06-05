# Threat Model: ESP32 Cryptographic Library (Arduinolibs Crypto)

## 1. System context

The `esp32/libraries/crypto` library is a lightweight, bare-metal C++ cryptographic library tailored for embedded systems and microcontrollers (specifically ESP32). It is based on Southern Storm Software's `arduinolibs` (2015) and implements essential cryptographic primitives needed for secure network transmission, telemetry authentication, and public-key cryptography helper arithmetic.

The library features:
1. **ChaCha20**: A stream cipher compliant with RFC 8439, supporting both 64-bit and 96-bit nonces, 128-bit/256-bit keys, and manual constant-time timing safety.
2. **Poly1305**: A high-speed message authentication code (MAC) algorithm operating mod 2^130-5, designed to be constant-time.
3. **ChaChaPoly**: An Authenticated Encryption with Associated Data (AEAD) construction combining ChaCha20 and Poly1305 in an Encrypt-then-MAC configuration.
4. **BigNumberUtil**: A utility class providing multi-precision integer (limb-based) arithmetic (addition, subtraction, multiplication, modular reduction mod 2^130-5) supporting 8, 16, 32, or 64-bit limbs.
5. **Crypto utilities**: Timing-safe memory cleaning (`clean`) and comparison (`secure_compare`).

In the `telelogger` vehicle tracker deployment, the library is statically compiled into the firmware using the `xtensa-esp32-elf-g++` toolchain with size optimization (`-Os`), stack protection (`-fstack-protector`), and function/data sections enabled (`-ffunction-sections`, `-fdata-sections`). It runs directly on the ESP32 hardware with bare-metal/FreeRTOS privileges. It processes UDP packet payloads and configures keying material on the stack, making timing safety, stack security, and primitive robustness critical.

## 2. Assets

| asset | description | sensitivity |
|---|---|---|
| Cryptographic Keys and Nonces | Symmetric keys (ChaCha, Poly1305) and nonces stored temporarily in memory. | critical |
| Plaintext Data | Sensitive telemetry or command payloads before encryption or after decryption. | high |
| Data Authenticity/Integrity | Verification state ensuring message authentication tags are valid and correct. | high |
| Firmware/Process Execution Integrity | Memory integrity and execution state of the ESP32 firmware (avoiding buffer overflows, RCE, or crashes). | critical |
| Constant-Time Execution Property | Timing characteristics of cryptographic operations preventing side-channel key recovery. | high |

## 3. Entry points & trust boundaries

| entry_point | description | trust_boundary | reachable_assets |
|---|---|---|---|
| Cipher API (setKey, setIV, encrypt, decrypt) | Function parameters supplying keying material and plaintext/ciphertext data. | application code → cipher state / process memory | Cryptographic Keys and Nonces, Plaintext Data, Firmware/Process Execution Integrity |
| Authenticated Cipher API (addAuthData, computeTag, checkTag) | Function parameters passing associated authenticated data and MAC verification tags. | application code / network input → authenticated cipher state | Data Authenticity/Integrity, Cryptographic Keys and Nonces, Plaintext Data |
| BigNumberUtil API (unpackLE, unpackBE, packLE, packBE, math methods) | Math helper functions converting between byte streams (untrusted network formats) and big number limb arrays. | untrusted byte arrays → limb arrays / process memory | Firmware/Process Execution Integrity |
| Crypto utility API (clean, secure_compare) | Helper methods for memory clearing and timing-safe comparisons. | caller data → constant-time comparison/cleaning | Cryptographic Keys and Nonces, Constant-Time Execution Property |

## 4. Threats

| id | threat | actor | surface | asset | impact | likelihood | status | controls | evidence |
|---|---|---|---|---|---|---|---|---|---|
| T1 | Symmetric key extraction or plaintext leakage due to lingering stack memory not securely zeroed | local_user | Cipher API (setKey, setIV, encrypt, decrypt), Authenticated Cipher API (addAuthData, computeTag, checkTag), Crypto utility API (clean, secure_compare) | Cryptographic Keys and Nonces, Plaintext Data | critical | likely | partially_mitigated | Destructors and `clear()` call `clean()`, which uses `volatile` pointers and assembly memory barrier. Compiler options do not use LTO, preserving standard volatile assumptions. | security_analysis.md:HIGH-1, security_analysis.md:INFO-2 |
| T2 | Memory corruption leading to code execution or denial of service via mismatched sizes in BigNumber conversion functions | remote_unauth | BigNumberUtil API (unpackLE, unpackBE, packLE, packBE, math methods) | Firmware/Process Execution Integrity | critical | very_rare | mitigated | `BigNumberUtil` is completely unused in the active firmware codebase; compiler options `-ffunction-sections`, `-fdata-sections` and size optimization (`-Os`) cause the unused helper code to be entirely stripped by the linker. | |
| T3 | Authentication tag verification bypass or crashes due to destructive finalization in stateful API reuse | remote_unauth | Authenticated Cipher API (addAuthData, computeTag, checkTag) | Data Authenticity/Integrity, Firmware/Process Execution Integrity | high | likely | unmitigated | none | security_analysis.md:HIGH-2 |
| T4 | Key space reduction or truncation resulting in weak symmetric keys due to unvalidated input sizes | supply_chain | Cipher API (setKey, setIV, encrypt, decrypt) | Cryptographic Keys and Nonces | high | possible | unmitigated | none | security_analysis.md:MEDIUM-3 |
| T5 | Key recovery or plaintext leakage via timing side-channel attacks on non-constant-time calculations | adjacent_network | Cipher API (setKey, setIV, encrypt, decrypt), Authenticated Cipher API (addAuthData, computeTag, checkTag), BigNumberUtil API (unpackLE, unpackBE, packLE, packBE, math methods), Crypto utility API (clean, secure_compare) | Cryptographic Keys and Nonces, Plaintext Data, Constant-Time Execution Property | high | rare | mitigated | Manual constant-time operations for ChaCha20 quarter-round, counter increment, Poly1305 reduction, and `secure_compare`. | security_analysis.md:Section 6.1 |
| T6 | Key recovery or plaintext leakage via power analysis or electromagnetic side-channels on hardware | adjacent_network | Cipher API (setKey, setIV, encrypt, decrypt) | Cryptographic Keys and Nonces, Plaintext Data | medium | possible | unmitigated | none; target hardware is a basic board without hardware side-channel countermeasures. | security_analysis.md:Section 6.2 |

## 5. Deprioritized

| threat | reason |
|---|---|
| Replay attacks | Deprioritized; the library provides cryptographic primitives but lacks session tracking state. Replay protection must be implemented at the protocol/application integration layer. |
| Key storage and management | Deprioritized; the library operates purely on in-memory keys passed by the caller application. Secure persistent key storage must be handled by the firmware. |
| Nonce entropy generation | Deprioritized; the library accepts external IV parameters via `setIV()` and does not generate nonces itself. Nonce uniqueness and RNG seeding are caller responsibilities. |
| Physical debugging interface access (JTAG/SWD) | Deprioritized; physical debug interfaces are absent on the target deployment boards. |

## 6. Open questions

- Does the compiler toolchain ever perform cross-module optimizations or register-spill operations that leak key materials despite memory barriers in `clean()`?
- Are compiler flags like `-fstack-protector` fully active and generating protection canaries for the critical cryptostate parsing functions in `telecrypt.cpp`?

## 7. Provenance

- mode: bootstrap-then-interview
- date: 2026-06-05
- target: esp32/libraries/crypto @ dbb39af
- inputs: security_analysis.md, compiler options, owner interview
- owner: Florian

## 8. Recommended mitigations

| mitigation | threat_ids | closes_class | effort |
|---|---|---|---|
| Implement explicit bounds checking in BigNumberUtil::unpackLE and BigNumberUtil::unpackBE to prevent writes past the destination limb array length (though currently dead code). | T2 | yes | M |
| Reject invalid key lengths (e.g., return false if length is not exactly 16 or 32 bytes) in ChaCha::setKey instead of silently padding or truncating. | T4 | yes | S |
| Modify ChaChaPoly::checkTag to perform operations on a cloned state, preserving the state for subsequent calls, or defensively reset state parameters. | T3 | yes | S |
| Standardize stack and heap clearing calls on Platform/OS secure-zero implementations (e.g. memset_s or native ESP-IDF secure clearing helpers) to ensure compiler LTO never optimizes them away. | T1 | partial | S |
| Verify timing-safe assembly/machine instructions in final production builds using automated side-channel evaluation tools. | T5 | yes | M |
