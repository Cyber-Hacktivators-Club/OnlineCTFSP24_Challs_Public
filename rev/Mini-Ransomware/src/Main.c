#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define ENCRYPTED_FILE "/flag.txt"
#define ENCRYPTED_FILE "flag.txt"
#define KEY_LENGTH 10

void customEncrypt(char *data, size_t dataLen, const char *key, size_t keyLen) {
    for (size_t i = 0; i < dataLen; i++) {
        // Apply Caesar cipher +13 first
        if ((data[i] >= 'A' && data[i] <= 'Z') || (data[i] >= 'a' && data[i] <= 'z')) {
            if (data[i] >= 'A' && data[i] <= 'Z') {
                data[i] = 'A' + (data[i] - 'A' + 13) % 26; // Uppercase shift
            } else {
                data[i] = 'a' + (data[i] - 'a' + 13) % 26; // Lowercase shift
            }
        }
        
        // Apply XOR encryption after Caesar cipher
        data[i] ^= key[i % keyLen];
    }
}

void generateKey(char *key, size_t length) {
    srand(0xC3Bad);
    for (size_t i = 0; i < length; i++) {
        key[i] = 'a' + (rand() % 26); // Generate lowercase letters 'a' to 'z'
    }
    key[length] = '\0';
}

int encryptFile(const char *filePath, const char *key, size_t keyLen) {
    FILE *file = fopen(filePath, "rb+");
    if (!file) {
        perror("Error opening file");
        return 0;
    }
    
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    
    char *buffer = (char *)malloc(fileSize);
    if (!buffer) {
        perror("Memory allocation error");
        fclose(file);
        return 0;
    }
    
    fread(buffer, 1, fileSize, file);
    customEncrypt(buffer, fileSize, key, keyLen);
    
    rewind(file);
    fwrite(buffer, 1, fileSize, file);
    
    free(buffer);
    fclose(file);
    return 1;
}

int main() {
    char encryptionKey[KEY_LENGTH + 1];
    generateKey(encryptionKey, KEY_LENGTH);
    
    if (encryptFile(ENCRYPTED_FILE, encryptionKey, KEY_LENGTH)) {
        printf("Your files have been encrypted. To decrypt them, you must pay the ransom.\n");
        printf("Contact us at hackers@cyberhacktivators.club to get the decryption key.\n");
        printf("Do not attempt to decrypt files without the key, or your data may be lost forever.\n");
    }
    return 0;
}