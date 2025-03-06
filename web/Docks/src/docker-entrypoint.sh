#!/bin/sh

FLAG_FILE="/flag.txt"


echo "CHC{FAKE_FLAG}" > "$FLAG_FILE"

# Run Python script to encode the flag and modify main.cpp
echo "Starting web module..."
exec  apache2-foreground  