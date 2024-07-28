#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void prepareKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int dict[26] = {0};
    int i, j, k;
    int len = strlen(key);
    for (i = 0; i < len; i++) {
        if (key[i] == 'j') {
            key[i] = 'i';
        }
        if (key[i] == 'J') {
            key[i] = 'I';
        }
        dict[toupper(key[i]) - 'A'] = 2;
    }
    char currentChar = 'A';
    for (i = 0, k = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (k < len) {
                while (dict[toupper(key[k]) - 'A'] == 1) {
                    k++;
                }
                keyTable[i][j] = toupper(key[k++]);
            } else {
                while (dict[currentChar - 'A'] != 0) {
                    currentChar++;
                }
                if (currentChar == 'J') currentChar++;
                keyTable[i][j] = currentChar++;
            }
            dict[keyTable[i][j] - 'A'] = 1;
        }
    }
}
void search(char keyTable[SIZE][SIZE], char a, char b, int arr[]) {
    int i, j;
    if (a == 'j') a = 'i';
    else if (a == 'J') a = 'I';
    if (b == 'j') b = 'i';
    else if (b == 'J') b = 'I';
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            }
            if (keyTable[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}
void encrypt(char str[], char keyTable[SIZE][SIZE], char result[]) {
    int i, a[4];
    for (i = 0; str[i] != '\0'; i += 2) {
        if (str[i + 1] == '\0') {
            str[i + 1] = 'X';
            str[i + 2] = '\0';
        }
        if (str[i] == str[i + 1]) {
            memmove(&str[i + 1], &str[i], strlen(&str[i]) + 1);
            str[i + 1] = 'X';
        }
        search(keyTable, toupper(str[i]), toupper(str[i + 1]), a);

        if (a[0] == a[2]) {
            result[i] = keyTable[a[0]][(a[1] + 1) % SIZE];
            result[i + 1] = keyTable[a[2]][(a[3] + 1) % SIZE];
        } else if (a[1] == a[3]) {
            result[i] = keyTable[(a[0] + 1) % SIZE][a[1]];
            result[i + 1] = keyTable[(a[2] + 1) % SIZE][a[3]];
        } else {
            result[i] = keyTable[a[0]][a[3]];
            result[i + 1] = keyTable[a[2]][a[1]];
        }
    }
    result[i] = '\0';
}
int main() {
    char key[100], str[100];
    char keyTable[SIZE][SIZE];
    char result[200];
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    printf("Enter the plaintext: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    for (int i = 0, j = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = toupper(str[i]);
        }
    }
    prepareKeyTable(key, keyTable);
    encrypt(str, keyTable, result);
    printf("Encrypted message: %s\n", result);
    return 0;
}

