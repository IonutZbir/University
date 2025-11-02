/*
Generare due processi figli che comunicano con il padre. Uno dei processi
genera numeri casuali [0-100] ed invia al padre solo i numeri pari. L'altro
processo genera numeri casuali [0-100] ed invia al padre solo i numeri
dispari. Il padre fa la loro somma e quando la somma > 190, termina
l'esecuzione dei figli.
*/

#include <signal.h> // pid_t
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // system calls

/*
 * p1 = fork()
 * if(p1 == 0){
 *      cose
 * }else if(p1 > 0){
 *      padre
 *      p2 = fork()
 *      if(p2 == 0){
 *          cose
 *      }else if(p2 > 0){
 *          padre
 *          p3 = fork()
 *      if(p3 == 0){
 *          cose
 *      }
 *          ....
 *          ....
 *      else (p_n > 0){
 *          padre
 *          codice padre finale
 *      }
 *      }
 * }
 */

#define PIPE_RD 0
#define PIPE_WR 1

int main() {
    pid_t child_even, child_odd;
    int n;
    int fd_pari[2], fd_dispari[2];
    srand(time(NULL));

    // chiudo i versi di scrittura delle pipe al padre
    close(fd_pari[PIPE_WR]);
    close(fd_dispari[PIPE_WR]);

    // creazione di pipe
    if (pipe(fd_pari) < 0 || pipe(fd_dispari) < 0) {
        perror("[ERROR]: Can't create pipe");
    }

    // creazione primo figlio
    child_even = fork();
    if (child_even < 0) {
        perror("[ERROR]: Can't creare even child");
    }
    if (child_even == 0) {
        // codice del figlio
        // chiudo la pipe in lettura
        close(fd_pari[PIPE_RD]);
        while (1) {
            n = rand() % 101;
            if (n % 2 == 0) {
                // se n è pari, lo scrivo sulla pipe
                write(fd_pari[PIPE_WR], &n, sizeof(n));
            }
        }
    } else if (child_even > 0) {
        // codice del padre
        // creazione secondo figlio
        child_odd = fork();
        if (child_odd < 0) {
            perror("[ERROR]: Can't creare odd child");
        }
        if (child_odd == 0) {
            // codice del figlio
            // chiudo la pipe in lettura
            close(fd_dispari[PIPE_RD]);
            while (1) {
                n = rand() % 101;
                if (n % 2 != 0) {
                    // se n è dispari, lo scrivo sulla pipe
                    write(fd_dispari[PIPE_WR], &n, sizeof(n));
                }
            }
        } else if (child_odd > 0) {
            // codice del padre
            int buf_even, buf_odd, sum;
            while (1) {
                // leggo dal pipe
                read(fd_pari[PIPE_RD], &buf_even, sizeof(buf_even));
                read(fd_dispari[PIPE_RD], &buf_odd, sizeof(buf_odd));
                sum = buf_odd + buf_even;
                printf("[INFO]: %d + %d = %d\n", buf_odd, buf_even, sum);
                if (sum > 190) {
                    kill(child_odd, SIGKILL);
                    kill(child_even, SIGKILL);
                    break;
                }
            }
        }
    }
    return 0;
}
