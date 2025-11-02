/*
Scrivere un programma C che segue le seguenti specifiche.
Il processo eseguito, inizialmente crea un buffer come array di 11 numeri interi, inizializzati a zero.
In seguito genera tre thread utilizzando le librerie POSIX secondo le seguenti specifiche:
•   Il primo thread sceglie casualmente una cella del buffer e vi scrive il numero +1,
    qualsiasi sia il valore presente nella cella.
•   Il secondo thread sceglie casualmente una cella del buffer e vi scrive il numero -1,
    qualsiasi sia il valore presente nella cella.
•   Il terzo thread controlla se tutte le celle del buffer sono state inizializzate.
    In caso positivo, determina se il numero di celle contententi un valore pari a +1 è maggiore di quelle con -1
    e termina tutti e tre i thread.
•  Mentre un thread ha accesso al buffer, nessun altro thread deve accedervi.
•  Una volta che un thread ha acceduto in lettura o scrittura al buffer,
   deve attendere un numero di secondi random tra 0 e 3
*/

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 5

pthread_mutex_t the_mutex;
pthread_cond_t cond_control;

int buffer[N] = {0};
pthread_t p1, p2, p3;

void print_buffer() {
    printf("[");
    for (int i = 0; i < N - 1; i++) {
        printf("%3d,", buffer[i]);
    }
    printf("%3d ]\n", buffer[N - 1]);
}

void *set_one(void *args) {
    while (1) {
        pthread_mutex_lock(&the_mutex);
        int index = rand() % N;
        buffer[index] = 1;
        printf("[INFO]: sono thread 1, ho generato l'indice: %d\n", index);
        print_buffer();
        pthread_cond_signal(&cond_control);
        pthread_mutex_unlock(&the_mutex);
        sleep(rand() % 4);
    }
}

void *set_neg_one(void *args) {
    while (1) {
        pthread_mutex_lock(&the_mutex);
        int index = rand() % N;
        buffer[index] = -1;
        printf("[INFO]: Sono thread 2, ho generato l'indice: %d\n", index);
        print_buffer();
        pthread_cond_signal(&cond_control);
        pthread_mutex_unlock(&the_mutex);
        sleep(rand() % 4);
    }
}

int check_init() {
    for (int i = 0; i < N; ++i) {
        if (buffer[i] == 0) {
            return 0;
        }
    }
    return 1;
}

void *control(void *args) {
    while (1) {
        pthread_mutex_lock(&the_mutex);

        // controllo se tutti i elementi dell'array sono inizializzatise
        // se lo sono allora il thread va avanti, altrimenti lascia il mutex e rifà il controllo.
        while (check_init() == 0) {
            sleep(rand() % 4);
            pthread_cond_wait(&cond_control, &the_mutex);
        }
        int n_ones = 0, n_neg_ones = 0;
        for (int i = 0; i < N; i++) {
            if (buffer[i] == 1)
                n_ones++;
            if (buffer[i] == -1)
                n_neg_ones++;
        }

        if (n_ones > n_neg_ones) {
            printf("[INFO]: Ha vinto il thread 1, impostando %d -> '1'\n", n_ones);
        } else {
            printf("[INFO]: Ha vinto il thread 2, impostando %d -> '-1'\n", n_neg_ones);
        }
        // printf("[INFO]: sono il 3 thread\n");
        pthread_kill(p1, SIGINT);
        pthread_kill(p2, SIGINT);
        pthread_mutex_unlock(&the_mutex);

        pthread_exit(0); // Termina il thread
    }
}
int main() {
    srand(time(NULL));

    pthread_mutex_init(&the_mutex, NULL);
    pthread_cond_init(&cond_control, NULL);

    pthread_create(&p1, NULL, set_one, NULL);
    pthread_create(&p2, NULL, set_neg_one, NULL);
    pthread_create(&p3, NULL, control, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);

    pthread_cond_destroy(&cond_control);
    pthread_mutex_destroy(&the_mutex);
    return 0;
}
