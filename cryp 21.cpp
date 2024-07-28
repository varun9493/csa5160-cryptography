#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
void print_data(const char *title, const void* data, int len) {
    printf("%s : ", title);
    const unsigned char * p = (const unsigned char*)data;
    for (int i = 0; i < len; ++i)
        printf("%02X ", *p++);
    printf("\n");
}
void pad(unsigned char* input, int input_len, unsigned char* output, int block_size) {
    int pad_len = block_size - (input_len % block_size);
    memcpy(output, input, input_len);
    output[input_len] = 0x80;
    memset(output + input_len + 1, 0x00, pad_len - 1);
}
int get_padded_size(int input_len, int block_size) {
    return input_len + (block_size - (input_len % block_size));
}
int main() {
    const unsigned char key[AES_BLOCK_SIZE] = "thisisakey123456";
    const unsigned char iv[AES_BLOCK_SIZE] = "thisisiv12345678";
    const unsigned char input[] = "This is a test message for AES encryption.";
    int input_len = strlen((const char*)input);
    printf("CBC Mode:\n");
    aes_cbc_encrypt_decrypt(input, input_len, key, iv);
    return 0;
}

