#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Per strsignal()
#include <unistd.h>

void signalHandler(int signum) {
    printf("\nInterrupt signal [%d] received which is [%s]\n", signum,
           strsignal(signum));
    // cleanup and terminate program
    exit(signum);
}

int main() {
    // register signal SIGINT and signal handler
    // signal(SIGINT, signalHandler);  // CTRL+C
    signal(SIGTERM, signalHandler); // CTRL+Z

    while (1) {
        printf("Going to sleep...\n");
        sleep(1);
    }

    return 0; // questa riga non verrà mai raggiunta a causa del ciclo while(1)
}
