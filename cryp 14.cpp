#include <stdio.h>
#include <string.h>
void encrypt(const char* plaintext, const int* keyStream, char* ciphertext) {
    int length = strlen(plaintext);
    for (int i = 0; i < length; i++) {
        if (plaintext[i] != ' ') {
            ciphertext[i] = ((plaintext[i] - 'a' + keyStream[i]) % 26) + 'a';
        } else {
            ciphertext[i] = ' ';
        }
    }
    ciphertext[length] = '\0';
}
void decrypt(const char* ciphertext, const int* keyStream, char* plaintext) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] != ' ') {
            plaintext[i] = ((ciphertext[i] - 'a' - keyStream[i] + 26) % 26) + 'a';
        } else {
            plaintext[i] = ' ';
        }
    }
    plaintext[length] = '\0';
}
void findKey(const char* desiredPlaintext, const char* ciphertext, int* keyStream) {
    int length = strlen(desiredPlaintext);
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] != ' ') {
            keyStream[i] = (ciphertext[i] - desiredPlaintext[i] + 26) % 26;
        } else {
            keyStream[i] = 0;
        }
    }
}
int main() {
    const char* plaintext = "send more money";
    const int keyStream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[50];
    encrypt(plaintext, keyStream, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    const char* desiredPlaintext = "cash not needed";
    int newKeyStream[50];
    findKey(desiredPlaintext, ciphertext, newKeyStream);
    printf("New key stream: ");
    for (int i = 0; i < strlen(desiredPlaintext); i++) {
        printf("%d ", newKeyStream[i]);
    }
    printf("\n");
    char decryptedText[50];
    decrypt(ciphertext, newKeyStream, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);
    return 0;
}

