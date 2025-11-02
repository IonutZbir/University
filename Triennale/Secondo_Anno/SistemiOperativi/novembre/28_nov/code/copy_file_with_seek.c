/* Programma di copia di file con controllo errori minimale e reportistica. */

#include <ctype.h>
#include <fcntl.h> //Contiene le costanti che vengono utilizzate nelle chiamate di sistema relative al controllo dei file descriptors.
                   //In questo programma, O_RDONLY viene utilizzato per aprire il file di input in modalità sola lettura.
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUF_SIZE 8       // Dimensione del buffer: 4096 byte
#define OUTPUT_MODE 0700 // Bit di protezione per file di output

#define TRUE 1

long fileSize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0) {
        return st.st_size;
    } else {
        perror("[ERROR]: Error getting file size");
        return -1; // Indicates an error
    }
}

int main(int argc, char *argv[]) {
    int in_fd, out_fd;      // File descriptor per i file di input e output
    int rd_count, wt_count; // Contatori per la lettura e scrittura
    long size;
    char buffer[BUF_SIZE]; // Buffer per la lettura e scrittura dei dati

    char *source_code_file = argv[0];

    // Controllo del numero di argomenti
    if (argc != 4) {
        // Stampa un messaggio di errore se il numero di argomenti non è 
        // corretto
        fprintf(stderr, "[ERROR]: Errore di sintassi. Uso: %s input_file_path output_file_path indice_inziale \n", source_code_file);
        exit(1); // scrivo su STD_ERROR
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];
    long index = (long)atoi(argv[3]); // converte una stringa in intero poi con il cast in long

    // Apertura del file di input
    in_fd = open(input_filename, O_RDONLY); // Apre il file di origine
    if (in_fd < 0)
        exit(2); // Se non può aprirlo, esce

    size = fileSize(input_filename);
    printf("[INFO]: file size = %ld\n", size);

    if (index > size) {
        fprintf(stderr, "[ERROR]: L'indice (%ld) iniziale supera la lunghezza del file\n", index);
        exit(4);
    }
    printf("[INFO]: index = %ld\n", index);

    out_fd = creat(output_filename, OUTPUT_MODE); // Crea il file di destinazione
    if (out_fd < 0)
        exit(3); // Se non può crearlo, esce

    if (lseek(in_fd, index, SEEK_CUR) == -1)
        exit(4); // se non riesce a creare il cursore

    while (TRUE) {
        rd_count = read(in_fd, buffer, BUF_SIZE); // Legge un blocco di dati
        if (rd_count <= 0)
            break; // Se fine del file o errore, esce dal ciclo

        wt_count = write(out_fd, buffer, rd_count); // Scrive i dati
        if (wt_count <= 0)
            exit(5); // wt_count <= 0 è un errore
    }

    // Chiusura dei file
    close(in_fd);
    close(out_fd);

    if (rd_count == 0)
        exit(0); // Nessun errore sull’ultima lettura
    else
        exit(6); // Errore sull’ultima lettura
}
