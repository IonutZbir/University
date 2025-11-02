/* Programma di copia di file con controllo errori minimale e reportistica. */

#include <fcntl.h> //Contiene le costanti che vengono utilizzate nelle chiamate di sistema relative al controllo dei file descriptors.
                   //In questo programma, O_RDONLY viene utilizzato per aprire il file di input in modalità sola lettura.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 700     // Dimensione del buffer: 4096 byte
#define OUTPUT_MODE 0700 // Bit di protezione per file di output

#define TRUE 1

int main(int argc, char *argv[]) {
    int in_fd, out_fd;      // File descriptor per i file di input e output
    int rd_count, wt_count; // Contatori per la lettura e scrittura
    char buffer[BUF_SIZE];  // Buffer per la lettura e scrittura dei dati

    // Controllo del numero di argomenti
    if (argc != 3) {
        // Stampa un messaggio di errore se il numero di argomenti non è 
        // corretto
        fprintf(stderr, "Errore di sintassi. Uso: %s input_file_path output_file_path\n", argv[0]);
        exit(1); // scrivo su STD_ERROR
    }

    // Apertura del file di input
    in_fd = open(argv[1], O_RDONLY); // Apre il file di origine
    if (in_fd < 0)
        exit(2); // Se non può aprirlo, esce

    // Creazione del file di output
    // Nota: equivalenza tra
    // - creat(path, mode);
    // - open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
    // YES: Ken Thompson, the creator of Unix, once joked that the missing
    // letter was his largest regret in the design of Unix.
    out_fd = creat(argv[2], OUTPUT_MODE); // Crea il file di destinazione
    if (out_fd < 0)
        exit(3); // Se non può crearlo, esce

    // Ciclo di copia

    while (TRUE) {
        rd_count = read(in_fd, buffer, BUF_SIZE); // Legge un blocco di dati
        printf("%d\n", rd_count);
        if (rd_count <= 0)
            break; // Se fine del file o errore, esce dal ciclo

        wt_count = write(out_fd, buffer, rd_count); // Scrive i dati
        if (wt_count <= 0)
            exit(4); // wt_count <= 0 è un errore
    }

    // Chiusura dei file
    close(in_fd);
    close(out_fd);

    if (rd_count == 0)
        exit(0); // Nessun errore sull’ultima lettura
    else
        exit(5); // Errore sull’ultima lettura
}
