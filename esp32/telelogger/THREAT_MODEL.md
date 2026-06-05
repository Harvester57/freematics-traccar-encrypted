# Threat Model: telelogger

## 1. System context
telelogger is an Arduino-based vehicle telemetry logging firmware running on the Freematics ONE+ ESP32 vehicle data logger device. It collects real-time vehicle telemetry data from OBD-II diagnostics (via CAN/K-line), geolocation data from internal/external GNSS receivers, motion data from MEMS sensors (accelerometer, gyroscope), and external sensor inputs. Collected telemetry is buffered in IRAM/PSRAM and can be stored locally on a MicroSD card or SPIFFS flash. It is transmitted in real-time to a remote Traccar/Freematics server over UDP or HTTP(s) via built-in WiFi or cellular modems. When enabled, UDP telemetry is encrypted end-to-end using ChaCha20-Poly1305. The device also supports configuration and diagnostics via a Bluetooth Low Energy (BLE) Serial Port Profile (SPP) interface and local HTTP APIs.

## 2. Assets
| asset | description | sensitivity |
|---|---|---|
| CHACHA20_KEY | 256-bit encryption key used to encrypt and decrypt UDP packet telemetry | critical |
| wifiPassword | WPA2 password credentials for connecting to the configured WiFi access point | high |
| cellCredentials | Cellular APN credentials and SIM PIN configuration stored in device flash | high |
| telemetry data | Real-time vehicle telemetry including OBD-II values, GPS coordinates, speed, and device IDs | medium |
| host process integrity | Execution integrity of the ESP32 microcontroller, protecting against control flow hijacking | critical |
| OBD-II vehicle bus communication | Direct communication stream with the vehicle's ECU; must prevent unauthorized CAN message injection | critical |

## 3. Entry points & trust boundaries
| entry_point | description | trust_boundary | reachable_assets |
|---|---|---|---|
| remote server network responses | UDP/HTTP packets received from the remote tracking server | untrusted network → process memory | host process integrity, telemetry data |
| local BLE interface | BLE SPP commands processed locally from Bluetooth broadcasts | untrusted Bluetooth → application configuration | wifiPassword, cellCredentials, host process integrity |
| OBD-II CAN connection | Incoming OBD-II telemetry read from vehicle's Engine Control Unit (ECU) | vehicle bus → process memory | host process integrity, telemetry data |

## 4. Threats
| id | threat | actor | surface | asset | impact | likelihood | status | controls | evidence |
|---|---|---|---|---|---|---|---|---|---|
| T1 | Memory corruption leading to RCE via stack buffer overflow in UDP decryption | remote_unauth | remote server network responses | host process integrity | critical | likely | unmitigated | none | c0357a63c54b6103c88e71e51776749a02bb6801 |
| T3 | Traffic eavesdropping or spoofing when server encryption is disabled | adjacent_network | remote server network responses | telemetry data | high | possible | partially_mitigated | SERVER_ENCRYPTION_ENABLE configuration parameter |  |
| T4 | Memory corruption via malformed OBD-II ECU responses | local_user | OBD-II CAN connection | host process integrity | critical | rare | unmitigated | none |  |

## 5. Deprioritized
| threat | reason |
|---|---|
| Unauthenticated configuration modification and credentials theft via BLE interface (T2) | BLE is disabled by default (ENABLE_BLE 0 in config.h) and is not used operationally. |
| Information leakage via local HTTPD | ENABLE_HTTPD is disabled by default in config.h (set to 0) |

## 6. Open questions
- Does the underlying cell/WiFi network library enforce buffer size restrictions on incoming UDP packet buffers before they are processed by the application? (Owner currently does not have the details on the library's internal UDP buffer handling).

## 7. Provenance
- mode: bootstrap-then-interview
- date: 2026-06-05
- target: esp32/telelogger @ 7da6fc2
- inputs: git-log + CHANGELOG mined
- owner: Florian

## 8. Recommended mitigations
| mitigation | threat_ids | closes_class | effort |
|---|---|---|---|
| Pass size parameters to decrypt_string and enforce bounds checks on destination buffers | T1 | yes | S |
| Enforce SERVER_ENCRYPTION_ENABLE as a mandatory compilation flag and prohibit fallback | T3 | yes | S |
| Implement input validation and length assertions on incoming OBD-II message parsing buffers | T4 | partial | M |
