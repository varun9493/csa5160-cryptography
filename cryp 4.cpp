#include <stdio.h>
#include <string.h>
#define SIZE 26
void generateTable(char table[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            table[i][j] = 'A' + (i + j) % SIZE;
        }
    }
}
void polyalphabeticSubstitutionCipher(char *plain, char *key, char *cipher) {
    int i, j, k = 0;
    char table[SIZE][SIZE];
    generateTable(table);
    for (i = 0; plain[i]; i++) {
        j = (plain[i] - 'A' + key[k % strlen(key)] - 'A') % SIZE;
        cipher[i] = table[j][plain[i] - 'A'];
        k++;
    }
    cipher[i] = '\0';
}
int main() {
    char plain[100], key[100], cipher[100];
    printf("Enter the plaintext: ");
    scanf("%s", plain);
    printf("Enter the key: ");
    scanf("%s", key);
    polyalphabeticSubstitutionCipher(plain, key, cipher);
    printf("Ciphertext: %s\n", cipher);
    return 0;
}
