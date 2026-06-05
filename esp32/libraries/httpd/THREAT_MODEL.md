# Threat Model: MiniWeb HTTP Server (Freematics ESP32 Logger)

## 1. System context

MiniWeb is a lightweight, embeddable HTTP/1.1 web server implemented in C. In this repository, it is used by the Freematics ESP32 vehicle telelogger firmware to expose configuration and telemetry log files over a local WiFi network. The server runs directly on the ESP32 micro-controller, handling incoming connections, parsing URL query strings and JSON POST payloads, and serving telemetry CSV logs stored on SPIFFS or SD card storage.

## 2. Assets

| asset | description | sensitivity |
|---|---|---|
| Host process integrity | Integrity of the ESP32 firmware execution state and telelogger tasks. | critical |
| WiFi Credentials & Configuration | Saved WiFi SSID and passwords, and NVS configuration data. | high |
| Telemetry Log Files | Vehicle telemetry CSV log files stored on SPIFFS or SD card. | medium |
| Service Availability | Availability of the web server for live telemetry monitoring and log retrieval. | medium |

## 3. Entry points & trust boundaries

| entry_point | description | trust_boundary | reachable_assets |
|---|---|---|---|
| HTTP Port 80 | TCP socket listening on port 80 for incoming HTTP requests (GET, POST). Registered URL handlers parse paths and payloads. | unauth network → application logic | Host process integrity, WiFi Credentials & Configuration, Telemetry Log Files, Service Availability |
| Local Filesystem | Serves static files and reads telemetry CSV files from SPIFFS or SD card. | local file → process memory | Host process integrity, Telemetry Log Files |

## 4. Threats

| id | threat | actor | surface | asset | impact | likelihood | status | controls | evidence |
|---|---|---|---|---|---|---|---|---|---|
| T1 | Memory corruption or buffer overflow in HTTP request header or parameter parsing leading to daemon crash or remote code execution | remote_unauth | HTTP Port 80 | Host process integrity, Service Availability | critical | likely | unmitigated | none | CVE-2020-29596 |
| T2 | Directory traversal via URL-encoded sequences in HTTP paths leading to unauthorized reading of arbitrary files on SPIFFS/SD card | remote_unauth | Local Filesystem | Telemetry Log Files, WiFi Credentials & Configuration | high | likely | unmitigated | none | CVE-2011-4878 |
| T3 | Eavesdropping on unencrypted HTTP communication exposes telemetry logs and WiFi/NVS credentials in transit | adjacent_network | HTTP Port 80 | Telemetry Log Files, WiFi Credentials & Configuration | high | likely | unmitigated | none | |
| T4 | Authentication bypass or credential sniffing due to use of HTTP Basic Authentication over cleartext | remote_unauth | HTTP Port 80 | WiFi Credentials & Configuration, Host process integrity | high | possible | unmitigated | none | |
| T5 | NULL pointer dereference when allocating memory for HTTP headers, query parameters, or payloads under high concurrency or large size leading to device crash | remote_unauth | HTTP Port 80 | Service Availability, Host process integrity | medium | likely | unmitigated | none | |
| T6 | Out-of-bounds read in JSON parser when parsing truncated payloads leads to ESP32 firmware crash | remote_unauth | HTTP Port 80 | Service Availability, Host process integrity | medium | possible | unmitigated | none | |

## 5. Deprioritized

| threat | reason |
|---|---|
| Spoofing of Local Filesystem storage | Out of scope; filesystem resides on local physical flash/SD media, so remote network actors cannot spoof or manipulate the storage hardware directly. |
| Tampering of Local Filesystem logs | The web server only supports read-only operations (GET) and structured deletion (api/delete) of logs; arbitrary write/modification of local files is not supported by the HTTP endpoints. |
| Repudiation of HTTP actions | Not applicable as the vehicle telelogger is a single-user embedded device; multi-user audit logging and non-repudiation are not part of the security requirements. |

## 6. Open questions

- [Owner-states] No network restriction is applied to the WiFi Access Point (default credentials "PASSWORD" are used). Affects: T3, T4, T5, T6 likelihood. Verify by: inspecting telelogger config settings for WiFi AP configurations.
- [Owner-states] No client-side verification or encryption is applied to the telemetry CSV logs on consumer/receiver systems. Affects: T2, T3 impact. Verify by: checking traccar server integration and receiver decryption logic.
- Is there any FreeRTOS heap limit or safety wrapper in the firmware to prevent standard memory allocation failures (malloc/calloc) from crashing the main telelogger loop?

## 7. Provenance

- mode: bootstrap-then-interview
- date: 2026-06-06
- target: esp32/libraries/httpd @ d3da228
- inputs: git-log + CHANGELOG mined; Owner interview input
- owner: Florian

## 8. Recommended mitigations

| mitigation | threat_ids | closes_class | effort |
|---|---|---|---|
| Replace all unsafe string functions (sprintf, strcpy) with bounds-checked alternatives (snprintf, strncpy), and enforce maximum size limits on HTTP header fields. | T1 | yes | M |
| Perform directory traversal validation on URL paths after decoding all URL-encoded characters (e.g. checking that the path does not resolve outside the web root directory). | T2 | yes | S |
| Fix the JSON parser to validate payload bounds before advancing pointers, and explicitly handle truncated JSON objects. | T6 | yes | S |
| Check the return value of all malloc, calloc, and realloc calls, and gracefully reject requests with HTTP 500/503 errors if memory is exhausted. | T5 | yes | M |
| Implement TLS/HTTPS support for the web server, or restrict access to the local Access Point with strong WPA2/WPA3 passwords. | T3, T4 | partial | L |
