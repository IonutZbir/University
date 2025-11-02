/*
 Si richiede di implementare un programma in linguaggio C che utilizzi il metodo delle fork per la comunicazione tra processi.
 Il programma dovrà creare un file di testo e poi creare due processi figli. Uno dei processi figli dovrà scrivere una sequenza di
 N numeri interi pari da 0 a 9 nel file, mentre l'altro processo figlio dovrà scrivere una sequenza di N numeri interi dispari da 0 a 9, attraverso
 la funzione seek va a scriverli subito dopo la sequenza degli N numeri pari nello stesso file.
 Il processo padre dovrà leggere i dati dal file e stamparli a video.

@author Adriano Porzia
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

#define PIPE_RD 0
#define PIPE_WR 1

#define MAX 10
#define MASK 0700

void print_buffer(char buffer[], int n) {
    printf("[ ");
    for (int i = 0; i < n - 1; i++) {
        printf("%c, ", buffer[i]);
    }
    printf("%c ]\n", buffer[n - 1]);
}

int main() {
    srand(time(NULL));
    const char *filename = "dati.txt";
    pid_t pid_p, pid_d;
    int fd_p[2];
    int fd_d[2];

    if (pipe(fd_p) < 0 || pipe(fd_d) < 0) {
        fprintf(stderr, "[ERROR]: could not create pipes\n");
        return -1;
    }

    pid_p = fork();
    if (pid_p < 0) {
        fprintf(stderr, "[ERROR]: could not create pipes\n");
        return -1;
    }
    if (pid_p == 0) {
        const int len_seq = 10;
        int file = creat(filename, MASK);
        int pari;
        close(fd_p[PIPE_RD]);
        for (int i = 0; i < len_seq; i++) {
            do {
                pari = rand() % MAX;
            } while (pari % 2 == 1);

            printf("%d ", pari);
            char buff = (char)(pari + '0');

            write(file, &buff, sizeof(buff));
        }
        printf("\n");
        write(fd_p[PIPE_WR], &len_seq, sizeof(len_seq));
        close(file);

    } else if (pid_p > 0) {
        pid_d = fork();
        if (pid_d == 0) {
            const int len_seq = 5;
            int offset;
            int dispari;
            int file = creat(filename, MASK);
            waitpid(pid_p, NULL, 0);
            read(fd_p[PIPE_RD], &offset, sizeof(offset));
            lseek(file, offset, SEEK_SET);

            for (int i = 0; i < len_seq; i++) {
                do {
                    dispari = rand() % MAX;
                } while (dispari % 2 == 0);
                printf("%d ", dispari);
                char buff = (char)(dispari + '0');

                write(file, &buff, sizeof(buff));
            }
            printf("\n");
            offset += len_seq; // trovo la lunghezza totale della sequenza
            write(fd_d[PIPE_WR], &offset, sizeof(offset));
            close(file);
        } else if (pid_d > 0) {
            close(fd_p[PIPE_WR]);
            close(fd_p[PIPE_RD]);
            close(fd_d[PIPE_WR]);

            int len;

            waitpid(pid_d, NULL, 0);
            read(fd_d[PIPE_RD], &len, sizeof(len));

            int file = open(filename, O_RDONLY);
            char buffer[len];
            read(file, &buffer, len);

            printf("[INFO] : il numero di elementi totale è %d\n", len);
            print_buffer(buffer, len);
            printf("[ %s ]\n", buffer);

            close(file);
            return 0;
        }
    }
}
