#include <stdlib.h>
#include <sys/types.h>     
#include <sys/socket.h>    /* per struct setsockopt */
#include <errno.h>
#include <stdio.h>    /* per scanf */
#include <sys/time.h> /* per struct timeval */
#include <unistd.h>
#include <string.h>   /* per memcmp */
#include <arpa/inet.h> 

int main(int argc, char *argv[]) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sockfd == -1) {
        perror("Errore nella creazione della socket");
        exit(EXIT_FAILURE);
    }

    /* Indica un intervallo di tempo come numero di secondi piu' un certo numero di microsecondi (sempre inferiore a 1 milione)*/
    struct timeval timeout;      
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;

    /* 
        Imposta l'ozione (a livello di socket) per il timeout di ricezione.
        Restituisce 0 in caso di successo, -1 in caso di errore.
    */
    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
        perror("Errore nella impostazione del timeout di ricezione");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    /* Indirizzo del server. Si noti l'uso di INADDR_LOOPBACK (cioe' 127.0.0.1), usato per comunicare sulla stessa macchina */
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_addr.sin_port = htons(7000);

    printf("Primo operando: ");
    int first_operand;
    scanf("%d", &first_operand);

    printf("Secondo operando: ");
    int second_operand;
    scanf("%d", &second_operand);


    uint32_t input[] = { htonl(first_operand), htonl(second_operand) }; /* converto entrami gli operandi in network byte order */

    ssize_t write_count = sendto(sockfd, &input, sizeof(input), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (write_count == -1) {
        perror("Impossibile inviare la richiesta al server");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in replier_addr;
    socklen_t replier_addr_len = sizeof(replier_addr);
    memset(&replier_addr, 0, sizeof(replier_addr));

    uint32_t sum;

    while (1) { /* cicla finche' non riceve un messaggio dal server oppure si verifica un errore (incluso il timeout) */
        ssize_t read_count = recvfrom(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *)&replier_addr, &replier_addr_len);

        if (read_count == -1) {
            perror("Impossibile ricevere la risposta dal server");
            close(sockfd);
            exit(EXIT_FAILURE);
        } 
        
        if (read_count != sizeof(sum)) {
            fprintf(stderr, "Attesi %ld byte ma letti %ld\n", sizeof(sum), read_count);
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        /* Verifica che l'indirizzo del mittente della risposta sia il serveer, usando la funzione memcmp per un confronto byte a byte */
        if (replier_addr_len != sizeof(replier_addr) || memcmp(&replier_addr, &server_addr, sizeof(replier_addr)) != 0) {
            fprintf(stderr, "Ignora messaggio in ingresso non proveniente dal server");
            continue;
        } else {
            break;
        }
    }

    close(sockfd); /* Chiude la socket */

    sum = ntohl(sum); /* Converte il risultato dal byte order di rete a quello dell'host */

    printf("%d + %d = %d\n", first_operand, second_operand, sum);


    return EXIT_SUCCESS;
}