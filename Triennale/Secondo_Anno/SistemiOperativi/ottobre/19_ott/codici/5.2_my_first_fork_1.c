#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {

    int pid, child_status;
    // fork -> int
    // i figli/cloni hanno pid = 0
    // il padre ha un pid > 0
    pid = fork();
    // il figlio inizia la sua esecuzione dall'istruzione subito il fork

    if (pid < 0) {
        fprintf(stderr, "[ERROR]: Could not initialize process");
        exit(0);
    }

    if (pid == 0) { // figlio
        printf("[INFO]: I am the child and I see the PID %d\n", pid);
    } else {                 // è il padre 
        wait(&child_status); // wait for child
        //   wait vuole il puntatore alla variabile
        printf("[INFO]: I am the parent, I see the child's PID (%d) and the status (%d)\n", pid, child_status);
    }
}
