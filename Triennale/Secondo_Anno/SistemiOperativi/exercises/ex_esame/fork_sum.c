/*
Generare due processi figli che comunicano con il padre.
    - Uno dei processi genera numeri casuali [0-50] ed invia al padre solo i numeri multipli di 3.
    - L'altro processo genera numeri casuali [51-100] ed invia al padre solo i numeri multipli di 2.
    - Il padre stampa i numeri ricevuti ed esegue la loro somma, quando la somma > 130 termina i processi.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define PIPE_WR 1
#define PIPE_RD 0

int main() {

    srand(time(NULL));

    int fd_tre[2], fd_due[2];
    pid_t p1, p2;

    int n_rand;

    if (pipe(fd_tre) < 0 || pipe(fd_due) < 0) {
        fprintf(stderr, "[ERROR]: could not create pipes\n");
        return -1;
    }

    p1 = fork();

    if (p1 < 0) {
        fprintf(stderr, "[ERROR]: could not create proccess\n");
        return -1;
    }

    if (p1 == 0) {
        // first child
        close(fd_tre[PIPE_RD]);
        while (1) {
            do {
                n_rand = rand() % 51;
            } while (n_rand % 3 != 0);
            write(fd_tre[PIPE_WR], &n_rand, sizeof(n_rand));
            sleep(1);
        }
    } else if (p1 > 0) {
        p2 = fork();
        if (p2 < 0) {
            fprintf(stderr, "[ERROR]: could not creare proccess\n");
            return -1;
        }
        if (p2 == 0) {
            // second child
            close(fd_tre[PIPE_RD]);
            while (1) {
                do {
                    n_rand = rand() % 51 + 50;
                } while (n_rand % 2 != 0);
                write(fd_due[PIPE_WR], &n_rand, sizeof(n_rand));
                sleep(1);
            }
        } else if (p2 > 0) {
            // parent
            int sum, n1, n2;
            close(fd_tre[PIPE_WR]);
            close(fd_due[PIPE_WR]);

            do {
                read(fd_tre[PIPE_RD], &n1, sizeof(n1));
                read(fd_due[PIPE_RD], &n2, sizeof(n2));
                sum = n1 + n2;
                printf("[INFO]: %d + %d = %d\n", n1, n2, sum);
            } while (sum < 130);
            kill(p1, SIGTERM);
            kill(p2, SIGTERM);
            return 0;
        }
    }
}
