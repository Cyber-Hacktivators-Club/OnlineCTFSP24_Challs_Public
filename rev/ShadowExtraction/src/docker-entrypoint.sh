#!/bin/sh

FLAG_FILE="/flag.txt"

echo "CHC{FAKE_FLAG}" > "$FLAG_FILE"

# Compile the C++ program
gcc /app/main.c -o /app/shadows -fno-stack-protector -z execstack -no-pie
# strip /app/shadows
upx --best --lzma /app/shadows -o /app/dist/shadows


echo "Starting web module..."
exec  python3 /app/web/main.py  