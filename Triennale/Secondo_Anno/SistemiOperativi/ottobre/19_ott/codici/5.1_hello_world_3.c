#include <stdio.h>
#include <sys/syscall.h> //
#include <unistd.h>      // libreria per le chiamate di sistema
#define STDOUT 1

int main(int argc, char **argv) {
    char msg[] = "Hello World!\n";
    int nr = SYS_write;
    syscall(nr, STDOUT, msg, sizeof(msg));
    return 0;
}
