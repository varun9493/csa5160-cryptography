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
void des_ecb(const unsigned char *plaintext, unsigned char *ciphertext, size_t length, DES_key_schedule *schedule, int enc) {
    DES_cblock block;
    for (size_t i = 0; i < length; i += 8) {
        memcpy(block, plaintext + i, 8);
        if (enc) {
            DES_ecb_encrypt(&block, (DES_cblock *)(ciphertext + i), schedule, DES_ENCRYPT);
        } else {
            DES_ecb_encrypt(&block, (DES_cblock *)(ciphertext + i), schedule, DES_DECRYPT);
        }
    }
}
void des_cbc(const unsigned char *input, unsigned char *output, size_t length, DES_key_schedule *schedule, DES_cblock *iv, int enc) {
    DES_ncbc_encrypt(input, output, length, schedule, iv, enc);
}
void des_cfb(const unsigned char *input, unsigned char *output, size_t length, DES_key_schedule *schedule, DES_cblock *iv, int enc) {
    int num = 0;
    DES_cfb64_encrypt(input, output, length, schedule, iv, &num, enc);
}
int main() {
    DES_cblock key = {0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};
    DES_key_schedule schedule;
    DES_set_key_checked(&key, &schedule);
    DES_cblock iv = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    DES_cblock iv_copy;
    unsigned char plaintext[] = "Hello, DES Modes!";
    size_t plaintext_len = sizeof(plaintext) - 1;
    size_t pad_len = 8 - (plaintext_len % 8);
    unsigned char padded_plaintext[plaintext_len + pad_len];
    memcpy(padded_plaintext, plaintext, plaintext_len);
    for (size_t i = 0; i < pad_len; i++) {
        padded_plaintext[plaintext_len + i] = pad_len;
    }
    size_t padded_len = plaintext_len + pad_len;
    unsigned char ciphertext[padded_len];
    unsigned char decrypted_text[padded_len];
    printf("ECB Mode:\n");
    des_ecb(padded_plaintext, ciphertext, padded_len, &schedule, DES_ENCRYPT);
    print_hex("Ciphertext", ciphertext, padded_len);
    des_ecb(ciphertext, decrypted_text, padded_len, &schedule, DES_DECRYPT);
    printf("Decrypted text: %.*s\n\n", (int)(padded_len - decrypted_text[padded_len - 1]), decrypted_text);
    printf("CBC Mode:\n");
    memcpy(iv_copy, iv, sizeof(DES_cblock));
    des_cbc(padded_plaintext, ciphertext, padded_len, &schedule, &iv_copy, DES_ENCRYPT);
    print_hex("Ciphertext", ciphertext, padded_len);
    memcpy(iv_copy, iv, sizeof(DES_cblock));
    des_cbc(ciphertext, decrypted_text, padded_len, &schedule, &iv_copy, DES_DECRYPT);
    printf("Decrypted text: %.*s\n\n", (int)(padded_len - decrypted_text[padded_len - 1]), decrypted_text);
    printf("CFB Mode:\n");
    memcpy(iv_copy, iv, sizeof(DES_cblock));
    des_cfb(padded_plaintext, ciphertext, padded_len, &schedule, &iv_copy, DES_ENCRYPT);
    print_hex("Ciphertext", ciphertext, padded_len);
    memcpy(iv_copy, iv, sizeof(DES_cblock));
    des_cfb(ciphertext, decrypted_text, padded_len, &schedule, &iv_copy, DES_DECRYPT);
    printf("Decrypted text: %.*s\n", (int)(padded_len - decrypted_text[padded_len - 1]), decrypted_text);
    return 0;
}

