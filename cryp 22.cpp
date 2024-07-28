int main() {
    BYTE key = 0xFD;
    BYTE iv = 0xAA;
    BYTE plaintext[] = {0x01, 0x23};
    int plaintext_len = sizeof(plaintext);
    BYTE padded_plaintext[16];
    memcpy(padded_plaintext, plaintext, plaintext_len);
    int padded_len = pad(padded_plaintext, plaintext_len, 1);
    BYTE ciphertext[16];
    BYTE decrypted_text[16];
    cbc_encrypt(padded_plaintext, padded_len, key, &iv, ciphertext);
    printf("Encrypted text: ");
    for (int i = 0; i < padded_len; i++) {
        print_byte_binary(ciphertext[i]);
        printf(" ");
    }
    printf("\n");
    cbc_decrypt(ciphertext, padded_len, key, &iv, decrypted_text);
    printf("Decrypted text: ");
    for (int i = 0; i < padded_len; i++) {
        print_byte_binary(decrypted_text[i]);
        printf(" ");
    }
    printf("\n");
    return 0;
}

