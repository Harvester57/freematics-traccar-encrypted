# Threat Model: TinyGPS

## 1. System context

TinyGPS is an open-source C/C++ GPS parsing library designed for Arduino and other resource-constrained microcontrollers. In the context of this repository, it is deployed as an embedded library inside the ESP32-based telelogger project. The library receives character-by-character NMEA-0183 sentences (primarily `$GPRMC` and `$GPGGA`) from a connected hardware GPS module via a serial (UART) interface. It parses these streams to extract location data (latitude/longitude), datetime, speed, course, altitude, satellites count, and precision indices.

The library is relatively small (under 500 lines of code) and is designed to operate passively on incoming streams. However, because it is written in C++ and runs on an embedded device without operating system-level process isolation, vulnerabilities such as buffer overflows or out-of-bounds reads could lead to memory corruption, firmware crashes, or GPS spoofing. No public CVEs exist for the TinyGPS library, but manual code analysis reveals logic flaws and potential out-of-bounds access bugs.

## 2. Assets

| asset | description | sensitivity |
|---|---|---|
| host process integrity | The ESP32 microcontroller host firmware memory safety and correct execution state. | critical |
| GPS data integrity / location correctness | Parsed GPS data (latitude, longitude, time, course, speed) used by the tracking application. | high |
| service availability | The continuous availability of GPS tracking service without crashes or hangs. | medium |

## 3. Entry points & trust boundaries

| entry_point | description | trust_boundary | reachable_assets |
|---|---|---|---|
| NMEA input stream | Character-by-character NMEA sentence bytes parsed by `TinyGPS::encode(char c)`. | untrusted stream → process memory | host process integrity, GPS data integrity / location correctness, service availability |

## 4. Threats

| id | threat | actor | surface | asset | impact | likelihood | status | controls | evidence |
|---|---|---|---|---|---|---|---|---|---|
| T2 | Out-of-bounds memory read in cardinal course parser leading to firmware crash or undefined behavior | remote_unauth | NMEA input stream | host process integrity, service availability | medium | possible | partially_mitigated | hardware watchdog for automatic reboot |  |
| T3 | Signed integer overflow in NMEA numeric parsers leading to undefined behavior or incorrect data state | remote_unauth | NMEA input stream | host process integrity, GPS data integrity / location correctness | medium | possible | unmitigated | none |  |
| T4 | Denial of service via stream flooding causing CPU exhaustion or loss of valid GPS updates | remote_unauth | NMEA input stream | service availability | medium | possible | partially_mitigated | character buffer sizing limits in TinyGPS, hardware watchdog for automatic reboot |  |
| T5 | Out-of-bounds memory read in NMEA sentence type parser leading to undefined behavior or logic bypass | remote_unauth | NMEA input stream | host process integrity | low | possible | unmitigated | none |  |

## 5. Deprioritized

| threat | reason |
|---|---|
| Forgery of GPS location and datetime tracking data via unauthenticated NMEA input stream | Risk accepted by owner: GPS spoofing is considered an acceptable risk for this deployment. |
| Elevation of privilege from NMEA stream | Not applicable: TinyGPS is a single-privilege library running on a bare-metal microcontroller without privilege separation. |
| Information disclosure of local data via NMEA stream | Not applicable: TinyGPS only parses input passively and does not support output commands or queries to read local data. |
| Repudiation | Not applicable: TinyGPS does not maintain multi-user identity or audit logs; auditing is handled by the calling telelogger application. |

## 6. Open questions

- Are there upstream filters or rate-limiting controls on the character stream before it is passed to `TinyGPS::encode()`?
- [Owner-states] The serial/UART stream from the GPS module is dedicated and not multiplexed with other inputs. Affects: NMEA input stream isolation. Verify by: reviewing hardware schematics.
- [Owner-states] There is a hardware watchdog that automatically reboots the ESP32 in the event of a crash or hang. Affects: T2 and T4 status/controls. Verify by: testing the watchdog reset functionality in the firmware.

## 7. Provenance

- mode: bootstrap-then-interview
- date: 2026-06-05
- target: esp32/libraries/TinyGPS @ f57000a
- inputs: git-log + CHANGELOG mined, owner interview feedback
- owner: present, unnamed

## 8. Recommended mitigations

| mitigation | threat_ids | closes_class | effort |
|---|---|---|---|
| Modulo-normalize the course value and add bounds check in `TinyGPS::cardinal` | T2 | yes | S |
| Add string length validation before character skip in `TinyGPS::gpsstrcmp` | T5 | yes | S |
| Implement overflow checks and input length limits during integer parsing in `gpsatol` | T3 | yes | S |
| Implement location validation/filtering in the application layer (e.g. speed/distance thresholds) | T1 | partial | M |
