#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

// Definizione di costanti per leggibilità per i descrittori di file
#define STDIN 0
#define STDOUT 1
#define PIPE_RD 0 // Lato di lettura della pipe
#define PIPE_WR 1 // Lato di scrittura della pipe

int main(int argc, char **argv) {

    pid_t cat_pid, sort_pid;
    int fd[2]; // Descrittori di file per la pipe: fd[0] per leggere, fd[1] per
               // scrivere

    pipe(fd); // Crea una pipe. fd[PIPE_RD] sarà l'estremità di lettura,
              // fd[PIPE_WR] sarà l'estremità di scrittura

    cat_pid = fork(); // Fork del processo corrente

    if (cat_pid == 0) {
        // Questo è il processo figlio per 'cat'
        close(fd[PIPE_RD]); // Chiude l'estremità di lettura della pipe, non 
                            // necessaria qui
        close(STDOUT);      // Chiude l'output standard

        /*

        La funzione dup viene utilizzata nei programmi Unix/Linux per duplicare
        un file descriptor esistente, ottenendo un secondo file descriptor che
        punta alla stessa risorsa interna (ad esempio, uno stesso file o lato di
        una pipe). Questo nuovo file descriptor e' il più Basso Disponibile: dup 
        sceglie automaticamente  il numero di file descriptor più basso che è
        disponibile nel processo corrente. Per esempio, se i file descriptor 0,
        1, e 2 sono chiusi, dup utilizzerà il 0 per la sua duplicazione.

         */

        // When working with pipes, dup is often used to redirect standard input
        // or standard output to the read or write end of a pipe.

        dup(fd[PIPE_WR]);
        // Duplica l'estremità di scrittura della pipe al descrittore di file 
        // dell'output standard. Ora, 'cat' scriverà sulla pipe invece che sul 
        // terminale
        execl("/bin/cat", "cat", "names.txt", NULL); // Esegui il comando 'cat'
    }

    sort_pid = fork(); // Fork del processo corrente ancora per 'sort'

    if (sort_pid == 0) {
        // Questo è il processo figlio per 'sort'
        close(fd[PIPE_WR]);
        // Chiude l'estremità di scrittura della pipe, 
        // non necessaria qui
        close(STDIN);     // Chiude l'input standard
        dup(fd[PIPE_RD]); // Duplica l'estremità di lettura della pipe al 
        // descrittore di file dell'input standard
        // Ora, 'sort' leggerà dalla pipe invece che dalla tastiera
        execl("/usr/bin/sort", "sort", NULL); // Esegui il comando 'sort'
    }

    // Questo è il processo genitore
    close(fd[PIPE_RD]);
    // Chiude l'estremità di lettura della pipe, il genitore non la usa
    close(fd[PIPE_WR]);
    // Chiude l'estremità di scrittura della pipe, il genitore non la usa

    // Aspetta che i processi figli terminino
    waitpid(cat_pid, NULL, 0);  // Aspetta il processo 'cat'
    waitpid(sort_pid, NULL, 0); // Aspetta il processo 'sort'
    return 0;
}
