# Use Python Alpine as the base image
FROM python:3.11-alpine

# Set working directory
WORKDIR /app

# Install required dependencies in a single RUN command
RUN apk add --no-cache bash curl g++

# Copy dependency file first for better caching
COPY web/requirements.txt /app/web/requirements.txt

# Install Python dependencies efficiently
RUN pip install --no-cache-dir --upgrade pip \
    && pip install -r /app/web/requirements.txt

# Copy the rest of the application files
COPY web /app/web
RUN mkdir /app/dist
COPY docker-entrypoint.sh /docker-entrypoint.sh

# Set execute permissions for necessary scripts
RUN chmod +x /docker-entrypoint.sh

# Expose port 8080
EXPOSE 8080

# Copy the challenge file (C++ source code)
COPY encrypt_flag.py /app/encrypt_flag.py
RUN apk add --no-cache \
    gcc \
    g++ \
    musl-dev \
    make \
    upx
COPY main.c /app/main.c


# Set entrypoint
ENTRYPOINT ["/docker-entrypoint.sh"]
