#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 5000
#define BUFFERSIZE 1000

char buffer[BUFFERSIZE];

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in serveraddr;

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(serveraddr.sin_family, "127.0.0.1", &serveraddr.sin_addr);
    serveraddr.sin_port = htons(PORT);

    if (((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    memset(&buffer, 0, sizeof(buffer));

    if (fgets((char *)&buffer, sizeof(buffer), stdin)) {
        if (send(sockfd, &buffer, strlen(buffer), 0) == -1) {
            perror("send");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        shutdown(sockfd, SHUT_WR);

        ssize_t nread;
        while ((nread = recv(sockfd, &buffer, sizeof(buffer), 0)) > 0) {
            write(STDOUT_FILENO, buffer, nread);
        }
        if (nread == -1) {
            perror("recv");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }

    fsync(STDOUT_FILENO);

    close(sockfd);

    return EXIT_SUCCESS;
}
