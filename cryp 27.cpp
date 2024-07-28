#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
unsigned long long rsa_encrypt(unsigned long long plaintext, unsigned long long e, unsigned long long n) {
    return mod_exp(plaintext, e, n);
}
unsigned long long rsa_decrypt(unsigned long long ciphertext, unsigned long long d, unsigned long long n) {
    return mod_exp(ciphertext, d, n);
}
int char_to_int(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    return -1;
}
char int_to_char(int i) {
    if (i >= 0 && i < 26) {
        return 'A' + i;
    }
    return '?';
}
int main() {
    unsigned long long p = 61;
    unsigned long long q = 53;
    unsigned long long n = p * q;
    unsigned long long phi = (p - 1) * (q - 1);
    unsigned long long e = 17;
    unsigned long long d = 0;
    unsigned long long k = 1;
    while ((1 + k * phi) % e != 0) {
        k++;
    }
    d = (1 + k * phi) / e;
    printf("Public key: (e = %llu, n = %llu)\n", e, n);
    printf("Private key: (d = %llu, n = %llu)\n", d, n);
    char plaintext[] = "HELLO";
    int length = strlen(plaintext);
    unsigned long long ciphertext[length];
    unsigned long long decryptedtext[length];
    printf("Plaintext: %s\n", plaintext);
    for (int i = 0; i < length; i++) {
        int plaintext_int = char_to_int(plaintext[i]);
        ciphertext[i] = rsa_encrypt(plaintext_int, e, n);
        printf("Encrypted char %c: %llu\n", plaintext[i], ciphertext[i]);
    }
    for (int i = 0; i < length; i++) {
        decryptedtext[i] = rsa_decrypt(ciphertext[i], d, n);
        printf("Decrypted int %llu: %c\n", decryptedtext[i], int_to_char(decryptedtext[i]));
    }
    printf("Decrypted text: ");
    for (int i = 0; i < length; i++) {
        printf("%c", int_to_char(decryptedtext[i]));
    }
    printf("\n");
    return 0;
}

