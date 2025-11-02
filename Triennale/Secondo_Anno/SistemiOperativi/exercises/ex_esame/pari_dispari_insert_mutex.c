/*
Si scriva un programma con tre thread che risolvono il seguente problema:
Un buffer di n elementi inizializzato con a -1 viene riempito nel seguente modo:
    - Il primo thread aggiunge nelle posizioni pari del buffer un numero casuale da 0 a 100.
    - Il secondo thread aggiunge nelle posizioni dispari del buffer un casuale da 100 a 200.
    - Il terzo thread somma gli elementi e modifica il buffer nel seguente modo:
        buff[0] = buff[0], buff[1] = buff[1] + buff[0], buff[2] = buff[1] + buff[2]
Si proponga una soluzione di mutua esclusione.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10
#define NT 3

pthread_t threads[NT];
pthread_mutex_t mutex;
pthread_cond_t cond;

int done = 0;

int buffer[N];

void print_buffer() {
    printf("[ ");
    for (int i = 0; i < N - 1; i++) {
        printf("%d, ", buffer[i]);
    }
    printf("%d ]\n", buffer[N - 1]);
}

void *add_pari(void *args) {
    int pos, num;
    while (done == 0) {
        do {
            pos = rand() % N;
        } while (pos % 2 != 0);
        pthread_mutex_lock(&mutex);

        num = rand() % 101;

        printf("[INFO]: Sono il thread pari. buffer[%d] = %d\n", pos, num);

        buffer[pos] = num;
        print_buffer();

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 2);
    }
    pthread_exit(NULL);
}

void *add_dispari(void *args) {
    int pos, num;
    while (done == 0) {
        do {
            pos = rand() % N;
        } while (pos % 2 != 1);
        pthread_mutex_lock(&mutex);

        num = rand() % 101 + 100;
        printf("[INFO]: Sono il thread dispari. buffer[%d] = %d\n", pos, num);

        buffer[pos] = num;
        print_buffer();

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 2);
    }
    pthread_exit(NULL);
}

int check_buffer() {
    for (int i = 0; i < N; i++) {
        if (buffer[i] == -1)
            return 0;
    }
    return 1;
}

void *sum(void *args) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (!check_buffer()) {
            pthread_cond_wait(&cond, &mutex);
        }
        done = 1;
        for (int i = 1; i < N; i++) {
            buffer[i] += buffer[i - 1];
        }

        printf("[INFO]: Sono il terzo thread, ho effettuato le somme.\n");
        print_buffer();
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
}

int main() {

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        buffer[i] = -1;
    }
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&threads[0], NULL, add_pari, NULL);
    pthread_create(&threads[1], NULL, add_dispari, NULL);
    pthread_create(&threads[2], NULL, sum, NULL);

    for (int i = 0; i < NT; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
