#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    long long start;
    long long end;
    double sum;
} ThreadData;

void *calculate_pi(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    double sum = 0.0;

    for (long long i = data->start; i < data->end; i++) {
        sum += ((i % 2 == 0 ? 1 : -1) / (double)(2 * i + 1));
    }

    data->sum = sum;
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <iterations> <threads>\n", argv[0]);
        return 1;
    }

    long long iterations = atoll(argv[1]);
    int num_threads = atoi(argv[2]);
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    long long chunk_size = iterations / num_threads;
    double pi = 0.0;

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == num_threads - 1) ? iterations : (i + 1) * chunk_size;
        thread_data[i].sum = 0.0;
        pthread_create(&threads[i], NULL, calculate_pi, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        pi += thread_data[i].sum;
    }

    pi *= 4;
    printf("Computed Pi value: %.15f\n", pi);

    return 0;
}
