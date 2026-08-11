#include <stdio.h>

int main() {
    int attempts[] = {12, 45, 8, 89, 34};
    int max = 0;

    // Loop through the array to find the maximum value
    for (int i = 0; i < 5; i++) {
        if (attempts[i] > max) {
            max = attempts[i];
        }
    }

    printf("Max attempts: %d\n", max);
    return 0;
}