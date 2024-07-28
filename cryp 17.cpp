#include <stdio.h>
#include <stdint.h>
typedef uint64_t ull;
typedef uint32_t uint32;
ull initial_permutation(ull input);
ull final_permutation(ull input);
void generate_keys(ull key, ull* subkeys);
ull des_round(ull input, ull key);
ull des_decrypt(ull input, ull* subkeys);
int main() {
    ull ciphertext = 0x85E813540F0AB405;
    ull key = 0x133457799BBCDFF1;
    ull subkeys[16];
    generate_keys(key, subkeys);
    ull plaintext = des_decrypt(ciphertext, subkeys);
    printf("Decrypted plaintext: %016llX\n", plaintext);
    return 0;
}
ull initial_permutation(ull input) {
    return input;
}
ull final_permutation(ull input) {
    return input;
}
void generate_keys(ull key, ull* subkeys) {
    for (int i = 0; i < 16; i++) {
        subkeys[15 - i] = key ^ i;
    }
}

ull des_round(ull input, ull key) {
    return input ^ key;
}
ull des_decrypt(ull input, ull* subkeys) {
    ull data = initial_permutation(input);
    for (int i = 0; i < 16; i++) {
        data = des_round(data, subkeys[i]);
    }
    data = final_permutation(data);
    return data;
}
