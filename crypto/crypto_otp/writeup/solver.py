import base64

def otp_decrypt(cipher_b64, key):
    cipher = base64.b64decode(cipher_b64)
    return ''.join([chr(b ^ ord(key)) for b in cipher])

cipher = "IkMbNxZAQ04="  # Cipher Flag from Server
B64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

for key in B64_CHARS:
    decrypted = otp_decrypt(cipher, key)
    try:
        decoded = base64.b64decode(decrypted).decode()
        if "CHC{" in decoded:
            print(f"[+] Key Found: {key}")
            print(f"[+] Flag: {decoded}")
            break
    except:
        pass