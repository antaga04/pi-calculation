#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <iterations>\n", argv[0]);
        return 1;
    }

    long long iterations = atoll(argv[1]);
    double pi = 0.0;

    for (long long i = 0; i < iterations; i++) {
        pi += ((i % 2 == 0 ? 1 : -1) / (double)(2 * i + 1));
    }

    pi *= 4;
    printf("Computed Pi value: %.15f\n", pi);

    return 0;
}
