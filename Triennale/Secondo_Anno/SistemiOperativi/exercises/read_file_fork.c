/*
Create a program that reads a large file and counts the occurrences of a specific word using parallel processing.
Divide the file into sections, and let each child process handle a section.
The parent process should aggregate the results from all child processes.
*/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

#define PIPE_WR 1
#define PIPE_RD 0

int get_file_size(const char *file_name) {
    struct stat file_info;
    if (stat(file_name, &file_info) < 0) {
        return -1;
    }
    return file_info.st_size;
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "[ERROR]: ./%s inputfile.txt word_to_search\n", argv[0]);
        return -1;
    }

    pid_t p1, p2;
    int fd_p1[2], fd_p2[2];

    const char *file_name = argv[1];
    const char *word = argv[2];
    const int file_size = get_file_size(file_name);
    const int half = file_size / 2;
    const int word_len = strlen(word);
    char buffer[word_len];

    if (pipe(fd_p1) < 0 || pipe(fd_p2) < 0) {
        fprintf(stderr, "[ERROR]: Could not create pipes\n");
        return -1;
    }

    if ((p1 = fork()) < 0) {
        fprintf(stderr, "[ERROR]: Could not create process\n");
        return -1;
    }
    if (p1 == 0) {
        int i = 0;
        int file = open(file_name, O_RDONLY);
        while (i < half) {
            read(file, &buffer, word_len);
            if (buffer[i] != '\n') {
            }
        }
    } else if (p1 > 0) {
        if ((p2 = fork()) < 0) {
            fprintf(stderr, "[ERROR]: Could not create process\n");
            return -1;
        }
    }

    return 0;
}
