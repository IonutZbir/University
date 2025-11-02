/* Due processi leggono dallo stesso file che si trova dentro una dir, per
 * esempio /data/file.txt, controllare che il file sia in modalità lettura, 
 * altrimenti errore. Il primo processo legge dall'inizio del file fino a metà, 
 * il secondo legge dalla metà in poi. I figli mandano il contenuto al padre, e
 * il padre lo stampa: [PID] -> contenuto
 */

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

#define PIPE_RD 0
#define PIPE_WR 1

long file_size(const char *filename) {
    struct stat st;
    // st.st_mode: da informazioni sulla tipologia del file (dir o no), e i permessi
    if (stat(filename, &st) == 0) {
        return st.st_size;
    } else {
        perror("[ERROR]: Error getting file size");
        return -1; // Indicates an error
    }
}

int check_read_permission(const char *filename) {
    struct stat fileInfo;
    if (stat(filename, &fileInfo) < 0) {
        return -1;
    }
    int user = fileInfo.st_mode & S_IRUSR;
    return user;
}

int main(int dim, char **argv) {

    const char input_file[] = "data/input.txt";
    pid_t p1, p2;
    int fd_p1[2], fd_p2[2];
    long size = file_size(input_file);
    int half = size / 2;
    char buff[half];
    if (pipe(fd_p1) < 0 || pipe(fd_p2) < 0) {
        fprintf(stderr, "[ERROR]: Could not create pipe\n");
        exit(1);
    }

    if ((p1 = fork()) < 0) {
        fprintf(stderr, "[ERROR]: Could not create process\n");
        exit(2);
    }
    if (p1 == 0) {
        close(fd_p1[PIPE_RD]);
        int perm = check_read_permission(input_file);
        if (!perm) {
            fprintf(stderr, "[ERROR]: Not enough permissions\n");
            exit(3);
        }
        int file = open(input_file, O_RDONLY);
        read(file, &buff, half);
        close(file);
        write(fd_p1[PIPE_WR], &buff, half);
    } else if (p1 > 0) {
        if ((p2 = fork()) < 0) {
            fprintf(stderr, "[ERROR]: Could not create process\n");
            exit(2);
        }
        if (p2 == 0) {
            close(fd_p2[PIPE_RD]);
            int perm = check_read_permission(input_file);
            if (!perm) {
                fprintf(stderr, "[ERROR]: Not enough permissions\n");
                exit(3);
            }
            int file = open(input_file, O_RDONLY);
            lseek(file, half, SEEK_SET);
            read(file, &buff, half);
            close(file);
            write(fd_p2[PIPE_WR], &buff, half);
        } else if (p2 > 0) {
            close(fd_p1[PIPE_WR]);
            close(fd_p2[PIPE_WR]);

            read(fd_p1[PIPE_RD], buff, half);
            waitpid(p1, NULL, 0);
            printf("[INFO]: [%d] -> %s\n", p1, buff);

            printf("------------------------------------------------\n");

            read(fd_p2[PIPE_RD], buff, half);
            waitpid(p2, NULL, 0);
            printf("[INFO]: [%d] -> %s\n", p2, buff);
        }
    }

    return 0;
}
