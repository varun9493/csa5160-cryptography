#include <stdio.h>
#include <string.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int isValidA(int a) {
    return gcd(a, 26) == 1;
}
void affineEncrypt(char* plaintext, char* ciphertext, int a, int b) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((a * (plaintext[i] - 'A') + b) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((a * (plaintext[i] - 'a') + b) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}
int main() {
    char plaintext[100], ciphertext[100];
    int a, b;
    printf("Enter the value of a (must be coprime with 26): ");
    scanf("%d", &a);
    while (!isValidA(a)) {
        printf("Invalid value for a. Please enter a value that is coprime with 26: ");
        scanf("%d", &a);
    }
    printf("Enter the value of b: ");
    scanf("%d", &b);
    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);
    affineEncrypt(plaintext, ciphertext, a, b);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}


