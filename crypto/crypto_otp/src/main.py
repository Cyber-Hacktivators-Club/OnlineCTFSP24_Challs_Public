import socket
import threading
import base64
import random
import string
import re

B64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

def get_flag():
    try:
        with open('/flag.txt', 'r') as f:
            return f.read().strip()
    except Exception as e:
        return "FLAG_NOT_FOUND"

FLAG = get_flag()


def otp_encrypt_decrypt(data, key):
    return bytes([b ^ ord(key) for b in data])


def handle_client(client_socket):
    # Send Welcome Message
    client_socket.send(b"Welcome to Crypto Challenge!\n")
    client_socket.send(b"\nChoose any Base64 character as your OTP key:\n")

    # Receive user's key
    key = client_socket.recv(1024).strip().decode()

    if len(key) != 1 or key not in B64_CHARS:
        client_socket.send(b"Invalid key! Use exactly **ONE** Base64 character.\n")
        client_socket.close()
        return

    # Encrypt the Flag
    encoded_flag = base64.b64encode(FLAG.encode())
    encrypted_flag = otp_encrypt_decrypt(encoded_flag, key)
    encrypted_b64 = base64.b64encode(encrypted_flag)

    client_socket.send(f"\nCipher Flag = {encrypted_b64.decode()}\n".encode())
    client_socket.send(b"\nNow input any Base64 string to encrypt it with your key!\n")

    while True:
        try:
            client_socket.send(b"\nEnter your Base64 message: ")
            user_input = client_socket.recv(1024).strip().decode()

            if user_input == "":
                client_socket.send(b"Goodbye!\n")
                client_socket.close()
                break

            try:
                user_data = base64.b64decode(user_input)
                encrypted_input = otp_encrypt_decrypt(user_data, key)
                encrypted_input_b64 = base64.b64encode(encrypted_input)

                client_socket.send(f"Encrypted Result = {encrypted_input_b64.decode()}\n".encode())
            except:
                client_socket.send(b"Invalid Base64 String!\n")

        except:
            client_socket.close()
            break


def main():
    host = "0.0.0.0"
    port = 8080

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen(5)

    print(f"Server running on {host}:{port} 🚀")

    while True:
        client, addr = server.accept()
        print(f"[+] Connection from {addr}")
        client_thread = threading.Thread(target=handle_client, args=(client,))
        client_thread.start()


if __name__ == "__main__":
    main()