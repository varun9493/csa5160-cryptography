#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void encrypt(char *plaintext, char *key) {
    char alphabet[30] ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = plaintext[i];
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            int index = toupper(c) - 'A';
            plaintext[i] = islower(c) ? tolower(key[index]) : key[index];
        }
    }
}
int main() {
    char plaintext[100];
    char key[27];
    printf("Enter a string to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    printf("Enter the 26-character key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    if (strlen(key) != 26) {
        printf("Key must be 26 characters long.\n");
        return 1;
    }
    encrypt(plaintext, key);
    printf("Encrypted text: %s\n", plaintext);
    return 0;
}

