# ==============================================================================
# STAGE 1: Build the Go binary
# ==============================================================================
FROM golang:1.26-alpine@sha256:91eda9776261207ea25fd06b5b7fed8d397dd2c0a283e77f2ab6e91bfa71079d AS builder

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
FROM alpine:3.23@sha256:5b10f432ef3da1b8d4c7eb6c487f2f5a8f096bc91145e68878dd4a5019afde11

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
