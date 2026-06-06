# Vulnerability Scan Findings — Freematics Traccar Decryption Server

**Target:** `server/`
**Scanned at:** 2026-06-06T02:19:00+02:00
**Source files reviewed:** 8 (5 Go, 3 shell/config)
**Focus areas:** 4

## Summary

| Total | HIGH | MEDIUM | LOW | Low Confidence |
|-------|------|--------|-----|----------------|
| 4     | 3    | 1      | 0   | 0              |

## Findings Overview

| ID | Severity | Confidence | Category | File:Line | Title |
|----|----------|------------|----------|-----------|-------|
| F-001 | HIGH | 0.9 | sensitive-data-exposure | src/server.go:103 | Decrypted telemetry plaintext (GPS, speed, PII) logged at INFO level |
| F-002 | HIGH | 0.7 | command-injection | entrypoint.sh:29 | Unsanitized environment variables interpolated into sed patterns |
| F-003 | HIGH | 0.9 | resource-exhaustion | src/server.go:119 | Unused UDP listener socket created per packet leaks file descriptors |
| F-004 | MEDIUM | 0.6 | sensitive-data-exposure | src/server.go:99 | Full hex dump of failed-decryption packets logged |

---

## Detailed Findings

### F-001 — Decrypted telemetry plaintext (GPS, speed, PII) logged at INFO level

| Field | Value |
|-------|-------|
| **Severity** | HIGH |
| **Confidence** | 0.9 |
| **Category** | sensitive-data-exposure |
| **File** | `src/server.go` |
| **Lines** | 103, 169 |

**Description:**
On line 103, the full decrypted plaintext of every client telemetry packet is logged at INFO level via `logger.Infof()`. The plaintext contains real-time GPS coordinates, vehicle speed, OBD-II diagnostics, and potentially PII. Line 169 logs the same plaintext a second time after successfully forwarding the encrypted response back to the client. In production, INFO-level logs are typically shipped to centralized logging (CloudWatch, ELK, etc.), making the plaintext readable by anyone with log access. This effectively undoes the encryption-in-transit protection the proxy is designed to provide.

**Exploit Scenario:**
An attacker who gains read access to the log aggregation system (e.g., via a compromised Grafana dashboard, misconfigured S3 bucket for log storage, or lateral movement within the infrastructure) can extract real-time GPS coordinates, vehicle speeds, and OBD-II data for all tracked vehicles. No decryption key is needed — the data is in plaintext in the logs.

**Recommendation:**
Log only metadata at INFO level (source IP, packet size, success/failure). Move full plaintext logging to DEBUG or TRACE level, and ensure production deployments use INFO or above. Alternatively, log a truncated hash/fingerprint of the payload for debugging purposes.

---

### F-002 — Unsanitized environment variables interpolated into sed patterns

| Field | Value |
|-------|-------|
| **Severity** | HIGH |
| **Confidence** | 0.7 |
| **Category** | command-injection |
| **File** | `entrypoint.sh` |
| **Lines** | 29, 34, 40, 46 |

**Description:**
On lines 29, 34, 40, and 46 of `entrypoint.sh`, environment variables (`CHACHA_KEY`/`CHACHA20_KEY`, `LISTEN_PORT`, `DEST_ADDRESS`, `DEST_PORT`) are interpolated directly into `sed` substitution patterns without any sanitization or escaping. The sed delimiter is `/`, so any environment variable value containing `/` will break the sed command or alter its behavior. More critically, the `sed -i` command operates on `/tmp/config.yml`, and a crafted value containing sed metacharacters could inject arbitrary replacement content into `config.yml`.

**Exploit Scenario:**
An attacker who controls the container's environment variables (e.g., via a compromised CI/CD pipeline, Kubernetes ConfigMap, or Docker API access) sets `DEST_ADDRESS` to a value like `192.168.1.1\"/\nchacha_key: "attacker_controlled_key` to inject a different encryption key into the generated config.yml, causing the server to use an attacker-known key for all encryption/decryption.

**Recommendation:**
Validate all environment variables against strict patterns before interpolation (e.g., `DEST_ADDRESS` must match an IP/hostname regex, `LISTEN_PORT` must be numeric, `CHACHA_KEY` must be exactly 64 hex characters). Use `printf '%s'` with proper quoting or a templating tool (`envsubst`) instead of sed with unsanitized input.

---

### F-003 — Unused UDP listener socket created per packet leaks file descriptors

| Field | Value |
|-------|-------|
| **Severity** | HIGH |
| **Confidence** | 0.9 |
| **Category** | resource-exhaustion |
| **File** | `src/server.go` |
| **Lines** | 111–124 |

**Description:**
On lines 111-124, every successfully-decrypted packet handler goroutine creates a new UDP listener socket via `net.ListenUDP("udp", ":0")`. This socket (`listenConn`) is **never used** — the code subsequently creates a separate `forwardConn` via `net.DialUDP()` on line 127 and uses that for both sending and receiving. The `listenConn` consumes a file descriptor and an ephemeral port until the goroutine exits (`defer` on line 124). Under sustained traffic, file descriptor or ephemeral port exhaustion will crash the server.

**Exploit Scenario:**
A remote attacker sends a flood of validly-encrypted UDP packets (or a compromised tracker sends at high frequency). Each packet spawns a goroutine that allocates two UDP sockets instead of one. The unused `listenConn` sockets accumulate until the OS limit (typically 1024 or 65535 FDs) is hit, causing subsequent `net.ListenUDP` or `net.DialUDP` calls to fail and crashing the service.

**Recommendation:**
Remove the unused `listenConn` socket creation entirely (lines 111-124). The `forwardConn` on line 127 already handles both sending to and receiving from the backend.

> [!NOTE]
> Already identified as T5 in the project's THREAT_MODEL.md.

---

### F-004 — Full hex dump of failed-decryption packets logged

| Field | Value |
|-------|-------|
| **Severity** | MEDIUM |
| **Confidence** | 0.6 |
| **Category** | sensitive-data-exposure |
| **File** | `src/server.go` |
| **Line** | 99 |

**Description:**
On line 99, when decryption fails, the entire raw packet is hex-encoded and logged at WARN level: `rawHex := hex.EncodeToString(buf[:n])`. For a maximum UDP packet of 1500 bytes, this produces 3000 characters of hex per log line. An attacker can flood the listener port with garbage packets, each generating a WARN-level log entry with the full 3KB hex dump.

**Exploit Scenario:**
A remote attacker sends thousands of random 1500-byte UDP packets per second to the listener port. Each packet fails decryption and generates a ~3KB WARN log line. At 10,000 packets/second, this produces ~30MB/s of log output, filling disk and overwhelming the logging infrastructure.

**Recommendation:**
Log only a truncated prefix of the raw hex (e.g., first 32 bytes) and the total length. Rate-limit decryption failure logging (e.g., log one summary every N failures or per source IP per interval).

---

## Provenance

- **Mode:** static scan (single-pass, `--single` auto-selected for <15 source files)
- **Scoped from:** `THREAT_MODEL.md` sections 3 & 4
- **Skill:** `/vuln-scan`
- **Note:** These are static candidates, not verified. For rigorous verification, run `/triage`.
