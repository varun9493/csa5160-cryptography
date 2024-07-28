#include <stdio.h>
#include <stdlib.h>
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
int main() {
    int p = 61;
    int q = 59;
    int n = p * q;
    int e = 31;
    int plaintext_blocks[] = {123, 456, 789, 1011};
    int num_blocks = sizeof(plaintext_blocks) / sizeof(plaintext_blocks[0]);
    int ciphertext_blocks[num_blocks];
    printf("Public key: (e = %d, n = %d)\n", e, n);
    for (int i = 0; i < num_blocks; i++) {
        ciphertext_blocks[i] = rsa_encrypt(plaintext_blocks[i], e, n);
        printf("Plaintext block %d: %d\n", i, plaintext_blocks[i]);
        printf("Encrypted block %d: %d\n", i, ciphertext_blocks[i]);
    }
    return 0;
}

