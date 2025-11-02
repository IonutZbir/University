#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Args {
    const char *data;
    int len;
    int t;
} Args;

sem_t mutex;
int in = 0;

void *print_char(void *args) {
    int i = 0;
    Args *s = (Args *)args;

    while (i < s->len) {
        sem_wait(&mutex);
        if (in >= s->len) {
            sem_post(&mutex);
            break;
        }
        printf("%c ", s->data[in] + 'A' - 'a');
        in++;
        printf("[INFO]: Sono il thread: %d\n", s->t);
        sem_post(&mutex);
        sleep(1);
        i++;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "[ERROR]: No string in input\n");
        return -1;
    }

    const char *s = argv[1];
    const int len = strlen(s);
    const int n = len / 2;

    pthread_t thds[n];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < n; i++) {
        Args *args = (Args *)malloc(sizeof(Args));
        args->data = s;
        args->len = len;
        args->t = i;
        pthread_create(&thds[i], NULL, print_char, (void *)args);
    }

    for (int i = 0; i < len / 2; i++) {
        pthread_join(thds[i], NULL);
    }

    sem_destroy(&mutex);

    return 0;
}
