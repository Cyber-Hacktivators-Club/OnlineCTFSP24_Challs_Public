#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ptrace.h>

#define FLAG_SIZE 35  // Adjust this based on the actual flag length
#define XOR_KEY 0x5F   // Simple XOR encryption key

unsigned char encrypted_flag[FLAG_SIZE] = {0x1C, 0x17, 0x1C, 0x24, 0x3E, 0x3D, 0x3C, 0x22};

// Correct passphrase to unlock the flag
const char *correct_passphrase = "h4x0r_shad0w_key";

// Anti-debugging: Check if debugger is attached
void anti_debugging() {
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1) {
        printf("Debugger detected! Exiting...\n");
        exit(1);
    }

    // Additional trick: Check parent process ID (PPID)
    if (getppid() != 1) {
        printf("Suspicious environment detected! Exiting...\n");
        exit(1);
    }
}

// XOR decryption routine
void decrypt_flag(char *buffer, size_t length) {
    for (size_t i = 0; i < length; i++) {
        buffer[i] ^= XOR_KEY;  // XOR decryption
    }
}

// Self-decrypting payload
void execute_payload() {
    unsigned char payload[] = { 0x55 ^ 0xAA, 0x48 ^ 0xAA, 0x89 ^ 0xAA, 0xE5 ^ 0xAA, 0xC3 ^ 0xAA };

    void *exec_mem = mmap(NULL, sizeof(payload), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (exec_mem == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    for (size_t i = 0; i < sizeof(payload); i++) {
        ((unsigned char *)exec_mem)[i] = payload[i] ^ 0xAA;
    }

    ((void(*)())exec_mem)();
}

int main() {
    char user_input[32];

    // Anti-debugging check
    anti_debugging();

    printf("Enter passphrase: ");
    scanf("%31s", user_input);

    if (strcmp(user_input, correct_passphrase) == 0) {
        char *decrypted_flag = (char *)malloc(FLAG_SIZE);
        if (!decrypted_flag) {
            printf("Memory allocation failed!\n");
            return 1;
        }

        memcpy(decrypted_flag, encrypted_flag, FLAG_SIZE);
        decrypt_flag(decrypted_flag, FLAG_SIZE);

        printf("Access Granted! But where is the flag?\n");

        execute_payload(); // Hidden execution

    } else {
        printf("Wrong passphrase! Try again.\n");
    }

    return 0;
}
