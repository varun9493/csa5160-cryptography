#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define KECCAK_ROUNDS 24
#define STATE_SIZE 25 
const int rotation_constants[5][5] = {
    { 0, 36, 3, 41, 18 },
    { 1, 44, 10, 45, 2 },
    { 62, 6, 43, 15, 61 },
    { 28, 55, 25, 21, 56 },
    { 27, 20, 39, 8, 14 }
};
const uint64_t round_constants[KECCAK_ROUNDS] = {
    0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808aULL, 0x8000000080008000ULL,
    0x000000000000808bULL, 0x0000000080000001ULL, 0x8000000080008081ULL, 0x8000000000008009ULL,
    0x000000000000008aULL, 0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000aULL,
    0x000000008000808bULL, 0x800000000000008bULL, 0x8000000000008089ULL, 0x8000000000008003ULL,
    0x8000000000008002ULL, 0x8000000000000080ULL, 0x000000000000800aULL, 0x800000008000000aULL,
    0x8000000080008081ULL, 0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL
};
uint64_t rotate_left(uint64_t value, int shift) {
    return (value << shift) | (value >> (64 - shift));
}
void keccak_f(uint64_t state[STATE_SIZE]) {
    int x, y;
    for (int round = 0; round < KECCAK_ROUNDS; round++) {
        uint64_t C[5], D[5], B[5][5];
        for (x = 0; x < 5; x++) {
            C[x] = state[x] ^ state[x + 5] ^ state[x + 10] ^ state[x + 15] ^ state[x + 20];
        }
        for (x = 0; x < 5; x++) {
            D[x] = C[(x + 4) % 5] ^ rotate_left(C[(x + 1) % 5], 1);
        }
        for (x = 0; x < 5; x++) {
            for (y = 0; y < 5; y++) {
                state[x + 5 * y] ^= D[x];
            }
        }
        for (x = 0; x < 5; x++) {
            for (y = 0; y < 5; y++) {
                B[y][(2 * x + 3 * y) % 5] = rotate_left(state[x + 5 * y], rotation_constants[x][y]);
            }
        }
        for (x = 0; x < 5; x++) {
            for (y = 0; y < 5; y++) {
                state[x + 5 * y] = B[x][y] ^ ((~B[(x + 1) % 5][y]) & B[(x + 2) % 5][y]);
            }
        }
        state[0] ^= round_constants[round];
    }
}
void sha3_init(uint64_t state[STATE_SIZE]) {
    memset(state, 0, sizeof(uint64_t) * STATE_SIZE);
}
void sha3_absorb(uint64_t state[STATE_SIZE], const uint8_t *message, size_t length) {
    size_t rate = 136;
    while (length >= rate) {
        for (size_t i = 0; i < rate / 8; i++) {
            state[i] ^= ((uint64_t *)message)[i];
        }
        keccak_f(state);
        message += rate;
        length -= rate;
    }
    uint8_t last_block[rate];
    memset(last_block, 0, rate);
    memcpy(last_block, message, length);
    last_block[length] = 0x06;
    last_block[rate - 1] |= 0x80;
    for (size_t i = 0; i < rate / 8; i++) {
        state[i] ^= ((uint64_t *)last_block)[i];
    }
    keccak_f(state);
}
void sha3_squeeze(uint64_t state[STATE_SIZE], uint8_t *hash, size_t hash_length) {
    size_t rate = 136;
    while (hash_length > 0) {
        size_t bytes_to_copy = (hash_length < rate) ? hash_length : rate;
        memcpy(hash, state, bytes_to_copy);
        hash += bytes_to_copy;
        hash_length -= bytes_to_copy;
        if (hash_length > 0) {
            keccak_f(state);
        }
    }
}
int main() {
    uint64_t state[STATE_SIZE];
    uint8_t message[] = "Hello, world!";
    uint8_t hash[32];
    sha3_init(state);
    sha3_absorb(state, message, sizeof(message) - 1);
    sha3_squeeze(state, hash, sizeof(hash));
    printf("SHA-3-256 hash: ");
    for (size_t i = 0; i < sizeof(hash); i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    return 0;
}

