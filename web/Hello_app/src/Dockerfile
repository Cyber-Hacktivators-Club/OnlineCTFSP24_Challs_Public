FROM python:3.10-slim

# Install necessary packages and clean up
RUN apt-get update && apt-get install -y --no-install-recommends \
    netcat-openbsd curl socat && \
    rm -rf /var/lib/apt/lists/*

# Create user and set working directory
RUN useradd -m CHC
WORKDIR /home/CHC

# Copy application files
COPY --chown=CHC:CHC app.py  docker-entrypoint.sh /home/CHC/

RUN sed -i 's/\r$//' /home/CHC/docker-entrypoint.sh
# Set appropriate permissions before switching user
RUN chmod +x /home/CHC/app.py /home/CHC/docker-entrypoint.sh
RUN pip install --no-cache-dir Flask
# Install Python dependencies

# Switch to non-root user
USER CHC

# Expose necessary port
EXPOSE 1337

# Set entrypoint script
ENTRYPOINT ["/home/CHC/docker-entrypoint.sh"]
