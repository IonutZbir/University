/*
  Un processo genera due processi figli P1 e P2.
  Il figlio P1 esegue un ciclo indeterminato durante il quale
  genera casualmente numeri interi compresi tra 0 e 100.
  P1 comunica, ad ogni iterazione, il numero al padre solo se esso è dispari. 
  P2 fa la stessa cosa ma comunica al padre solo i numeri pari.
  Il padre, per ogni coppia di numeri che riceve dai figli ne fa la somma e la
  visualizza. Il programma deve terminare quando la somma dei due numeri
  ricevuti supera il valore 190: il padre, allora, invia un segnale di
  terminazione a ciascuno dei figli.
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Definizione delle costanti per gli estremi dei pipe
#define LEGGI 0
#define SCRIVI 1
#define DIM 6

// Dichiarazione dei pipe
int pd1[2];
int pd2[2];

int main() {
    int pid1, pid2;

    int n, n2;

    int somma = 0;

    clock_t t1;

    // Creazione del primo pipe
    if (pipe(pd1) < 0) {
        printf("Errore pipe");
        return -1;
    }

    // Creazione del secondo pipe
    if (pipe(pd2) < 0) {
        printf("Errore pipe");
        return -1;
    }

    // Creazione del primo figlio
    pid1 = fork();
    if (pid1 == 0) {
        // Codice del primo figlio
        close(pd1[LEGGI]); // Il figlio chiude l'estremo di lettura del pipe
        t1 = clock();
        srand(t1); // Inizializzazione del generatore di numeri casuali
        while (1) {
            n = rand() % 101; // Genera un numero casuale tra 0 e 100
            // Se il numero è dispari, scrive nel pipe
            if (n % 2 == 1) {
                write(pd1[SCRIVI], &n,
                      sizeof(n)); // Everything is a file!! Ma allora e' vero...
            }
        }
    } else if (pid1 > 0) {
        // Codice del padre
        // SNODO FONDAMENTALE: SOLO IN QUESTO PUNTO IL PADRE PUO' GENERARE IL
        // SECONDO PROCESSO
        pid2 = fork();
        if (pid2 == 0) {
            // Codice del secondo figlio
            t1 = clock();
            srand(t1 + 2);     // Inizializzazione del generatore di numeri casuali
            close(pd2[LEGGI]); // Il figlio chiude l'estremo di lettura del pipe
            while (1) {
                n = rand() % 101; // Genera un numero casuale tra 0 e 100
                // Se il numero è pari, scrive nel pipe
                if (n % 2 == 0) {
                    write(pd2[SCRIVI], &n, sizeof(n));
                }
            }
        } else if (pid2 > 0) {
            // Codice (di nuovo) del padre
            close(pd1[SCRIVI]);
            close(pd2[SCRIVI]);

            while (1) {
                // Legge dai pipe.
                read(pd1[LEGGI], &n, sizeof(n));
                read(pd2[LEGGI], &n2, sizeof(n2));
                // Calcola la somma dei numeri
                somma = n + n2;
                printf("n1=%i, n2=%i Somma=%i \n", n, n2, somma);

                // Se la somma supera 190, termina i processi figli
                if (somma > 190) {
                    printf("That's all folks!");
                    kill(pid1, SIGKILL);
                    kill(pid2, SIGKILL);
                    return 0;
                }
            }
        }
    } else if (pid1 == -1) {
        // Se c'è un errore nella fork
        return -1;
    }
}
