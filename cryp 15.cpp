#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26
void calculateFrequency(const char* text, int* frequency) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequency[i] = 0;
    }
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            frequency[text[i] - 'a']++;
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            frequency[text[i] - 'A']++;
        }
    }
}
void decrypt(const char* ciphertext, int key, char* plaintext) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}
double scorePlaintext(const char* plaintext) {
    double englishFrequencies[ALPHABET_SIZE] = {
        8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406,
        6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.361, 0.150, 1.974, 0.074
    };
    int frequency[ALPHABET_SIZE];
    calculateFrequency(plaintext, frequency);
    double score = 0.0;
    int length = strlen(plaintext);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double observedFrequency = (double)frequency[i] / length * 100.0;
        score += englishFrequencies[i] * observedFrequency;
    }
    return score;
}
void frequencyAttack(const char* ciphertext, int topN) {
    char plaintext[1000];
    double scores[ALPHABET_SIZE];
    char possiblePlaintexts[ALPHABET_SIZE][1000];
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decrypt(ciphertext, key, plaintext);
        scores[key] = scorePlaintext(plaintext);
        strcpy(possiblePlaintexts[key], plaintext);
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (scores[i] < scores[j]) {
                double tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;
                char tempText[1000];
                strcpy(tempText, possiblePlaintexts[i]);
                strcpy(possiblePlaintexts[i], possiblePlaintexts[j]);
                strcpy(possiblePlaintexts[j], tempText);
            }
        }
    }
    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        printf("%d: %s (Score: %.2f)\n", i + 1, possiblePlaintexts[i], scores[i]);
    }
}
int main() {
    const char* ciphertext = "zpv bsf jo ejggjdvmuz boe joufsftujoh ujnft";
    int topN;
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);
    frequencyAttack(ciphertext, topN);
    return 0;
}

