/*
Creare un programma che che legge un file e conta le occorenze di una parola nel seguente modo:
    - Il primo processo legge dall'inzio alla metà e conta le occorenze della parola.
    - Il secondo processo legge dalla metà fino alla fine e conta le occorenze dell parola.
    - Inviano poi il numero di occorenze al processo padre, il quale le somma e le stampa a video.
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 1
#define RD_PIPE 0
#define WR_PIPE 1

int str_equals(const char *str1, char *str2) {
    printf("[INFO]: %s - %s\n", str1, str2);
    if (strcmp(str1, str2) == 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "[ERROR]: %s file word\n", argv[0]);
        return -1;
    }

    int first_pipe[2], second_pipe[2];
    int first_pid, second_pid;

    struct stat file_info;

    const char *file_name = argv[1];
    const char *word_to_find = argv[2];

    int len = strlen(word_to_find);

    stat(file_name, &file_info);

    int file_size = file_info.st_size;
    const int half = file_size / 2;

    if (pipe(first_pipe) < 0 || pipe(second_pipe) < 0) {
        fprintf(stderr, "[ERROR]: could not create pipes\n");
        return -1;
    }

    first_pid = fork();

    if (first_pid == 0) {
        int i = 0, count = 0;
        int file = open(file_name, O_RDONLY);
        close(first_pipe[RD_PIPE]);
        char buffer[len + 1];

        while (i <= half) {
            read(file, buffer, sizeof(buffer));
            buffer[len] = '\0';
            count += str_equals(word_to_find, buffer);
            i++;
            lseek(file, i, SEEK_SET);
        }

        write(first_pipe[WR_PIPE], &count, sizeof(count));
        close(file);
        exit(0);
    } else if (first_pid > 0) {
        second_pid = fork();
        if (second_pid == 0) {
            char buffer[len + 1];
            int count = 0, i = half;
            int file = open(file_name, O_RDONLY);
            close(second_pipe[RD_PIPE]);

            while ((i + len) <= file_size) {
                lseek(file, i, SEEK_SET);
                read(file, buffer, sizeof(buffer));
                buffer[len] = '\0';
                count += str_equals(word_to_find, buffer);
                i++;
            }

            write(second_pipe[WR_PIPE], &count, sizeof(count));
            close(file);
            exit(1);
        } else if (second_pid > 0) {
            int x, y;
            close(first_pipe[WR_PIPE]);
            close(second_pipe[WR_PIPE]);

            waitpid(first_pid, NULL, 0);
            read(first_pipe[RD_PIPE], &x, sizeof(x));
            waitpid(second_pid, NULL, 0);
            read(second_pipe[RD_PIPE], &y, sizeof(y));

            printf("[INFO]: '%s' compare '%d' volte all'interno del file '%s'\n", word_to_find, x + y, file_name);
            return 0;
        }
    }
}
