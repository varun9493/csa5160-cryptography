#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 6
void generateKeySquare(char keySquare[SIZE][SIZE]) {
    char letters[SIZE * SIZE] = "MFHIKUNOPQZVWXYLEARGDSTBC";
    int i, j, k = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            keySquare[i][j] = letters[k++];
        }
    }
}
void preprocessMessage(char message[], char processedMessage[]) {
    int i, j = 0;
    for (i = 0; i < strlen(message); i++) {
        if (isalpha(message[i])) {
            processedMessage[j++] = toupper(message[i]);
        }
    }
    processedMessage[j] = '\0';
}
void formatMessageForPlayfair(char processedMessage[], char formattedMessage[]) {
    int i, j = 0;
    for (i = 0; i < strlen(processedMessage); i++) {
        formattedMessage[j++] = processedMessage[i];
        if (i < strlen(processedMessage) - 1 && processedMessage[i] == processedMessage[i + 1]) {
            formattedMessage[j++] = 'X';
        }
    }
    if (j % 2 != 0) {
        formattedMessage[j++] = 'X';
    }
    formattedMessage[j] = '\0';
}
void encryptPlayfair(char message[], char keySquare[SIZE][SIZE], char encryptedMessage[]) {
    int i, a, b, c, d;
    int length = strlen(message);   
    for (i = 0; i < length; i += 2) {
        a = b = c = d = -1;
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (keySquare[row][col] == message[i] || (message[i] == 'J' && keySquare[row][col] == 'I')) {
                    a = row;
                    b = col;
                }
                if (keySquare[row][col] == message[i + 1] || (message[i + 1] == 'J' && keySquare[row][col] == 'I')) {
                    c = row;
                    d = col;
                }
            }
        }
        if (a == c) {
            encryptedMessage[i] = keySquare[a][(b + 1) % SIZE];
            encryptedMessage[i + 1] = keySquare[c][(d + 1) % SIZE];
        }
        else if (b == d) {
            encryptedMessage[i] = keySquare[(a + 1) % SIZE][b];
            encryptedMessage[i + 1] = keySquare[(c + 1) % SIZE][d];
        }
        else {
            encryptedMessage[i] = keySquare[a][d];
            encryptedMessage[i + 1] = keySquare[c][b];
        }
    }
    encryptedMessage[length] = '\0';
}
int main() {
    char keySquare[SIZE][SIZE] = {0};
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char processedMessage[256];
    char formattedMessage[256];
    char encryptedMessage[256];
    generateKeySquare(keySquare);
    preprocessMessage(message, processedMessage);
    formatMessageForPlayfair(processedMessage, formattedMessage);
    encryptPlayfair(formattedMessage, keySquare, encryptedMessage);
    printf("Original message: %s\n", message);
    printf("Processed message: %s\n", processedMessage);
    printf("Formatted message: %s\n", formattedMessage);
    printf("Encrypted message: %s\n", encryptedMessage);
    return 0;
}

