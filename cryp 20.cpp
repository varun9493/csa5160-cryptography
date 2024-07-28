#include <stdio.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <string.h>
void print_data(const char *title, const void* data, int len);
int main() {
    unsigned char key[AES_BLOCK_SIZE];
    unsigned char input[2 * AES_BLOCK_SIZE];
    unsigned char output[2 * AES_BLOCK_SIZE];
    unsigned char decrypted[2 * AES_BLOCK_SIZE];
    memset(key, 0x00, AES_BLOCK_SIZE);
    memset(input, 0x00, 2 * AES_BLOCK_SIZE);
    strncpy((char*)key, "thisisakey123456", AES_BLOCK_SIZE);
    strncpy((char*)input, "plaintextblock1plaintextblock2", 2 * AES_BLOCK_SIZE);
    AES_KEY encryptKey, decryptKey;
    AES_set_encrypt_key(key, 128, &encryptKey);
    AES_set_decrypt_key(key, 128, &decryptKey);
    AES_encrypt(input, output, &encryptKey);
    AES_encrypt(input + AES_BLOCK_SIZE, output + AES_BLOCK_SIZE, &encryptKey);
    print_data("Encrypted:", output, 2 * AES_BLOCK_SIZE);
    output[0] ^= 0x01;
    AES_decrypt(output, decrypted, &decryptKey);
    AES_decrypt(output + AES_BLOCK_SIZE, decrypted + AES_BLOCK_SIZE, &decryptKey);
    print_data("Decrypted with error:", decrypted, 2 * AES_BLOCK_SIZE);
    return 0;
}
void print_data(const char *title, const void* data, int len) {
    printf("%s : ", title);
    const unsigned char * p = (const unsigned char*)data;
    for (int i = 0; i < len; ++i)
        printf("%02X ", *p++);
    printf("\n");
}
