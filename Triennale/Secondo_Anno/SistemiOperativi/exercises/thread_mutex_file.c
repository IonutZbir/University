/*
1.  Il programma crea un file chiamato dati.txt" contenente un array di 10 numeri interi, inizializzati a zero.
    Ogni numero deve essere separato da uno spazio.
2.  Genera tre thread utilizzando le librerie POSIX:
    • Il primo thread legge il contenuto del file "dati.txt", imposta 1 una cella causale
    scrive i nuovi valori nel file.
    Il thread esegue questa operazione in un ciclo infinito con una pausa casuale tra le iterazioni.
    • Il secondo thread legge il contenuto del file "dati.txt", imposta -1 una cella casuale
    scrive i nuovi valori nel fie.
    Il thread esegue questa operazione in un ciclo infinito con una pausa casuale tra le iterazioni.
    • Il terzo thread, in un ciclo infinito, controlla se tutti i valori nel file sono diversi da 0, se lo sono, conta gli +- uni.
    In caso affermativo, termina entrambi i thread.
4.  Assicurati che un thread abbia accesso esclusivo al file mentre legge o scrive. Utilizza I mutex per gestire
    l'accesso concorrente al file.
5.  Introduci una pausa casuale tra le operazioni di lettura e scrittura del thread.
*/

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define N 10
#define OUTPUT_MODE 0700

pthread_mutex_t the_mutex;
pthread_cond_t condp;
pthread_t p1, p2, p3;

const char file_name[] = "dati.txt";

int char_to_int(char n) {
    return n - '0';
}

char int_to_char(int n) {
    return n + '0';
}

int write_file(int *buffer, int len) {
    int file = creat(file_name, OUTPUT_MODE);
    if (file < 0)
        return -1;
    char buff[4];

    for (int i = 0; i < len; i++) {
        buff[0] = int_to_char(0);
        buff[1] = int_to_char(0);
        buff[2] = ' ';
        buff[3] = '\0';
        // printf("%s\n", buff);
        write(file, &buff, strlen(buff));
    }
    close(file);
    return 0;
}

int modify_file(int index, int mode) {
    struct stat info;
    int file;
    int n;
    char char_repr[2];

    file = open(file_name, O_RDWR);

    // printf("[INFO]: %d\n", index);

    lseek(file, (index * 2), SEEK_SET);
    read(file, &char_repr, sizeof(char_repr));

    printf("[INFO]: CHAR: %s\n", char_repr);

    sscanf(char_repr, "%d", &n);

    lseek(file, -2, SEEK_CUR);
    // n++ ? (mode == 1) : n--; WRONG
    n = (mode == 1) ? (n + 1) : (n - 1);
    printf("[INFO]: INT++: %d\n", n);
    sprintf(char_repr, "%d", n);
    write(file, &char_repr, sizeof(char_repr));
    close(file);

    return 0;
}

void print_data() {
    struct stat info;
    stat(file_name, &info);
    int size = info.st_size;
    int file;
    char buffer[size];
    file = open(file_name, O_RDONLY);
    read(file, &buffer, size);
    printf("\n[ ");
    printf("%d -> %s", (int)strlen(buffer), buffer);
    printf("]\n");
    close(file);
}

void *increment(void *args) {
    int index, i = 0;
    while (i < N) {
        pthread_mutex_lock(&the_mutex);
        index = rand() % N;
        modify_file(index, 1);
        print_data();
        i++;
        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&the_mutex);
        sleep(rand() % 4);
    }
    pthread_exit(0);
}

void *decrement(void *args) {
    int index, i = 0;
    while (i < N) {
        pthread_mutex_lock(&the_mutex);
        index = rand() % N;
        modify_file(index, 0);
        print_data();
        i++;
        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&the_mutex);
        sleep(rand() % 4);
    }
    pthread_exit(0);
}

int main() {
    srand(time(NULL));
    int buffer[N] = {0};
    if (write_file(buffer, N) < 0) {
        fprintf(stderr, "[ERROR]: Could not write on file\n");
        return -1;
    }
    int index = rand() % N;
    printf("[INFO]: index: %d\n", index);
    print_data();
    int i = 0;
    while (i < N) {
        modify_file(i, 1);
        i++;
    }
    print_data();

    return 0;
}

int main1() {
    srand(time(NULL));
    int buffer[N] = {0};
    if (write_file(buffer, N) < 0) {
        fprintf(stderr, "[ERROR]: Could not write on file\n");
        return -1;
    }

    pthread_create(&p1, NULL, increment, NULL);
    pthread_create(&p2, NULL, decrement, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_mutex_destroy(&the_mutex);
    pthread_cond_destroy(&condp);
    return 0;
}
