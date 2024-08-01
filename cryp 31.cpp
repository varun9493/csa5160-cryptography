#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/aes.h>
#define BLOCK_SIZE 16
#define AES_KEY_SIZE 16
void AES_Encrypt(uint8_t* plaintext, uint8_t* key, uint8_t* ciphertext);
void GenerateSubkeys(uint8_t* key, uint8_t* K1, uint8_t* K2);
void LeftShiftOneBit(uint8_t* input, uint8_t* output);
void XOR_128(uint8_t* a, uint8_t* b, uint8_t* out);
void PrintHex(uint8_t* array, int len);
int main() {
    uint8_t key[AES_KEY_SIZE] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x9c, 0xc5, 0x1b, 0xe4, 0x1f, 0xa0
    };
    uint8_t K1[BLOCK_SIZE], K2[BLOCK_SIZE];
    GenerateSubkeys(key, K1, K2);
    printf("Subkey K1: ");
    PrintHex(K1, BLOCK_SIZE);
    printf("Subkey K2: ");
    PrintHex(K2, BLOCK_SIZE);
    return 0;
}
void AES_Encrypt(uint8_t* plaintext, uint8_t* key, uint8_t* ciphertext) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);
    AES_encrypt(plaintext, ciphertext, &aesKey);
}
void GenerateSubkeys(uint8_t* key, uint8_t* K1, uint8_t* K2) {
    uint8_t L[BLOCK_SIZE] = {0};
    uint8_t Z[BLOCK_SIZE] = {0};
    uint8_t Rb[BLOCK_SIZE] = {
        0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    AES_Encrypt(Z, key, L);
    if ((L[0] & 0x80) == 0) {
        LeftShiftOneBit(L, K1);
    } else {
        uint8_t temp[BLOCK_SIZE];
        LeftShiftOneBit(L, temp);
        XOR_128(temp, Rb, K1);
    }
    if ((K1[0] & 0x80) == 0) {
        LeftShiftOneBit(K1, K2);
    } else {
        uint8_t temp[BLOCK_SIZE];
        LeftShiftOneBit(K1, temp);
        XOR_128(temp, Rb, K2);
    }
}
void LeftShiftOneBit(uint8_t* input, uint8_t* output) {
    int i;
    uint8_t overflow = 0;
    for (i = BLOCK_SIZE - 1; i >= 0; i--) {
        output[i] = (input[i] << 1) | overflow;
        overflow = (input[i] & 0x80) ? 1 : 0;
    }
}
void XOR_128(uint8_t* a, uint8_t* b, uint8_t* out) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = a[i] ^ b[i];
    }
}
void PrintHex(uint8_t* array, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x", array[i]);
    }
    printf("\n");
}
