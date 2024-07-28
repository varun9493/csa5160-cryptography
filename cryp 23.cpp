#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char BYTE;
const int a = 5;
const int b = 8;
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
BYTE affine_encrypt(BYTE plaintext, int a, int b) {
    return (a * plaintext + b) % 256;
}
BYTE affine_decrypt(BYTE ciphertext, int a, int b) {
    int a_inv = mod_inverse(a, 256);
    if (a_inv == -1) {
        printf("Inverse doesn't exist!");
       exit(1);
    }
    return (a_inv * (ciphertext - b)) % 256;
}
void print_byte_binary(BYTE byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 0x01);
    }
}
void ctr_encrypt_decrypt(BYTE* input, int input_len, BYTE* key_stream, BYTE* output) {
    for (int i = 0; i < input_len; i++) {
        output[i] = input[i] ^ key_stream[i];
    }
}
void generate_key_stream(BYTE* key_stream, int length, BYTE* nonce) {
    for (int i = 0; i < length; i++) {
        key_stream[i] = affine_encrypt(nonce[i], a, b);
    }
}
int main() {
    BYTE plaintext[] = {0x01, 0x02, 0x04};
    int plaintext_len = sizeof(plaintext);
    BYTE nonce[] = {0x00, 0x01, 0x02};
    BYTE key_stream[plaintext_len];
    BYTE ciphertext[plaintext_len];
    BYTE decrypted_text[plaintext_len];
    generate_key_stream(key_stream, plaintext_len, nonce);
    ctr_encrypt_decrypt(plaintext, plaintext_len, key_stream, ciphertext);
    printf("Encrypted text: ");
    for (int i = 0; i < plaintext_len; i++) {
        print_byte_binary(ciphertext[i]);
        printf(" ");
    }
    printf("\n");
    ctr_encrypt_decrypt(ciphertext, plaintext_len, key_stream, decrypted_text);
    printf("Decrypted text: ");
    for (int i = 0; i < plaintext_len; i++) {
        print_byte_binary(decrypted_text[i]);
        printf(" ");
    }
    printf("\n");
    return 0;
}

