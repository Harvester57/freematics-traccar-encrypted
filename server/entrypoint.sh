#!/bin/sh
set -e

# Path to the actual runtime configuration file
CONFIG_PATH="/tmp/config.yml"

# 1. Resolve base configuration file
if [ -f "/app/config.yml" ]; then
    echo "Found custom config.yml at /app/config.yml, using it as base."
    cp /app/config.yml "$CONFIG_PATH"
else
    echo "No base configuration found. Generating dynamic configuration."
    # Support both CHACHA_KEY and CHACHA20_KEY
    ACTUAL_KEY="${CHACHA_KEY:-$CHACHA20_KEY}"
    cat <<EOF > "$CONFIG_PATH"
chacha_key: "${ACTUAL_KEY:-d7f8dc39646486ffc9eafd165001f45f1ddf64328bf681159860c98a1c611569}"
destinations:
  ${LISTEN_PORT:-5170}:
    address: "${DEST_ADDRESS:-192.168.1.200}"
    port: ${DEST_PORT:-5171}
EOF
fi

# 2. Apply environment variable overrides if they are set
# Support both CHACHA_KEY and CHACHA20_KEY
ACTUAL_KEY="${CHACHA_KEY:-$CHACHA20_KEY}"

# sanitize_sed: escape the sed delimiter '/' and replacement metacharacter '&'
sanitize_sed() { printf '%s' "$1" | sed 's/[\/&]/\\&/g'; }

if [ -n "$ACTUAL_KEY" ]; then
    echo "Applying CHACHA_KEY override from environment..."
    sed -i "s/chacha_key:.*/chacha_key: \"$(sanitize_sed "$ACTUAL_KEY")\"/g" "$CONFIG_PATH"
fi

if [ -n "$LISTEN_PORT" ]; then
    echo "Applying LISTEN_PORT override to configuration: $LISTEN_PORT..."
    sed -i "s/^[[:space:]]*[0-9]\{2,\}:/  $(sanitize_sed "$LISTEN_PORT"):/g" "$CONFIG_PATH"
fi

if [ -n "$DEST_ADDRESS" ]; then
    echo "Applying DEST_ADDRESS override to configuration: $DEST_ADDRESS..."
    # Replace the address value in the config file
    sed -i "s/address:.*/address: \"$(sanitize_sed "$DEST_ADDRESS")\"/g" "$CONFIG_PATH"
fi

if [ -n "$DEST_PORT" ]; then
    echo "Applying DEST_PORT override to configuration: $DEST_PORT..."
    # Replace the port value in the config file
    sed -i "s/port:.*/port: $(sanitize_sed "$DEST_PORT")/g" "$CONFIG_PATH"
fi

# 3. Start the application passing the dynamic configuration file
echo "Starting Freematics Encrypt Server..."
exec /app/freematics-encrypt --config "$CONFIG_PATH"
