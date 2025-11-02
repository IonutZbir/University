/* Scrivere un programma in C con tre thread che operano su un array di dimensione N.
    - Il primo thread riempie un array con numeri casuali tra 0 e 100.
    - Il secondo thread trova il valore massimo nell'array.
    - Il terzo trova il valore minimo. (senza utilizzare pthread_cond_t)
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

pthread_t init_t, max_t, min_t;
pthread_mutex_t mutex;

int buffer[N] = {0};
int done = 0;

void print_buffer() {
    printf("[");
    for (int i = 0; i < N - 1; i++) {
        printf("%d, ", buffer[i]);
    }
    printf("%d ]\n", buffer[N - 1]);
}

void *init(void *args) {
    pthread_mutex_lock(&mutex);
    if (done == 0) {
        for (int i = 0; i < N; i++) {
            buffer[i] = rand() % 101;
            print_buffer();
            sleep(1);
        }
        done = 1;
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *max(void *args) {
    int m = 0;
    while (done != 1)
        ;

    for (int i = 0; i < N; i++) {
        if (buffer[i] >= m)
            m = buffer[i];
    }
    printf("[INFO]: il max è: %d\n", m);

    pthread_exit(NULL);
}

void *min(void *args) {
    int m = 0;
    while (done != 1)
        for (int i = 0; i < N; i++) {
            if (buffer[i] <= m)
                m = buffer[i];
        }
    printf("[INFO]: il min è: %d\n", m);

    pthread_exit(NULL);
}

int main() {

    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&init_t, NULL, init, NULL);
    pthread_create(&max_t, NULL, max, NULL);
    pthread_create(&min_t, NULL, min, NULL);

    pthread_join(init_t, NULL);
    pthread_join(max_t, NULL);
    pthread_join(min_t, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
