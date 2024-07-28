#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26
double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.361, 0.150,
    1.974, 0.074
};
typedef struct {
    char letter;
    int frequency;
} LetterFrequency;
int compare(const void *a, const void *b) {
    return ((LetterFrequency *)b)->frequency - ((LetterFrequency *)a)->frequency;
}
void calculateFrequency(const char* text, LetterFrequency* frequency) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequency[i].letter = 'a' + i;
        frequency[i].frequency = 0;
    }
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            frequency[text[i] - 'a'].frequency++;
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            frequency[text[i] - 'A'].frequency++;
        }
    }
}
void generateKey(LetterFrequency* ciphertextFreq, char* key) {
    qsort(ciphertextFreq, ALPHABET_SIZE, sizeof(LetterFrequency), compare);
    int englishFreqIndices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        englishFreqIndices[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (englishFrequencies[englishFreqIndices[i]] < englishFrequencies[englishFreqIndices[j]]) {
                int temp = englishFreqIndices[i];
                englishFreqIndices[i] = englishFreqIndices[j];
                englishFreqIndices[j] = temp;
            }
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[ciphertextFreq[i].letter - 'a'] = 'a' + englishFreqIndices[i];
    }
}
void decrypt(const char* ciphertext, const char* key, char* plaintext) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = key[ciphertext[i] - 'a'];
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = key[ciphertext[i] - 'A'];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}
void frequencyAttack(const char* ciphertext, int topN) {
    LetterFrequency frequency[ALPHABET_SIZE];
    char possiblePlaintexts[ALPHABET_SIZE][1000];
    double scores[ALPHABET_SIZE];
    calculateFrequency(ciphertext, frequency);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        char key[ALPHABET_SIZE + 1] = {0};
        generateKey(frequency, key);
        decrypt(ciphertext, key, possiblePlaintexts[i]);
        scores[i] = 0;
        int length = strlen(possiblePlaintexts[i]);
        for (int j = 0; j < length; j++) {
            if (possiblePlaintexts[i][j] >= 'a' && possiblePlaintexts[i][j] <= 'z') {
                scores[i] += englishFrequencies[possiblePlaintexts[i][j] - 'a'];
            }
        }
        LetterFrequency temp = frequency[0];
        for (int j = 0; j < ALPHABET_SIZE - 1; j++) {
            frequency[j] = frequency[j + 1];
        }
        frequency[ALPHABET_SIZE - 1] = temp;
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
    const char* ciphertext = "wkh fliihu brx duh orrnlqj iru lv d frpsxwhu surjudp pljkw lqyhqw";
    int topN;
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);
    frequencyAttack(ciphertext, topN);
    return 0;
}

