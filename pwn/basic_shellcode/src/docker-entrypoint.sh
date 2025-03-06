#!/bin/sh

echo "CHC{FAKE_FLAG}" > "$FLAG_FILE"

DEFAULT_PORT=1337
DEFAULT_FILE="/app/target"


# Set default values if variables are not set
PORT="${PORT:-$DEFAULT_PORT}"
FILE="${FILE:-$DEFAULT_FILE}"

# Compile the C++ program
cc -m32 -std=gnu99 -g -O0 -fno-stack-protector  -z execstack -o $FILE /app/target.c

echo "Starting On Server via Socat"
socat TCP-LISTEN:$PORT,reuseaddr,fork SYSTEM:"(exec 2>&1; $FILE)"