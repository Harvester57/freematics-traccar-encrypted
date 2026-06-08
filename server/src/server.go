package main

import (
	"encoding/hex"
	"flag"
	"fmt"
	"github.com/sirupsen/logrus"
	"gopkg.in/yaml.v2"
	"net"
	"os"
	"server/encryption"
	"server/logging"
	"time"
)

type Config struct {
	Destinations map[string]Destination `yaml:"destinations"`
	ChachaKey    string                 `yaml:"chacha_key"`
}

type Destination struct {
	Address string `yaml:"address"`
	Port    int    `yaml:"port"`
}

func main() {
	configFile := flag.String("config", "", "Path to the configuration file")
	flag.Parse()

	logLevel := logrus.InfoLevel
	if os.Getenv("LOG_LEVEL") == "debug" || os.Getenv("DEBUG") == "true" || os.Getenv("DEBUG") == "1" {
		logLevel = logrus.DebugLevel
	}
	logging.InitLogger(logLevel)
	logger := logging.GetLogger()

	if *configFile == "" {
		logger.Fatalln("Provide a configuration file via --config")
	}

	data, err := os.ReadFile(*configFile)
	if err != nil {
		logger.Fatalln("Error reading the configuration file:", err)
	}

	var config Config
	err = yaml.Unmarshal(data, &config)
	if err != nil {
		logger.Fatalln("Error parsing the configuration file:", err)
	}

	// Validate chacha key
	if len(config.ChachaKey) != 64 {
		logger.Fatalln("Invalid chacha_key. Should be 64 characters long")
	}

	// Validate destinations
	for port, dest := range config.Destinations {
		if dest.Address == "" || dest.Port == 0 {
			logger.Fatalln("Invalid destination for port %s", port)
		}
	}

	key, err := hex.DecodeString(config.ChachaKey)
	if err != nil {
		logger.Fatalln("Invalid chacha_key. Must be valid hexadecimal:", err)
	}

	for port, dest := range config.Destinations {
		go func(port string, dest Destination) {
			addr, err := net.ResolveUDPAddr("udp", ":"+port)
			if err != nil {
				logger.Fatalln("Error resolving address:", err)
				return
			}

			conn, err := net.ListenUDP("udp", addr)
			if err != nil {
				logger.Fatalln("Error listening on UDP:", err)
				return
			}
			defer conn.Close()

			logger.Infof("Listening on 0.0.0.0:%s", port)

			for {
				buf := make([]byte, 1500) // 1500 is the standard internet MTU.
				n, addr, err := conn.ReadFromUDP(buf)
				if err != nil {
					logger.Fatalf(formatLogMsg(addr.IP.String(), dest.Address, dest.Port, fmt.Sprintf("Error reading from UDP: %s", err)))
				}

				// Handle the message.
				go func(addr *net.UDPAddr, buf []byte, n int) {
					// Do the decryption.
					if len(buf[:n]) == 0 {
						return // Empty message — nothing to process.
					}

					plaintext, err := encryption.Decrypt(key, buf[:n])
					if err != nil {
						const maxHexPreview = 32 // 16 bytes → 32 hex chars
						rawHex := hex.EncodeToString(buf[:n])
						preview := rawHex
						if len(preview) > maxHexPreview {
							preview = preview[:maxHexPreview] + "..."
						}
						logger.Warnf(formatLogMsg(addr.IP.String(), dest.Address, dest.Port, fmt.Sprintf("Dropping message: decryption failed: %s. Length: %d, Preview: %s", err, n, preview)))
						return // Drop the message — never forward unauthenticated data.
					}

					logger.Infof(formatLogMsg(addr.IP.String(), dest.Address, dest.Port, fmt.Sprintf("Successfully decrypted client packet (%d bytes)", len(plaintext))))

					forwardAddr, err := net.ResolveUDPAddr("udp", fmt.Sprintf("%s:%d", dest.Address, dest.Port))
					if err != nil {
						logger.Fatalln("Error resolving forward address:", err)
						return
					}


					// Dial the backend server without binding a local address.
					forwardConn, err := net.DialUDP("udp", nil, forwardAddr)
					if err != nil {
						logger.Fatalln("Error dialing to forward address:", err)
						return
					}
					defer forwardConn.Close()

					// Forward the plaintext to the backend.
					_, err = forwardConn.Write(plaintext)
					if err != nil {
						logger.Errorf(formatLogMsg(addr.IP.String(), dest.Address, dest.Port, fmt.Sprintf("Error forwarding message: %s", err)))
						return
					}

					// Read the response from the backend with a timeout to prevent infinite blocking.
					err = forwardConn.SetReadDeadline(time.Now().Add(5 * time.Second))
					if err != nil {
						logger.Errorf(formatLogMsg(addr.IP.String(), dest.Address, dest.Port, fmt.Sprintf("Error setting read deadline: %s", err)))
						return
					}

					backendResponse := make([]byte, 1500)
					n, err = forwardConn.Read(backendResponse)
					if err != nil {
						logger.Errorf(formatLogMsg(addr.IP.String(), dest.Address, dest.Port, fmt.Sprintf("Error reading response from backend server: %s", err)))
						return
					}

					// Encrypt the backend's response.
					encryptedBackendResponse, err := encryption.Encrypt(key, backendResponse[:n])
					if err != nil {
						logger.Errorf(formatLogMsg(addr.IP.String(), dest.Address, dest.Port, fmt.Sprintf("Error encrypting response: %s", err)))
						return
					}

					// Forward the encrypted backend response to the client.
					_, err = conn.WriteToUDP(encryptedBackendResponse, addr)
					if err != nil {
						logger.Errorf(formatLogMsg(addr.IP.String(), dest.Address, dest.Port, fmt.Sprintf("Error forwarding response to client: %s", err)))
						return
					}

					logger.Infof(formatLogMsg(addr.IP.String(), dest.Address, dest.Port, fmt.Sprintf("Successfully forwarded encrypted response back to client (%d bytes)", len(encryptedBackendResponse))))
				}(addr, buf, n)
			}
		}(port, dest)
	}
	select {}
}

func formatLogMsg(srcIp string, destIp string, destPort int, msg string) string {
	return fmt.Sprintf("%s -> %s:%d -- %s", srcIp, destIp, destPort, msg)
}
