#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/sha.h>
void print_hex(const char *label, const unsigned char *data, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}
int main() {
    DSA *dsa = DSA_new();
    if (!DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL)) {
        fprintf(stderr, "Error generating DSA parameters\n");
        return 1;
    }
    if (!DSA_generate_key(dsa)) {
        fprintf(stderr, "Error generating DSA key\n");
        return 1;
    }
    print_hex("Private key", dsa->priv_key->data, dsa->priv_key->length);
    print_hex("Public key", dsa->pub_key->data, dsa->pub_key->length);
    print_hex("P", dsa->p->data, dsa->p->length);
    print_hex("Q", dsa->q->data, dsa->q->length);
    print_hex("G", dsa->g->data, dsa->g->length);
    const char *message = "Hello, DSA!";
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *)message, strlen(message), hash);
    unsigned char *signature = malloc(DSA_size(dsa));
    unsigned int sig_len;
    if (!DSA_sign(0, hash, SHA_DIGEST_LENGTH, signature, &sig_len, dsa)) {
        fprintf(stderr, "Error signing message\n");
        return 1;
    }
    print_hex("Signature", signature, sig_len);
    if (DSA_verify(0, hash, SHA_DIGEST_LENGTH, signature, sig_len, dsa) != 1) {
        fprintf(stderr, "Signature verification failed\n");
        return 1;
    }
    printf("Signature verification succeeded\n");
    free(signature);
    DSA_free(dsa);
    return 0;
}

