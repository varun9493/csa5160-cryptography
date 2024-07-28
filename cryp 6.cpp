#include <stdio.h>
#include <string.h>
#include <ctype.h>
int modInverse(int a, int m) {
	  a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 0) {
            return x;
        }
    }
    return 1;
}
void affineDecrypt(char* ciphertext, char* plaintext, int a, int b) {
    int a_inv = modInverse(a, 26); 
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((a_inv * ((ciphertext[i] - 'A' - b + 26)) % 26) + 'A');
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((a_inv * ((ciphertext[i] - 'a' - b + 26)) % 26) + 'a');
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}
int main() {
    char ciphertext[100], plaintext[100];
    int a = 3, b = 15;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    affineDecrypt(ciphertext, plaintext, a, b);
    printf("Plaintext: %s\n", plaintext);
    return 0;
}

