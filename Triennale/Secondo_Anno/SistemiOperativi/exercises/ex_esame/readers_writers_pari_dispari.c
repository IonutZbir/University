/*
Sei thread, un scrittore e 5 lettori. Lo scrittore scrive su un buffer numeri dispari da 0 a 50 nelle posizioni pari e numeri pari da 50 a 100 nelle posizioni dispari. I lettori
leggono coppie di numeri (paro, disparo), li somma e li stampa.
*/

#include <inttypes.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define R 5
#define N 10
#define MAX 10

sem_t mutex;
sem_t arr;
pthread_t writer;
pthread_t readers[R];
int buffer[N] = {0};
int r_count = 0;

int gen(int m, int off, int mod) {
    int n;
    do {
        n = rand() % m + 1 + off;
    } while (n % 2 != mod);
    return n;
}

void print_buffer() {
    printf("[");
    for (int i = 0; i < N - 1; i++) {
        printf("%d, ", buffer[i]);
    }
    printf("%d ]\n", buffer[N - 1]);
}

void *f_writer(void *args) {
    int i = 0;
    while (i < MAX) {
        int pos_pari = gen(N, 0, 1);
        int pos_dispari = gen(N, 0, 0);

        int n_dispari = gen(50, 50, 0);
        int n_pari = gen(50, 0, 1);

        sem_wait(&arr);

        buffer[pos_pari] = n_dispari;
        buffer[pos_dispari] = n_pari;

        print_buffer();

        sem_post(&arr);
        sleep(1);
        i++;
    }
    pthread_exit(NULL);
}

void *reader(void *args) {
    int i = 0;
    int *j = (int *)args;
    while (i < MAX) {
        sem_wait(&mutex);
        r_count++;
        if (r_count == 1)
            sem_wait(&arr);
        sem_post(&mutex);

        int pos_pari = gen(N, 0, 1);
        int pos_dispari = gen(N, 0, 0);
        int n1 = buffer[pos_pari];
        int n2 = buffer[pos_dispari];

        sem_wait(&mutex);
        r_count--;
        if (r_count == 0)
            sem_post(&arr);
        sem_post(&mutex);

        int sum = n1 + n2;
        printf("[INFO]: Sono il thread %d\n", *j);
        printf("[INFO]: %d + %d = %d \n", n1, n2, sum);
        sleep(1);
        i++;
    }
    pthread_exit(NULL);
}

int main() {

    srand(time(NULL));

    sem_init(&mutex, 0, 1);
    sem_init(&arr, 0, 1);

    for (int i = 0; i < R; i++) {
        int *k = malloc(sizeof(int));
        *k = i;
        pthread_create(&readers[i], NULL, reader, (void *)k);
    }
    pthread_create(&writer, NULL, f_writer, NULL);

    pthread_join(writer, NULL);
    for (int i = 0; i < R; i++) {
        pthread_join(readers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&arr);

    return 0;
}
