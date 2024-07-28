#include <stdio.h>
#include <stdint.h>
#include <string.h>
typedef uint64_t ull;
typedef uint8_t uint8;
void des_encrypt(ull plaintext, ull* ciphertext, ull key);
void des_decrypt(ull ciphertext, ull* plaintext, ull key);
void triple_des_encrypt(ull plaintext, ull* ciphertext, ull k1, ull k2);
void triple_des_decrypt(ull ciphertext, ull* plaintext, ull k1, ull k2);
void xor_blocks(ull* block1, ull block2);
void cbc_encrypt(ull* plaintext, ull* ciphertext, int num_blocks, ull iv, ull k1, ull k2);
void cbc_decrypt(ull* ciphertext, ull* plaintext, int num_blocks, ull iv, ull k1, ull k2);
int main() {
    ull plaintext[] = {0x0123456789ABCDEF, 0x23456789ABCDEF01};
    ull ciphertext[2];
    ull decrypted[2];
    ull iv = 0xAABBCCDDEEFF0011;
    ull key1 = 0x133457799BBCDFF1;
    ull key2 = 0x1A1B1C1D1E1F0102;
    printf("Plaintext blocks:\n");
    for (int i = 0; i < 2; i++) {
        printf("%016llX\n", plaintext[i]);
    }
    cbc_encrypt(plaintext, ciphertext, 2, iv, key1, key2);
    printf("\nCiphertext blocks:\n");
    for (int i = 0; i < 2; i++) {
        printf("%016llX\n", ciphertext[i]);
    }
    cbc_decrypt(ciphertext, decrypted, 2, iv, key1, key2);
    printf("\nDecrypted blocks:\n");
    for (int i = 0; i < 2; i++) {
        printf("%016llX\n", decrypted[i]);
    }
    return 0;
}
void des_encrypt(ull plaintext, ull* ciphertext, ull key) {
    *ciphertext = plaintext ^ key;
}
void des_decrypt(ull ciphertext, ull* plaintext, ull key) {
    *plaintext = ciphertext ^ key;
}
void triple_des_encrypt(ull plaintext, ull* ciphertext, ull k1, ull k2) {
    ull temp;
    des_encrypt(plaintext, &temp, k1);
    des_decrypt(temp, &temp, k2);
    des_encrypt(temp, ciphertext, k1);
}
void triple_des_decrypt(ull ciphertext, ull* plaintext, ull k1, ull k2) {
    ull temp;
    des_decrypt(ciphertext, &temp, k1);
    des_encrypt(temp, &temp, k2);
    des_decrypt(temp, plaintext, k1);
}
void xor_blocks(ull* block1, ull block2) {
    *block1 ^= block2;
}
void cbc_encrypt(ull* plaintext, ull* ciphertext, int num_blocks, ull iv, ull k1, ull k2) {
    ull prev_cipher = iv;
    for (int i = 0; i < num_blocks; i++) {
        xor_blocks(&plaintext[i], prev_cipher);
        triple_des_encrypt(plaintext[i], &ciphertext[i], k1, k2);
        prev_cipher = ciphertext[i];
    }
}
void cbc_decrypt(ull* ciphertext, ull* plaintext, int num_blocks, ull iv, ull k1, ull k2) {
    ull prev_cipher = iv;
    ull temp;
    for (int i = 0; i < num_blocks; i++) {
        triple_des_decrypt(ciphertext[i], &temp, k1, k2);
        xor_blocks(&temp, prev_cipher);
        plaintext[i] = temp;
        prev_cipher = ciphertext[i];
    }
}
