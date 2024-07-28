#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_LENGTH 26
void generateCipherSequence(char keyword[], char cipherSeq[]) {
    int dict[ALPHABET_LENGTH] = {0};
    int i, j = 0, k = 0;
    int len = strlen(keyword);
    for (i = 0; i < len; i++) {
        char ch = toupper(keyword[i]);
        if (isalpha(ch) && dict[ch - 'A'] == 0) {
            cipherSeq[j++] = ch;
            dict[ch - 'A'] = 1;
        }
    }
    for (i = 0; i < ALPHABET_LENGTH; i++) {
        if (dict[i] == 0) {
            cipherSeq[j++] = 'A' + i;
        }
    }
    cipherSeq[j] = '\0';
}
void encrypt(char plaintext[], char cipherSeq[], char ciphertext[]) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        char ch = toupper(plaintext[i]);
        if (isalpha(ch)) {
            ciphertext[i] = cipherSeq[ch - 'A'];
        } else {
            ciphertext[i] = ch;
        }
    }
    ciphertext[i] = '\0';
}
int main() {
    char keyword[100], plaintext[100];
    char cipherSeq[ALPHABET_LENGTH + 1];
    char ciphertext[100];
    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    generateCipherSequence(keyword, cipherSeq);
    printf("Generated cipher sequence: %s\n", cipherSeq);
    encrypt(plaintext, cipherSeq, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);
    return 0;
}

