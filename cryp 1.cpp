#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void encrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            text[i] = (c - base + shift) % 26 + base;
        }
    }
}
int main() {
    char text[100];
    int shift;
    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    printf("Enter the shift value: ");
    scanf("%d", &shift);
    encrypt(text, shift);
    printf("Encrypted text: %s\n", text);
    return 0;
}

