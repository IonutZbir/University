/*
Due thread, il produttore inserisce numeri pari da 0 a 100 in posizioni pari, e numeri dispari da 100 a 200 in posizioni dispari all'interno di un buffer di N elementi,
iniziliazzato a -1, il consumatore legge dal buffer un numero pari e un numero dispari, li somma e stampa la loro somma.
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10
#define MAX 10

sem_t mutex;
sem_t full, empty;
pthread_t prod, cons;
int buffer[N];

int gen_n(int n, int mod, int offset) {
    int x;
    do {
        x = rand() % n + offset;
    } while (x % 2 != mod);
    return x;
}

void print_buffer() {
    printf("[ ");
    for (int i = 0; i < N - 1; i++) {
        printf("%d, ", buffer[i]);
    }
    printf("%d ]\n", buffer[N - 1]);
}

void *producer(void *args) {

    int pos_p, pos_d;

    int i = 0;

    while (i < MAX) {

        sem_wait(&empty);
        sem_wait(&mutex);

        pos_p = gen_n(N, 1, 0);
        pos_d = gen_n(N, 0, 0);
        buffer[pos_p] = gen_n(100, 1, 0);
        buffer[pos_d] = gen_n(100, 0, 100);

        printf("\n --- T1 --- \n");

        printf("[INFO]: buffer[%d] = %d - buffer[%d] = %d\n", pos_p, buffer[pos_p], pos_d, buffer[pos_d]);

        print_buffer();

        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
        i++;
    }
    pthread_exit(NULL);
}

void *consumer(void *args) {
    int pos_p, pos_d, n_pari, n_dispari, sum;

    int i = 0;

    while (i < MAX) {

        sem_wait(&full);
        sem_wait(&mutex);

        pos_p = gen_n(N, 1, 0);
        pos_d = gen_n(N, 0, 0);

        n_pari = buffer[pos_p];
        n_dispari = buffer[pos_d];

        sum = n_pari + n_dispari;

        printf("\n --- T2 ---\n");

        printf("[INFO]: (buffer[%d] -> %d) + (buffer[%d] -> %d) = %d \n", pos_p, n_pari, pos_d, n_dispari, sum);

        sem_post(&mutex);
        sem_post(&empty);
        sleep(2);
        i++;
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
