# Threat Model: Freematics Traccar Decryption Server

## 1. System context

The `freematics-traccar-encrypted` proxy is a transparent, lightweight Go-based UDP proxy designed to secure the Freematics UDP telemetry protocol. By default, the protocol transmits sensitive vehicle diagnostics, speed, and GPS location in plaintext over UDP. This proxy acts as a secure intermediary on the server side: it listens on specified UDP ports, accepts encrypted UDP packets from ESP32 tracker clients, decrypts and authenticates them using the ChaCha20-Poly1305 AEAD algorithm with a 256-bit shared key, and forwards the resulting plaintext telemetry to a backend Traccar server. It also performs the reverse operation, encrypting response packets from the Traccar server and sending them back to the client trackers.

The codebase is extremely compact, containing a single main application file (`server.go`), a helper package for ChaCha20-Poly1305 encryption (`decrypt.go` and `encrypt.go`), and structured logging configuration (`logging.go`). The server is packaged in a dual-stage Docker container (using Alpine 3.23 as the base image for runtime) and is designed to run in a secure private network as a non-privileged user. It is typically deployed as a standalone native binary, inside a Docker container, or via Docker Compose.

## 2. Assets

| asset | description | sensitivity |
|---|---|---|
| Symmetric Encryption Key (chacha_key) | The 256-bit key used to encrypt and decrypt UDP packets between clients and the server. | critical |
| Client Telemetry Plaintext | Sensitive real-time OBD-II diagnostics, fuel metrics, speed, and GPS location data. | high |
| Server Process Availability | The service availability of the proxy handling incoming client telemetry traffic. | medium |
| Backend Traccar Interface | The UDP input interface of the backend Traccar server, which expects validated telemetry. | high |

## 3. Entry points & trust boundaries

| entry_point | description | trust_boundary | reachable_assets |
|---|---|---|---|
| UDP Listener Port | UDP socket listening on a configured port (default 5170) to receive encrypted telemetry packets from clients. | untrusted internet → server process memory | Symmetric Encryption Key (chacha_key), Client Telemetry Plaintext, Server Process Availability |
| UDP Backend Client Port | UDP client socket dialing and receiving packets from the backend Traccar server (default 5171). | backend server → server process memory | Client Telemetry Plaintext, Server Process Availability, Backend Traccar Interface |
| YAML Configuration File | YAML configuration file (config.yml) containing destinations and the symmetric ChaCha20 key. | local filesystem → server configuration state | Symmetric Encryption Key (chacha_key), Server Process Availability |
| Docker Entrypoint Environment Variables | Environment variables (CHACHA_KEY, CHACHA20_KEY, LISTEN_PORT, DEST_ADDRESS, DEST_PORT) used to generate the server's runtime YAML configuration. | container environment → config.yml generation | Symmetric Encryption Key (chacha_key), Server Process Availability |

## 4. Threats

| id | threat | actor | surface | asset | impact | likelihood | status | controls | evidence |
|---|---|---|---|---|---|---|---|---|---|
| T1 | Data tampering and spoofing via injection of unauthenticated UDP payloads bypassing decryption | remote_unauth | UDP Listener Port | Client Telemetry Plaintext, Backend Traccar Interface | critical | likely | mitigated | The proxy drops unauthenticated messages immediately and only forwards successfully decrypted payloads. | security_analysis.md:CRITICAL-2, commit f7eef06 |
| T2 | Compromise of symmetric encryption key via exposure in plaintext configurations or environment logs | local_admin | YAML Configuration File, Docker Entrypoint Environment Variables | Symmetric Encryption Key (chacha_key) | critical | possible | risk_accepted | Risk accepted by owner; environment-based key injection is acceptable. Length/hex checks on startup. | security_analysis.md:CRITICAL-3 |
| T3 | Exposure of the encryption key in container environment variables via host process listing or container inspect | local_user | Docker Entrypoint Environment Variables | Symmetric Encryption Key (chacha_key) | critical | possible | risk_accepted | Risk accepted by owner; environment-based key injection is acceptable. Minimal container runtime. | |
| T4 | Denial of service via UDP flooding leading to resource exhaustion (CPU/Memory) or socket exhaustion | remote_unauth | UDP Listener Port | Server Process Availability | high | likely | unmitigated | Port is exposed behind a NATed router with no external firewall filtering. | |
| T5 | Resource / file descriptor exhaustion due to unused UDP listener socket leak per incoming client packet | remote_unauth | UDP Backend Client Port | Server Process Availability | high | possible | unmitigated | none | |
| T6 | Replay attacks of historical client telemetry packets leading to spoofed coordinates on Traccar backend | remote_unauth | UDP Listener Port | Client Telemetry Plaintext, Backend Traccar Interface | medium | possible | unmitigated | Replay protection requested by owner but not yet implemented in code or protocol. | |
| T7 | Denial of service or incorrect decoding due to silent failure to parse hexadecimal configuration keys | local_admin | YAML Configuration File | Symmetric Encryption Key (chacha_key), Server Process Availability | medium | possible | mitigated | Go server checks error return values of hex.DecodeString on configuration parsing and fails early if invalid. | security_analysis.md:INFO-3, commit f7eef06 |

## 5. Deprioritized

| threat | reason |
|---|---|
| Repudiation | Not applicable; client tracking units transmit unilateral diagnostics logs, and non-repudiation is not a system requirement. |
| Local Privilege Escalation | Once inside the container, the minimal Alpine filesystem and statically linked non-root Go server contain no known local privilege escalation paths. |
| External Secret Management | Key storage in secrets managers (e.g. Docker Secrets/Vault) is deprioritized; environment-based configuration variables are accepted as secure enough for the target deployment context. |

## 6. Open questions

- **None** - All initial open questions regarding server network exposure, replay attack requirements, and key storage/secrets have been resolved during the owner interview.

## 7. Provenance

- mode: bootstrap-then-interview
- date: 2026-06-05
- target: c:\Users\Florian\OneDrive\Documents\Dev\freematics-traccar-encrypted\server @ 71f146f
- inputs: security_analysis.md, git-log mined, owner interview
- owner: Florian

## 8. Recommended mitigations

| mitigation | threat_ids | closes_class | effort |
|---|---|---|---|
| Integrate sequence numbers or high-resolution timestamps within the encrypted payload structure and enforce freshness checks on the proxy server. | T6 | yes | M |
| Remove the unused listenConn socket instantiation in server.go (lines 111-124) to eliminate the port/descriptor leak. | T5 | yes | S |
| Configure firewall rules on the backend Traccar server to only accept UDP packets from the proxy's IP address. | T1 | yes | S |
| Implement rate-limiting on incoming UDP traffic or configure OS-level iptables/rate-limits to restrict packet frequency per client IP. | T4 | yes | M |
| Enforce strict key quality validations (e.g. check key is not all zeros or repeating bytes) during config parsing. | T7 | partial | S |
