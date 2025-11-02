/*
Scrivere un programma C che segue le seguenti specifiche.
Il processo eseguito, inizialmente crea un buffer come array di 11 numeri interi, inizializzati a zero.
In seguito genera 2 processi figli utilizzando le librerie POSIX secondo le seguenti specifiche:
-   Il primo processo filgio sceglie casualmente una cella del buffer e la invia al padre. Il padre modifica il buffer in quella posizione inserendo 1. Dopo ogni scrittura su pipe
    attende un numero di secondi random tra 0 e 3.
-   Il secondo processo figlio sceglie casualmente una cella del buffer e la invia al padre. Il padre modifica il buffer in quella posizione inserendo -1. Dopo ogni scrittura su pipe
    attende un numero di secondi random tra 0 e 3.
-   Il padre dopo ogni modifica del buffer controlla se ci sono ancora degli 0. In caso affermativo conta gli 1 e gli -1, manda a video il risultato e invia un segnale di terminazione
    ai processi.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WR 1
#define RD 0
#define N 11

int init_b(int *buffer) {
    for (int i = 0; i < N; i++) {
        if (buffer[i] == 0)
            return 0;
    }
    return 1;
}

void print_b(int *buffer) {
    printf("[ ");
    for (int i = 0; i < N - 1; i++) {
        printf("%d, ", buffer[i]);
    }
    printf("%d ]\n", buffer[N - 1]);
}

int main() {

    pid_t pos, neg;
    int fd_pos[2], fd_neg[2];

    if (pipe(fd_pos) < 0 || pipe(fd_neg) < 0) {
        fprintf(stderr, "[ERROR]: Could not create pipes! \n");
        exit(1);
    }

    pos = fork();
    if (pos == 0) {
        srand(getpid());
        close(fd_pos[RD]);
        int i;
        while (1) {
            i = rand() % N;
            write(fd_pos[WR], &i, sizeof(i));
            printf("[INFO] POS: %d\n", i);
            sleep(rand() % 4);
        }
    } else if (pos > 0) {
        neg = fork();
        if (neg == 0) {
            srand(getpid());
            close(fd_neg[RD]);
            int i;
            while (1) {
                i = rand() % N;
                printf("[INFO] NEG: %d\n", i);
                write(fd_neg[WR], &i, sizeof(i));
                sleep(rand() % 4);
            }
        } else if (neg > 0) {
            close(fd_pos[WR]);
            close(fd_neg[WR]);

            int buffer[N] = {0};
            int p, n;

            while (1) {
                read(fd_pos[RD], &p, sizeof(p));
                read(fd_neg[RD], &n, sizeof(n));

                buffer[p] = 1;
                buffer[n] = -1;

                print_b(buffer);

                if (init_b(buffer)) {
                    int n_pos = 0, n_neg = 0;
                    for (int i = 0; i < N; i++) {
                        if (buffer[i] == 1) {
                            printf("%d, ", n_pos);
                            n_pos++;
                        } else {
                            printf("%d, ", n_neg);
                            n_neg++;
                        }
                    }
                    printf("[INFO]: Gli uno sono %d e gli -uno sono %d\n", n_pos, n_neg);
                    kill(pos, SIGTERM);
                    kill(neg, SIGTERM);
                    return 0;
                }
            }
        }
    }
}
