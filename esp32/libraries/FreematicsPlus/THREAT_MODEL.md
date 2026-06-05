# Threat Model: FreematicsPlus

## 1. System context

FreematicsPlus is a specialized C/C++ telematics library targeting the ESP32 platform, used primarily on Freematics ONE+ and Esprit hardware. The library exposes interfaces to communicate with an OBD-II diagnostic co-processor, external GPS modules, SIMCOM cellular modems, and local clients via BLE. The library is intended to compile into firmware that runs on vehicle trackers to collect diagnostic and location telemetry, uploading it to servers like Traccar over HTTP or UDP.

## 2. Assets

| asset | description | sensitivity |
|---|---|---|
| vehicle_telemetry | GPS coordinates, speed, RPM, battery voltage, VIN, Odometer and other sensor diagnostics. | medium |
| host_process_integrity | Firmware execution integrity on the ESP32 chip (prevention of crashes, freezes, or code execution). | critical |
| network_credentials | WiFi SSIDs, passwords, APN config, and remote host keys stored in memory or NVS. | high |
| can_bus_integrity | Active access/control to send CAN messages via link bridge interfaces. | critical |

## 3. Entry points & trust boundaries

| entry_point | description | trust_boundary | reachable_assets |
|---|---|---|---|
| BLE SPP Command Service | Wireless Bluetooth GATT SPP write handle (spp_command_uuid = 0xFFE1) used to receive configurations/commands. | Wireless unauthenticated client → BLE SPP server task | host_process_integrity, vehicle_telemetry, network_credentials |
| WiFi Client HTTP/UDP Receiver | Receives network data packets from remote endpoints over WiFi. | Remote network → Wifi client memory buffer | host_process_integrity, vehicle_telemetry |
| Cellular HTTP/UDP Receiver | Receives network data packets from remote endpoints over cellular (SIMCOM AT commands). | Cellular network → modem interface → serial buffer | host_process_integrity, vehicle_telemetry |
| OBD Co-processor UART/SPI Link | UART/SPI communication lines with the OBD co-processor link. | OBD co-processor → host process memory | host_process_integrity, vehicle_telemetry, can_bus_integrity |
| GPS NMEA Parser | Serial NMEA stream from the GPS receiver parsed character by character. | GPS serial output → NMEA parser | host_process_integrity, vehicle_telemetry |
| Physical flash/JTAG interface | Direct physical access to the ESP32 SPI flash pins or JTAG debug port. | Physical host interface → persistent flash memory | network_credentials |

## 4. Threats

| id | threat | actor | surface | asset | impact | likelihood | status | controls | evidence |
|---|---|---|---|---|---|---|---|---|---|
| T1 | Memory corruption leading to DoS or RCE via malformed UDP/TCP network responses | remote_unauth | WiFi Client HTTP/UDP Receiver, Cellular HTTP/UDP Receiver | host_process_integrity | critical | possible | partially_mitigated | Client sends UDP packets encrypted with ChaCha20-Poly1305 (using crypto library), authenticating packets before full decryption. Unencrypted HTTP interfaces remain unmitigated. | c0357a6, d1aef2e |
| T2 | Unauthorized CAN frame injection to vehicle network via SPI/UART link commands | adjacent_network | OBD Co-processor UART/SPI Link | can_bus_integrity | critical | possible | unmitigated | none | |
| T4 | Memory corruption and code execution via malformed OBD co-processor responses | adjacent_network | OBD Co-processor UART/SPI Link | host_process_integrity, vehicle_telemetry | high | possible | unmitigated | none | |
| T7 | Physical extraction of network credentials and cryptographic keys from device flash memory | local_user | Physical flash/JTAG interface | network_credentials | high | possible | unmitigated | No secure element available | |
| T3 | Unauthorized configuration or control command execution via unauthenticated Bluetooth BLE connection | adjacent_network | BLE SPP Command Service | host_process_integrity, vehicle_telemetry, network_credentials | high | very_rare | mitigated | BLE SPP service is disabled in the codebase | |
| T5 | Spoofing of vehicle location and time via simulated or spoofed GPS NMEA sentences | adjacent_network | GPS NMEA Parser | vehicle_telemetry | medium | possible | unmitigated | none | |
| T6 | Denial of Service via heap exhaustion from unauthenticated BLE command flooding | adjacent_network | BLE SPP Command Service | host_process_integrity | medium | very_rare | mitigated | BLE SPP service is disabled in the codebase | |

## 5. Deprioritized

| threat | reason |
|---|---|
| Repudiation: Actions performed by the device cannot be attributed to a specific user | Out of scope: The system operates as a single-user autonomous vehicle logger and does not support multi-tenant user authentication or require local non-repudiation controls. |
| Information Disclosure: Eavesdropping on the GPS serial connection | Out of scope: Eavesdropping on UART/SPI lines requires physical probe attachment to the PCB hardware, which is outside the scope of this software threat model. |

## 6. Open questions

- [Owner-states] BLE SPP is disabled. Affects: T3, T6 status. Verify by: Check `telelogger.ino` or configuration macros to verify BLE initialization/SPP server is compiled out.
- [Owner-states] Server supports PSK and ChaCha20-Poly1305 encryption for client UDP packets using the `crypto` library. Affects: T1 likelihood. Verify by: Confirm if all client network communications are encrypted via this library, or if unencrypted HTTP/UDP fallbacks remain.
- [Owner-states] No secure element is available on the hardware. Affects: T7 status. Verify by: Reviewing hardware schematics and bill of materials to confirm if flash-encryption or secure boot is configured instead.
- Upstream NMEA filtering: Is there any size limit or parsing sanity check applied to GPS serial data before sending it to the parser?

## 7. Provenance

- mode: bootstrap-then-interview
- date: 2026-06-06
- target: esp32/libraries/FreematicsPlus @ ba92f94
- inputs: git-log + CHANGELOG mined; owner interview answers
- owner: present, unnamed

## 8. Recommended mitigations

| mitigation | threat_ids | closes_class | effort |
|---|---|---|---|
| Enforce boundary checks on all network and link response parsing (e.g. check WifiHTTP and CellHTTP loops, and COBD::getVIN) | T1, T4 | yes | M |
| Enable ESP32 flash encryption and secure boot to prevent offline extraction of keys and credentials | T7 | yes | S |
| Restrict CAN write operations by implementing command filtering or a whitelist at the co-processor level | T2 | partial | L |
| Validate GPS satellite and checksum statistics to detect anomalies or spoofer signals | T5 | partial | S |
