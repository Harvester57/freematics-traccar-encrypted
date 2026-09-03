# ==============================================================================
# STAGE 1: Build the Go binary
# ==============================================================================
FROM golang:1.27-alpine@sha256:cf6fca6641884b8433441b2b0652976f975e1d0fdd26d177eaaf8596087f3125 AS builder

# Install build dependencies, git, and certificates
RUN apk update && apk add --no-cache git ca-certificates tzdata

# Set the working directory inside the builder container
WORKDIR /app

# Copy the go.mod and go.sum files first to leverage Docker's caching mechanism
COPY src/go.mod src/go.sum ./

# Download all Go module dependencies
RUN go mod download

# Copy the rest of the application source code
COPY src/ .

# Build the Go application:
# - CGO_ENABLED=0 produces a statically linked binary
# - GOOS=linux target Linux environment
# - -trimpath removes all file system paths from the compiled binary
# - -ldflags "-s -w" strips debugging information and symbols to reduce binary size
RUN CGO_ENABLED=0 GOOS=linux go build -v -trimpath -ldflags "-s -w" -o freematics-encrypt .

# ==============================================================================
# STAGE 2: Create the minimal runtime container
# ==============================================================================
FROM alpine:3.24@sha256:28bd5fe8b56d1bd048e5babf5b10710ebe0bae67db86916198a6eec434943f8b

# Import ca-certificates and tzdata for SSL/TLS and timezones
RUN apk add --no-cache ca-certificates tzdata

# Create a secure, non-privileged system user and group to run the server
RUN addgroup -S appgroup && adduser -S appuser -G appgroup

WORKDIR /app

# Copy the statically compiled binary from the builder stage
COPY --from=builder /app/freematics-encrypt /app/freematics-encrypt

# Copy the sample config and entrypoint script
COPY config.sample.yml /app/config.sample.yml
COPY entrypoint.sh /app/entrypoint.sh

# Ensure the entrypoint script is executable
RUN chmod +x /app/entrypoint.sh

# Set ownership of the application directory to the non-privileged user
RUN chown -R appuser:appgroup /app

# Run the container as the non-privileged user
USER appuser

# Document that the container listens on port 5170 UDP
EXPOSE 5170/udp

# Set the custom entrypoint script
ENTRYPOINT ["/app/entrypoint.sh"]
