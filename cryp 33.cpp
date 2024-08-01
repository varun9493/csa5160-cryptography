#include <stdio.h>
#include <string.h>
#include <openssl/des.h>
void print_hex(const char *label, const unsigned char *data, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}
int main() {
    DES_cblock key = {0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};
    DES_key_schedule schedule;
    DES_set_key_checked(&key, &schedule);
    DES_cblock iv = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    unsigned char plaintext[] = "Hello, DES!";
    size_t plaintext_len = sizeof(plaintext) - 1;
    size_t pad_len = 8 - (plaintext_len % 8);
    unsigned char padded_plaintext[plaintext_len + pad_len];
    memcpy(padded_plaintext, plaintext, plaintext_len);
    for (size_t i = 0; i < pad_len; i++) {
        padded_plaintext[plaintext_len + i] = pad_len;
    }
    size_t padded_len = plaintext_len + pad_len;
    unsigned char ciphertext[padded_len];
    DES_ncbc_encrypt(padded_plaintext, ciphertext, padded_len, &schedule, &iv, DES_ENCRYPT);
    print_hex("Ciphertext", ciphertext, padded_len);
    memcpy(iv, (DES_cblock[]){0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef}, sizeof(DES_cblock));
    unsigned char decrypted_text[padded_len];
    DES_ncbc_encrypt(ciphertext, decrypted_text, padded_len, &schedule, &iv, DES_DECRYPT);
    pad_len = decrypted_text[padded_len - 1];
    size_t decrypted_len = padded_len - pad_len;
    printf("Decrypted text: %.*s\n", (int)decrypted_len, decrypted_text);
    return 0;
}
