#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void generateKeySquare(char key[], char keySquare[SIZE][SIZE]) {
    int alphabet[26] = {0};
    int i, j, k = 0;
    for (i = 0; i < strlen(key); i++) {
        if (key[i] != 'J') {
            alphabet[toupper(key[i]) - 'A'] = 1;
        }
    }
    alphabet['J' - 'A'] = 1;
    k = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            while (alphabet[k] == 1) k++;
            if (k >= 26) break;
            if (alphabet[k] == 0) {
                keySquare[i][j] = (char)(k + 'A');
                alphabet[k] = 1;
            }
        }
    }
}
void decryptPlayfair(char message[], char keySquare[SIZE][SIZE]) {
    int i, a, b, c, d;
    for (i = 0; i < strlen(message); i += 2) {
        a = b = c = d = -1;
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (keySquare[row][col] == message[i]) {
                    a = row;
                    b = col;
                }
                if (keySquare[row][col] == message[i + 1]) {
                    c = row;
                    d = col;
                }
            }
        }
        if (a == c) {
            message[i] = keySquare[a][(b + SIZE - 1) % SIZE];
            message[i + 1] = keySquare[c][(d + SIZE - 1) % SIZE];
        }
        else if (b == d) {
            message[i] = keySquare[(a + SIZE - 1) % SIZE][b];
            message[i + 1] = keySquare[(c + SIZE - 1) % SIZE][d];
        }
        else {
            message[i] = keySquare[a][d];
            message[i + 1] = keySquare[c][b];
        }
    }
}
int main() {
    char key[] = "MONARCHY";
    char keySquare[SIZE][SIZE] = {0};
    char message[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    generateKeySquare(key, keySquare);
    decryptPlayfair(message, keySquare);
    printf("Decrypted message: %s\n", message);
    return 0;
}

