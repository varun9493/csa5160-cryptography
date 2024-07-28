#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int mod_inverse(int e, int phi) {
    int t = 0, new_t = 1;
    int r = phi, new_r = e;
    while (new_r != 0) {
        int quotient = r / new_r;
        int temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;
        int temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }
    if (r > 1) return -1;
    if (t < 0) t = t + phi;
    return t;
}
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
int rsa_encrypt(int plaintext, int e, int n) {
    return mod_exp(plaintext, e, n);
}
int rsa_decrypt(int ciphertext, int d, int n) {
    return mod_exp(ciphertext, d, n);
}
int main() {
    int p = 61;
    int q = 59;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 31;
    if (gcd(e, phi) != 1) {
        printf("e and phi are not coprime.\n");
        return 1;
    }
    int d = mod_inverse(e, phi);
    if (d == -1) {
        printf("Modular inverse does not exist.\n");
        return 1;
    }
    printf("Public key: (e = %d, n = %d)\n", e, n);
    printf("Private key: (d = %d, n = %d)\n", d, n);
    int plaintext = 123;
    printf("Plaintext: %d\n", plaintext);
    int ciphertext = rsa_encrypt(plaintext, e, n);
    printf("Encrypted text: %d\n", ciphertext);
    int decryptedtext = rsa_decrypt(ciphertext, d, n);
    printf("Decrypted text: %d\n", decryptedtext);
    return 0;
}

