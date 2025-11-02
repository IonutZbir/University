#include <stdlib.h> /* per EXIT_SUCCESS */
#include <stdint.h> /* per uint32_t */
#include <stdio.h>  /* per printf */

int main(int argc, char* argv[]) {
    uint32_t a = 0x01234567u;
    unsigned char *ptr = (unsigned char *)&a;

    /*
        Stampo 4 byte (in formato esadecimale), per un totale di 32 bit,
        partendo dall'indirizzo contenuto nel puntatore ptr.

        Nella printf:
            %p specifica un puntatore
            %02x specifica un numero in formato esadecimale allineato a destra
                 in un campo di ampiezza 2 con riempimento di zeri a sinistra.
                 Si noti che se il numero fosse maggiore di 255, sarebbero stampate
                 piu' di 2 cifre esadecimali.
                
    */

    printf("%p = %02x\n", ptr + 0, ptr[0]);
    printf("%p = %02x\n", ptr + 1, ptr[1]);
    printf("%p = %02x\n", ptr + 2, ptr[2]);
    printf("%p = %02x\n", ptr + 3, ptr[3]);

    /*
        Con un processore x64, l'output e' simile a quanto segue:

        0x7fffffffdb8c = 67
        0x7fffffffdb8d = 45
        0x7fffffffdb8e = 23
        0x7fffffffdb8f = 01

        Si noti che i byte del numero 0x01234567u sono scritti in memoria dal
        meno significativo al piu' significativo, cioe' nell'ordine little-endian.
    */
    return EXIT_SUCCESS;
}