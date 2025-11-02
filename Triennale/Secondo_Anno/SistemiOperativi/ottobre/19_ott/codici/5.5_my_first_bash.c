#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void free_args(char **args) {
    int i = 0;
    while (args[i]) {
        free(args[i]);
        i++;
    }
}

void read_command(char *cmd, char **args) {
    char *input = NULL;
    size_t len = 0;
    printf("myshell> ");
    ssize_t read_len = getline(&input, &len, stdin);

    if (read_len == -1) { // L'utente ha premuto CTRL+D
        // Quando l'utente preme CTRL+D, la funzione getline restituirà un 
        // alore negativo.  Puoi utilizzare questo per rilevare un EOF e agire
        // di conseguenza.
        printf("\n"); // Per andare a capo dopo CTRL+D
        exit(0);      // Chiudi il shell
    }

    char *token = strtok(input, " \n"); // Dividiamo input su spazi e eventuali
                                        // "\n" (alla fine della stringa)

    int i = 0;
    while (token) {
        args[i] = strdup(
            token); // Usa strdup per duplicare e assegnare memoria al token
        if (i == 0) {
            strcpy(cmd, token);
        }
        token = strtok(NULL, " \n");
        i++;
    }
    args[i] = NULL;
    free(input);
}

int main() {
    while (1) {
        char cmd[256], *args[256];
        int status;
        pid_t pid;

        read_command(cmd, args);

        if (strcmp(cmd, "exit") == 0) {
            exit(0);
        }

        pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0) {
            if (execvp(cmd, args) == -1) {
                perror("execvp failed");
                exit(1);
            }
        } else {
            if (wait(&status) == -1) {
                perror("wait failed");
                exit(1);
            }
        }

        // gestisce lo "spreco di memoria" introdotto da strdup
        free_args(args);
    }
    return 0;
}
