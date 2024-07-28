#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_TEXT_LENGTH 500
void countFrequency(char *ciphertext, int freq[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i]) || isdigit(ciphertext[i]) || ispunct(ciphertext[i])) {
            freq[ciphertext[i]]++;
        }
    }
}
void printFrequency(int freq[]) {
    printf("Character frequencies:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("%c: %d\n", i, freq[i]);
        }
    }
}
void substitute(char *ciphertext, char *key, char *result) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i]) || isdigit(ciphertext[i]) || ispunct(ciphertext[i])) {
            result[i] = key[ciphertext[i]];
        } else {
            result[i] = ciphertext[i];
        }
    }
    result[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    char key[256] = {0};
    char result[MAX_TEXT_LENGTH];
    int freq[256] = {0};
    for (int i = 0; i < 256; i++) {
        key[i] = i; 
    }
    key['‡'] = 'e';
    key['5'] = 't';
    key['3'] = 'h';
    countFrequency(ciphertext, freq);
    printFrequency(freq);
    substitute(ciphertext, key, result);
    printf("Decrypted message:\n%s\n", result);
    return 0;
}

