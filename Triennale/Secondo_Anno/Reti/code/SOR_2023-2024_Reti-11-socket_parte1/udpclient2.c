#include <stdlib.h>
#include <sys/types.h>     
#include <sys/socket.h>    /* per struct setsockopt */
#include <errno.h>
#include <stdio.h>    /* per scanf */
#include <sys/time.h> /* per struct timeval */
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h> 

/* come udpclient.c ma con l'aggiunta di una "connect" */

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


    /*
        Collega la socket rappresentata da sockfd all'indirizzo fornito. Nel caso di una socket di tipo SOCK_DGRAM, questa funzione
        NON crea una connessione con una socket remota, ma serve solo a indicare l'indirizzo:
        * cui sono indirizzati i dati in maniera predefinita (quando usiamo send invece di sendto)
        * da cui soltanto possiamo ricevere dati (quindi possiamo usare recv invece di recvfrom)
    */
    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));


    printf("Primo operando: ");
    int first_operand;
    scanf("%d", &first_operand);

    printf("Secondo operando: ");
    int second_operand;
    scanf("%d", &second_operand);


    uint32_t input[] = { htonl(first_operand), htonl(second_operand) }; /* converto entrami gli operandi in network byte order */

    ssize_t write_count = send(sockfd, &input, sizeof(input), 0);

    if (write_count == -1) {
        perror("Impossibile inviare la richiesta al server");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    uint32_t sum;

    while (1) { /* cicla finche' non riceve un messaggio dal server oppure si verifica un errore (incluso il timeout) */
        ssize_t read_count = recv(sockfd, &sum, sizeof(sum), 0);

        if (read_count == -1) {
            perror("Impossibile ricevere la risposta dal server");
            close(sockfd);
            exit(EXIT_FAILURE);
        } 
        
        if (read_count != sizeof(sum)) {
            fprintf(stderr, "Attesi %ld byte ma letti %ld\n", sizeof(sum), read_count);
            close(sockfd);
            exit(EXIT_FAILURE);
        } else {    /* Esce dal ciclo avendo ricevuto il numero di byte atteso */
            break;
        }
    }

    close(sockfd); /* Chiude la socket */

    sum = ntohl(sum); /* Converte il risultato dal byte order di rete a quello dell'host */

    printf("%d + %d = %d\n", first_operand, second_operand, sum);


    return EXIT_SUCCESS;
}