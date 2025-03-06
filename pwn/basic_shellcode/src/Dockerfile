FROM ubuntu:latest

# Install dependencies
RUN dpkg --add-architecture i386 && apt update && apt install -y \
    gcc g++ libc6-dev socat build-essential \
    gcc-multilib g++-multilib libc6-dev-i386 \
    && rm -rf /var/lib/apt/lists/*
# Set working directory
WORKDIR /app

# Copy source files
COPY target.c /app/target.c
COPY docker-entrypoint.sh /app/entrypoint.sh
RUN sed -i 's/\r$//' /app/entrypoint.sh
# Set executable permissions
RUN chmod +x /app/entrypoint.sh

# Expose the port
EXPOSE 1337

# Set entrypoint
ENTRYPOINT ["/app/entrypoint.sh"]
