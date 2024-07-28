#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define BLOCK_SIZE 16
void simple_block_cipher_encrypt(uint8_t *output, const uint8_t *input, const uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}
void cbc_mac(uint8_t *mac, const uint8_t *message, size_t message_len, const uint8_t *key) {
    uint8_t block[BLOCK_SIZE] = {0};
    uint8_t buffer[BLOCK_SIZE];
    for (size_t i = 0; i < message_len; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= message[i + j];
        }
        simple_block_cipher_encrypt(buffer, block, key);
        memcpy(block, buffer, BLOCK_SIZE);
    }
    memcpy(mac, block, BLOCK_SIZE);
}
int main() {
    uint8_t key[BLOCK_SIZE] = {
        0x1f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 
        0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0
    };
    uint8_t message[BLOCK_SIZE] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };
    uint8_t mac[BLOCK_SIZE];
    cbc_mac(mac, message, BLOCK_SIZE, key);
    printf("MAC: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", mac[i]);
    }
    printf("\n");
    uint8_t two_block_message[2 * BLOCK_SIZE];
    memcpy(two_block_message, message, BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        two_block_message[BLOCK_SIZE + i] = message[i] ^ mac[i];
    }
    uint8_t mac_two_blocks[BLOCK_SIZE];
    cbc_mac(mac_two_blocks, two_block_message, 2 * BLOCK_SIZE, key);
    printf("MAC for two-block message: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", mac_two_blocks[i]);
    }
    printf("\n");
    return 0;
}

