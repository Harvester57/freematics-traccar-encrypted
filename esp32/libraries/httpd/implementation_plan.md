# Implementation Plan: Migrate HTTP Server to Espressif Native `esp_http_server`

Migrate the web server implementation in the Freematics ESP32 vehicle telelogger from the legacy **MiniWeb** library ([httpd](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd)) to Espressif's official, native **`esp_http_server`** component. This will significantly improve security, memory stability, and code maintainability.

## User Review Required

> [!IMPORTANT]
> **No Threading/Task Model Blocking:** `esp_http_server` runs in its own FreeRTOS task created during startup. Handlers will execute in this context. While the telelogger's logging routines run in the main loop/other tasks, accessing shared files on the SD/SPIFFS card or live data structures must remain safe. Since the original MiniWeb server also ran asynchronously (or via polling that shared memory), the shared resource boundaries remain similar, but we must verify that no thread-safety issues arise.

> [!NOTE]
> **API Paths and Behavior:** All existing endpoint names and behaviors will be preserved exactly as they are currently documented and implemented:
> * `/api/info` - Device info (JSON)
> * `/api/live` - Live sensor/OBD telemetry (JSON)
> * `/api/list` - List telemetry CSV log files (JSON)
> * `/api/data/<id>?pid=<PID>` - JSON array of selected PID telemetry data
> * `/api/log/<id>` - Raw CSV telemetry file download
> * `/api/delete/<id>` - Delete telemetry log file

## Open Questions

> [!NOTE]
> **Do we need HTTPS/TLS immediately?** 
> The native server has a direct counterpart (`esp_https_server`) for TLS support. However, to minimize initial changes and preserve performance/heap space, we propose migrating to standard HTTP on port 80 first. If HTTPS is desired subsequently, it can be layered on top by modifying the server configuration and adding TLS certificates.

---

## Proposed Changes

### Web Server Component & Configuration

#### [DELETE] [httpd](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd)
We will completely remove the legacy MiniWeb files:
* [httpd.c](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/httpd.c)
* [httpd.h](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/httpd.h)
* [httpint.h](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/httpint.h)
* [httpjson.c](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/httpjson.c)
* [httppil.c](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/httppil.c)
* [httppil.h](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/httppil.h)
* [THREAT_MODEL.md](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/THREAT_MODEL.md)

#### [MODIFY] [dataserver.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/dataserver.cpp)
Refactor the web server setup, process loop, and endpoint handlers to use the new `esp_http_server` API.

* **Server Initialization & Lifespan:**
  * Replace the `HttpParam httpParam` global variable and `mwInitParam` calls with a handler of type `httpd_handle_t server = NULL;`.
  * Rewrite `serverSetup(IPAddress& ip)` to initialize and start `esp_http_server` with default configuration (`HTTPD_DEFAULT_CONFIG()`), and register the URI handlers.
  * Simplify `serverProcess(int timeout)` to just a delay or task yield, since `esp_http_server` runs background tasks natively and does not require polling via a loop function like `mwHttpLoop`.
* **API Endpoints Registration:**
  * Map `urlHandlerList` endpoints to `httpd_uri_t` structures.
  * Implement URI matching with wildcards for path-parameter endpoints like `/api/log/*` or `/api/data/*`.
* **Query Parameter Helper Functions:**
  * Implement lightweight helper functions using `httpd_query_key_value` to parse parameters like `pid`, `start`, and `duration`.
* **Refactoring Handlers:**
  * **`handlerInfo`**: Refactor to construct the JSON payload and send it using `httpd_resp_send()`. Set content-type to `application/json` via `httpd_resp_set_type()`.
  * **`handlerLogList`**: Read file names from SPIFFS/SD card and format JSON array. Send via `httpd_resp_send()`.
  * **`handlerLogDelete`**: Parse the ID from the URL path, delete the file, and send the text response.
  * **`handlerLogFile`**: Clean up chunked file streaming. Use a loop reading the file in chunks (e.g. 1-2 KB buffer) and transmit it using `httpd_resp_send_chunk(req, chunk_buf, bytes_read)`. When EOF is reached, close the file and call `httpd_resp_send_chunk(req, NULL, 0)` to finish. This replaces the complex connection-state checking via `param->hs->ptr`.
  * **`handlerLogData`**: Stream filtered CSV rows in JSON format chunk-by-chunk using `httpd_resp_send_chunk`.

#### [MODIFY] [telelogger.ino](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino)
* Replace `#include <httpd.h>` with `#include <esp_http_server.h>`.
* Refactor `handlerLiveData` to match the `esp_http_server` callback signature (`esp_err_t handlerLiveData(httpd_req_t *req)`).
* Use `httpd_resp_send()` to send live telemetry data and set appropriate response headers.

---

## Verification Plan

Since we are working with an embedded ESP32 platform, testing must cover both compilation correctness and runtime functionality.

### Automated Verification
1. **Compilation Check:**
   * Run the PlatformIO compile command to ensure all changes build without warnings or errors.
   * Command: `pio run -d esp32/telelogger`

### Manual Verification
1. **AP Connection & Network Availability:**
   * Boot the ESP32 and connect to the local softAP (WIFI SSID / Password configuration).
   * Confirm the device serves IP `192.168.4.1` (or configured gateway).
2. **API Endpoint Verification (via `curl` or browser):**
   * Check `/api/info` to verify basic system metrics (JSON).
   * Check `/api/live` to verify OBD, GPS, and MEMS parameters are populating correctly (JSON).
   * Check `/api/list` to list data CSV files.
   * Request `/api/log/<id>` to verify chunked telemetry CSV files stream correctly, terminate cleanly, and do not cause heap memory leaks.
   * Query `/api/data/<id>?pid=10d` (or other hexadecimal PIDs) to check filtered data output.
   * Request `/api/delete/<id>` to delete files and confirm they are removed.
