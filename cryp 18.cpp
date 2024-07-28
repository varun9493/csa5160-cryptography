#include <stdio.h>
#include <stdint.h>
typedef uint64_t ull;
typedef uint32_t uint32;
ull initial_permutation(ull input);
ull final_permutation(ull input);
void generate_keys(ull key, ull* subkeys);
ull des_round(ull input, ull key);
ull des_encrypt(ull input, ull* subkeys);
int main() {
    ull plaintext = 0x0123456789ABCDEF;
    ull key = 0x133457799BBCDFF1;
    ull subkeys[16];
    generate_keys(key, subkeys);
    ull ciphertext = des_encrypt(plaintext, subkeys);
    printf("Encrypted ciphertext: %016llX\n", ciphertext);
    return 0;
}
ull initial_permutation(ull input) {
    return input;
}
ull final_permutation(ull input) {
    return input;
}
void generate_keys(ull key, ull* subkeys) {
    uint32 C = (key >> 28) & 0xFFFFFFF;
    uint32 D = key & 0xFFFFFFF;
    int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    for (int i = 0; i < 16; i++) {
        C = ((C << shifts[i]) | (C >> (28 - shifts[i]))) & 0xFFFFFFF;
        D = ((D << shifts[i]) | (D >> (28 - shifts[i]))) & 0xFFFFFFF;
        subkeys[i] = ((ull)C << 24) | (D >> 4);
    }
}
ull des_round(ull input, ull key) {
    return input ^ key;
}
ull des_encrypt(ull input, ull* subkeys) {
    ull data = initial_permutation(input);
    for (int i = 0; i < 16; i++) {
        data = des_round(data, subkeys[i]);
    }
    data = final_permutation(data);
    return data;
}
