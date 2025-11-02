/*
Scrivere un programma C che segue le seguenti specifiche.
Il processo eseguito, inizialmente crea un buffer come array di 11 numeri interi, inizializzati a zero. In seguito genera tre thread utilizzando le librerie POSIX secondo le seguenti specifiche:
•   Il primo thread in un ciclo infinito sceglie casualmente una cella del buffer e vi scrive il numero +1, qualsiasi sia il valore presente nella cella.
•   Il secondo thread in un ciclo infinito sceglie casualmente una cella del buffer e vi scrive il numero -1, qualsiasi sia il valore presente nella cella.
•   Il terzo thread in un ciclo infinito controlla se tutte le celle del buffer sono state inizializzate ad un valore diverso da 0. In caso positivo, determina se il numero di celle contenenti un valore pari a +1 è maggiore di quelle con -1 e termina tutti e tre i thread.
•   Mentre un thread ha accesso al buffer, nessun altro thread deve accedervi.
•   Una volta che un thread ha acceduto in lettura o scrittura al buffer, deve attendere un numero di secondi random tra 0 e 3
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ARRAY_SIZE 11

int buffer[ARRAY_SIZE] = {0};
int done = 0;
pthread_mutex_t mutex;

void *write_positive(void *arg) {
    srand(time(NULL));
    while (done == 0) {
        pthread_mutex_lock(&mutex);
        int index = rand() % ARRAY_SIZE;
        buffer[index] = 1;
        printf("Writing a POSITIVE number in cell: %d\n", index);
        pthread_mutex_unlock(&mutex);

        int sleepTime = rand() % 3;
        sleep(sleepTime);
    }
    return NULL;
}

void *write_negative(void *arg) {
    srand(time(NULL) - 100); // Offset del seed
    while (done == 0) {
        pthread_mutex_lock(&mutex);
        int index = rand() % ARRAY_SIZE;
        buffer[index] = -1;
        printf("Writing a NEGATIVE number in cell: %d\n", index);
        pthread_mutex_unlock(&mutex);

        int sleepTime = rand() % 3;
        sleep(sleepTime);
    }
    return NULL;
}

void *check_array(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        printf("Checking\n");
        int pos_count = 0, neg_count = 0, initialized_count = 0;
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if (buffer[i] != 0) {
                initialized_count++;
                if (buffer[i] == 1) {
                    pos_count++;
                } else {
                    neg_count++;
                }
            }
        }
        if (initialized_count == ARRAY_SIZE) {
            printf("+1: %d, -1: %d\n", pos_count, neg_count);
            done = 1;
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        pthread_mutex_unlock(&mutex);

        int sleepTime = rand() % 3;
        sleep(sleepTime);
    }
}

int main() {
    pthread_t threads[3];
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&threads[0], NULL, write_positive, NULL);
    pthread_create(&threads[1], NULL, write_negative, NULL);
    pthread_create(&threads[2], NULL, check_array, NULL);

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
        printf("Thread %i terminated.\n", i);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
