#include <stdio.h>
#include <stdlib.h>
#include <time.h>
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
int main() {
    unsigned long long a = 5;
    unsigned long long q = 23;
    srand(time(0));
    unsigned long long x1 = rand() % (q - 1) + 1;
    unsigned long long A = mod_exp(a, x1, q);
    unsigned long long x2 = rand() % (q - 1) + 1;
    unsigned long long B = mod_exp(a, x2, q);
    printf("Public parameters: a = %llu, q = %llu\n", a, q);
    printf("Participant 1 sends: %llu\n", A);
    printf("Participant 2 sends: %llu\n", B);
    unsigned long long key1 = mod_exp(B, x1, q);
    unsigned long long key2 = mod_exp(A, x2, q);
    printf("Participant 1's computed key: %llu\n", key1);
    printf("Participant 2's computed key: %llu\n", key2);
    if (key1 == key2) {
        printf("The shared secret key is successfully computed by both participants: %llu\n", key1);
    } else {
        printf("There was an error in the key exchange.\n");
    }
    return 0;
}

