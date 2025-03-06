#!/bin/sh

FLAG_FILE="/home/CHC/flag.txt"


echo "CHC{FAKE_FLAG}" > "$FLAG_FILE"

# Run Python script to encode the flag and modify main.cpp
echo "Starting web module..."
exec  python /home/CHC/app.py  