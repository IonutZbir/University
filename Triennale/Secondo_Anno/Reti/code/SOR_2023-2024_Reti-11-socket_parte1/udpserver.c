#include <stdlib.h>      /* per EXIT_SUCCESS, EXIT_FAILURE */
#include <sys/socket.h>  /* per socket, AF_INET, SOCK_DGRAM, bind, struct sockaddr, recvfrom, sendto */
#include <arpa/inet.h>   /* per inet_ntop, htonl, htons */
#include <stdio.h>       /* per printf, perror */
#include <unistd.h>      /* per close, uint32_t */
#include <string.h>      /* per memset */
#include <netinet/in.h>  /* per IPPROTO_UDP, struct sockaddr_in */

int main(int argc, char *argv[]) {
    /* Creo una socket:
       * famiglia di indirizzi per Internet IPv4
       * tipo di socket (ovvero, semantica della comunicazione) a datagramma (senza connessione, trasferimento non affidabile di messagi di dimensione massima prestabilita)
       * protocollo UDP
    */
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); /* L'ultimo argomento sarebbe potuto essere 0, lasciando al sistema di inferire UDP */
    if (sockfd == -1) {
        perror("socket"); /* Stampa una descrizione dell'errore contenuto nella variabile errno */
        exit(EXIT_FAILURE);
    }

    /*
        Inizializza una variabile struct sockaddr_in per descrivere l'indirizzo della socket del server, che sarà associata alla porta 7000
        e a qualsisi indirizzo IP assegnato all'host (piu' precisamente a qualsiasi dei suoi adattatori di rete).

        In alternativa a INADDR_ANY, avremmo potuto usare INADDR_LOOPBACK per indicare l'indirizzo IP 127.0.0.1 usato per comunicare
        con altri processi sulla stessa macchina. 
    */
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* Network byte order */
    server_addr.sin_port = htons(7000); /* Network byte order */
    
    /* Associa la socket a un indirizzo locale */
    int rv = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)); /* si noti il cast a "struct sockaddr *", ovvero al tipo generico degli indirizzi delle socket */
    if (rv == -1) {
        perror("bind");
        close(sockfd); /* Chiude la socket prima di uscire */
        exit(EXIT_FAILURE);
    }


    /*
        Il server esegue ciclicamente il seguente processo:
        * riceve un messaggio di richiesta (ovvero due interi a 32 bit da sommare)
        * invia un messaggio di risposta (ovvero un intero a 32 bit pari alla somma dei numeri ricevuti nella richiesta),
          usando l'indirizzo IP e numero di porta di origine nella richiesta come indirizzo di ritorno per la risposta.
    */
    while (1) {
        /* Struttura popolata da recvfrom con l'indirizzo del mittente */
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        memset(&client_addr, 0, sizeof(client_addr));

        uint32_t input[2]; /* buffer dove saranno scritti i byte ricevuti*/

        /* 
            Riceve un datagramma dal client.
            Si noti che la lunghezza della struttura dati per l'indirizzo del mittente (client_addr_len) viene passsata come
            puntatore, perche' il valore corrente viene usato per verificare che il buffer sia sufficientemente lungo ma
            poi puo' essere cambiato per indicare la effettiva dimensione dell'indirizzo (non dovrebbe capitare).
            */
        ssize_t read_count = recvfrom(sockfd, &input, sizeof(input), 0, (struct sockaddr *)&client_addr, &client_addr_len);
        /*                            ^      ^           ^       ^                          ^               ^
          file descriptor della socket|      |           |       |                          |               |
          puntatore ai dati da spedire ------*           |       |                          |               |
          numero di byte da spedire ---------------------*       |                          |               |
          opzioni -----------------------------------------------*                          |               |
          struttura per indirizzo mittente -------------------------------------------------*               |
          puntatore alla lunghezza dell'indirizzo ----------------------------------------------------------*
        
        */

        /*
            Se non fossimo stati interessati all'indirizzo del mittente, avremmo potuti passare NULL e 0 come argomenti
            degli ultimi due parametri di recvfrom (oppure usare recv) 
        */

        /* recvfrom restiuisce -1 in caso di errore (dettaglio in errno) o il numero di byte letti */

        if (read_count == -1) {
            perror("recvfrom");
            continue; // questo server non risponde a messaggi errati
        } else if (read_count != sizeof(input)) { /* verifico che il numero di byte letti sia quanto atteso */
            fprintf(stderr, "Attesi %ld byte ma letti %ld\n", sizeof(input), read_count); /* la elle in %ld sta per tipo (unsigned) long int */
            continue; // questo server non risponde a messaggi errati
        }

        /* Converto l'indirizzo di rete del mittente in stringa per una stampa di log */
        const int STRING_LENGTH = 15;
        char client_addr_str[STRING_LENGTH + 1]; /* un carattere in piu' per il terminatore della stringa*/
        if (!inet_ntop(AF_INET, &client_addr.sin_addr, client_addr_str, sizeof(client_addr_str))) { /* il corpo dell'if non dovrebbe essere mai eseguito */
            perror("inet_ntop");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        /* Converto gli argomenti nella rappresentazione dell'host */
        uint32_t arg1 = ntohl(input[0]);
        uint32_t arg2 = ntohl(input[1]);

        /* Si noti la conversione del numero di porta */
        fprintf(stderr, "Ricevuto messaggio da %s:%d: %u + %u\n", client_addr_str, ntohs(client_addr.sin_port), arg1, arg2);

        uint32_t sum = arg1 + arg2;

        uint32_t data_to_send = htonl(sum); /* Converto il risultato in network byte order */

        sleep(10); /* una sleep dio 10 secondi per facilitare i test */

        /*
            Invia un datagramma al client. Gli argomenti hanno un significato analogo (ma complementare) a quanto visto per
            recvfrom
        */
        ssize_t write_count = sendto(sockfd, &data_to_send, (socklen_t)sizeof(sum), 0,(struct sockaddr *)&client_addr, client_addr_len);

        /* recvfrom restiuisce -1 in caso di errore (dettagliato in errno) o il numero di byte scritti */

        if (write_count == -1) {
            perror("sendto");
            continue; // passa avanti
        }
    }

    /* Questo e' un semplice serve di esempio, che NON termina mai. Infatti, questa parte di codice non viene mai eseguita. */
   
    /* Chiude la socket */
    close(sockfd);

    return EXIT_SUCCESS;
}