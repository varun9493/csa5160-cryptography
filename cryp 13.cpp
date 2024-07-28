#include <stdio.h>
#include <stdlib.h>
#define MOD 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
int determinant(int matrix[2][2]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}
void adjoint(int matrix[2][2], int adj[2][2]) {
    adj[0][0] = matrix[1][1];
    adj[0][1] = -matrix[0][1];
    adj[1][0] = -matrix[1][0];
    adj[1][1] = matrix[0][0];
}
int inverseMatrix(int matrix[2][2], int inverse[2][2]) {
    int det = determinant(matrix);
    int detInv = modInverse(det, MOD);
    if (detInv == -1) {
        return -1;
    }
    int adj[2][2];
    adjoint(matrix, adj);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inverse[i][j] = (adj[i][j] * detInv) % MOD;
            if (inverse[i][j] < 0) {
                inverse[i][j] += MOD;
            }
        }
    }
    return 0;
}
void multiplyMatrix(int matrix1[2][2], int matrix2[2], int result[2]) {
    for (int i = 0; i < 2; i++) {
        result[i] = 0;
        for (int j = 0; j < 2; j++) {
            result[i] += matrix1[i][j] * matrix2[j];
        }
        result[i] %= MOD;
    }
}
void decrypt(int keyInverse[2][2], int ciphertext[2], int plaintext[2]) {
    multiplyMatrix(keyInverse, ciphertext, plaintext);
}
void printMatrix(int matrix[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int plaintext[2][2] = { {7, 4}, {11, 14} };
    int ciphertext[2][2] = { {19, 21}, {15, 4} };
    int key[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            key[i][j] = (ciphertext[i][0] * modInverse(plaintext[0][j], 26) + ciphertext[i][1] * modInverse(plaintext[1][j], 26)) % 26;
        }
    }
    printf("Key matrix:\n");
    printMatrix(key);
    int keyInverse[2][2];
    if (inverseMatrix(key, keyInverse) == -1) {
        printf("Key matrix is not invertible\n");
        return -1;
    }
    printf("Inverse key matrix:\n");
    printMatrix(keyInverse);
    int decryptedText[2];
    for (int i = 0; i < 2; i++) {
        decrypt(keyInverse, ciphertext[i], decryptedText);
        printf("Decrypted block %d: %c%c\n", i + 1, decryptedText[0] + 'A', decryptedText[1] + 'A');
    }
    return 0;
}
