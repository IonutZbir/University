
#include <stdlib.h>      /* per EXIT_SUCCESS */
#include <stdint.h>      /* per uint32_t */
#include <stdio.h>       /* per fprintf */
#include <netinet/in.h>  /* per htonl e mthol*/

void print_number(uint32_t); /* Prototipo di una funzione ausiliaria definita in fondo*/

int main(int argc, char *argv[]) {
    uint32_t n = 0x01234567u; /* Il prefisso 0x per il formato esadecimale, il suffisso u per unsigned */

    printf("Rappresentazione dell'host:\n");
    print_number(n);
    printf("------\n");

    printf("Rappresentazione di rete:\n");
    /* Converte un intero a 32 bit da host a network byte order */
    uint32_t nn = htonl(n); /* Mnemonico: (h)ost to (n)etwork (l)ong (32 bit)*/
    print_number(nn);
    printf("------\n");


    printf("Indietro alla rappresentazione dell'host:\n");
    /* Converte un intero a 32 bit da network a host byte order */
    uint32_t nh = ntohl(nn); /* Mnemonico: (n)etwork to (h)ost (l)ong (32 bit)*/
    print_number(nh);
    printf("------\n");

    /* Esistono funzioni analoghe (htons e ntohs) che gestiscono interi a 16 bit [(s)hort] (usati per i numeri di porta) */

    /*
        Nota: lo standard non prescrive la dimensione in bit dei tipi short, int e long, che dipende dall'architettura del processore.
        Pone pero' il vincolo:

        2 <= sizeof(short) <= sizeof(int) <= sizeof(long)

        Avendo un processore a x64, si puo' ottenere il seguente risultato: 

            sizeof(short) = 2
            sizeof(int) = 4
            sizeof(long) = 8

    */

   printf("sizeof(short) = %ld\nsizeof(int) = %ld\nsizeof(long) = %ld\n", sizeof(short), sizeof(int), sizeof(long));

    return EXIT_SUCCESS;
}

void print_number(uint32_t n) {
    unsigned char *ptr = (unsigned char *)&n;
    printf("%p = %02x\n", ptr + 0, ptr[0]);
    printf("%p = %02x\n", ptr + 1, ptr[1]);
    printf("%p = %02x\n", ptr + 2, ptr[2]);
    printf("%p = %02x\n", ptr + 3, ptr[3]);
}