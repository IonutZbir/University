/*

Esempio dello schema Produttore Consumatore in C usando POSIX

Autore. Danilo Croce

NOTA: per essere eseguito in ambiente LINUX usare gcc -pthread source_file.c -o
binary_output


*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10 /* numero di posti nel buffer */
#define TRUE 1
#define MAX 100

/* Dichiarazione dei semafori */
sem_t mutex; // Semaforo per l'accesso esclusivo alla regione critica
sem_t empty; // Semaforo per contare i posti vuoti nel buffer
sem_t full;  // Semaforo per contare i posti pieni nel buffer

int buffer[N]; // Buffer condiviso tra produttore e consumatore
int in = 0;    // Indice dove inserire il prossimo elemento nel buffer

/* Funzioni helper per utilizzare i semafori */
/* Decrementa di 1 il semaforo, quando il semaforo è 0 il thread chiamante viene
 * bloccato */
void down(sem_t *sem) { sem_wait(sem); }

// Incrementa di 1 il semaforo, quando è > 0 viene risvegliato uno dei thread in attesa 
void up(sem_t *sem) { sem_post(sem); }

/* Funzione per inserire un elemento nel buffer */
void insert_item() {
    int item = rand() % 100; // Genera un elemento casuale
    printf("\nInserisco %d in posizione %d\n", item, (in + 1));
    buffer[in] = item; // Inserisce l'elemento nel buffer
    in++;              // Incrementa l'indice
}

/* Funzione per rimuovere un elemento dal buffer */
void remove_item() {
    int item = buffer[in - 1];
    printf("\nPrelevo %d da posizione %d\n", item, in);
    in--; // Decrementa l'indice
}

/* Funzione per stampare il contenuto del buffer */
void print_buffer() {
    for (int i = 0; i < in; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

/* Funzione eseguita dal thread del produttore */
void *producer(void *arg) {
    int i = 0;
    while (i < MAX) {
        down(&empty); // Decrementa empty, quindi aggiungo un elemento nel
                      // buffer. Se empty == 0, il buffer è pieno quindi il 
                      // produttore si blocca (si mette in attesa che il
                      // consumatore consuma almeno un elemento)
        down(&mutex); // Prova a entrare nella regione critica, se il mutex è 0
                      // attende altrimenti entra nella regione critica

        insert_item();  // Inserisce un elemento nel buffer
        print_buffer(); // Stampa il contenuto del buffer

        // Che succede se metto print_buffer dopo up(full) o dopo up(mutex)?
        // Il buffer potrebbe essere gia stato modificato dal consumatore poichè 
        // si trova al di fuori della regione critica

        up(&mutex); // Esce dalla regione critica
        up(&full);  // Segnala che c'è un posto pieno in più nel buffer,
                    // incrementando full

        // down(&mutex)
        // down(&empty)
        // se provo a scambiarli cosa succede? In pratica puo succedere che: il
        // thread si prende la zona critica e se empty == 0 allora si blocca
        // nella regione critica, bloccando tutta l'esecuzione del programma
        i++;
    }
    pthread_exit(NULL);
}

/* Funzione eseguita dal thread del consumatore */
void *consumer(void *arg) {
    int i = 0;
    while (i < MAX) {
        down(&full);  // Decrementa full, quindi consumo un elemento dal buffer,
                      // se full == 0, il buffer è vuoto quindi il consumatore si 
                      // blocca (si mette in attesa che il produttore produca
                      // almeno un elemento)
        down(&mutex); // Prova a entrare nella regione critica, se il mutex è 0
                      // attende altrimenti entra nella regione critica

        remove_item();  // Rimuove un elemento dal buffer
        print_buffer(); // Stampa il contenuto del buffer

        up(&mutex); // Esce dalla regione critica
        up(&empty); // Segnala che c'è un posto vuoto in più nel buffer, i
                    // incrementa empty
        i++;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod, cons; // Dichiarazione dei thread

    // Inizializzazione dei semafori
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

    // Creazione dei thread
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Attesa della terminazione dei thread
    pthread_join(prod, NULL); // non essendoci un exit girano all'infinito,
    pthread_join(cons, NULL);

    // Distruzione dei semafori
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
