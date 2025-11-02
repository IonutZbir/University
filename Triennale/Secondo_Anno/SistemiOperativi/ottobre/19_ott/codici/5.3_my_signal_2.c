#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Per strsignal()
#include <unistd.h>

void alarm_handler(int signal) {
    printf("In signal handler: caught signal %d which is %s!\n", signal,
           strsignal(signal));
    exit(0);
}

int main(int argc, char **argv) {
    signal(SIGALRM, alarm_handler);
    alarm(1); // alarm will send signal after 1 sec

    while (1) {
        printf("I am running!\n");
        sleep(1);
    }

    return 0;
}
