#include <stdio.h>
#include <string.h>
#define MATRIX_SIZE 2
#define MODULO 26
void encryptHillCipher(char plaintext[], int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char ciphertext[]) {
    int i, j, k, length = strlen(plaintext);
    for (i = 0; i < length; i += 2) {
        int a = plaintext[i] - 'a';
        int b = plaintext[i + 1] - 'a';
        int c = (keyMatrix[0][0] * a + keyMatrix[0][1] * b) % MODULO;
        int d = (keyMatrix[1][0] * a + keyMatrix[1][1] * b) % MODULO;
        ciphertext[i] = c + 'a';
        ciphertext[i + 1] = d + 'a';
    }
    ciphertext[length] = '\0';
}
void decryptHillCipher(char ciphertext[], int invKeyMatrix[MATRIX_SIZE][MATRIX_SIZE], char plaintext[]) {
    int i, j, k, length = strlen(ciphertext);
    for (i = 0; i < length; i += 2) {
        int a = ciphertext[i] - 'a';
        int b = ciphertext[i + 1] - 'a';
        int c = (invKeyMatrix[0][0] * a + invKeyMatrix[0][1] * b) % MODULO;
        int d = (invKeyMatrix[1][0] * a + invKeyMatrix[1][1] * b) % MODULO;
        if (c < 0) c += MODULO;
        if (d < 0) d += MODULO;
        plaintext[i] = c + 'a';
        plaintext[i + 1] = d + 'a';
    }
    plaintext[length] = '\0';
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}
void findInverseMatrix(int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], int invKeyMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
    int invDet = modInverse(det, MODULO);
    invKeyMatrix[0][0] = keyMatrix[1][1] * invDet % MODULO;
    invKeyMatrix[0][1] = -keyMatrix[0][1] * invDet % MODULO;
    invKeyMatrix[1][0] = -keyMatrix[1][0] * invDet % MODULO;
    invKeyMatrix[1][1] = keyMatrix[0][0] * invDet % MODULO;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (invKeyMatrix[i][j] < 0) invKeyMatrix[i][j] += MODULO;
        }
    }
}
int main() {
    char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclock";
    char ciphertext[256];
    char decryptedText[256];
    int keyMatrix[MATRIX_SIZE][MATRIX_SIZE] = {{9, 4}, {5, 7}};
    int invKeyMatrix[MATRIX_SIZE][MATRIX_SIZE];
    printf("Original message: %s\n", plaintext);
    encryptHillCipher(plaintext, keyMatrix, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);
    findInverseMatrix(keyMatrix, invKeyMatrix);
    decryptHillCipher(ciphertext, invKeyMatrix, decryptedText);
    printf("Decrypted message: %s\n", decryptedText);
    return 0;
}

