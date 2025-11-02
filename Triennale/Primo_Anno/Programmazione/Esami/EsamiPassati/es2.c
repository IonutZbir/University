#include <stdio.h>
#include <stdlib.h>

// Funzione per spostare le sequenze di 1 al centro delle righe
int *centering(int* mat, int r, int c) {
    // Allocazione di memoria per la matrice modificata
    int *n_mat = calloc(r * c, sizeof(int));

    // Iterazione attraverso le righe della matrice di input
    for (int row = 0; row < r; row++) {
        int ones_row = 0;

        // Conteggio degli elementi 1 nella riga corrente
        for (int col = 0; col < c; col++) {
            if (mat[row * c + col] == 1) {
                ones_row++;
            }
        }

        // Se la riga è completamente riempita di 1 o completamente riempita di 0, copia la riga di input nella matrice modificata
        if (ones_row == c || ones_row == 0) {
            for (int col = 0; col < c; col++) {
                n_mat[row * c + col] = mat[row * c + col];
            }
        } 
        // Altrimenti, sposta gli elementi 1 al centro della riga
        else {
            // Calcolo della colonna di partenza per posizionare gli elementi 1 al centro
            int start_col = (c - ones_row + 1) / 2;

            // Posizionamento degli elementi 1 nella matrice modificata
            for (int col = start_col; col < start_col + ones_row; col++) {
                n_mat[row * c + col] = 1;
            }
        }
    }

    // Restituzione della matrice modificata
    return n_mat;
}

int main() {
    int r = 6;
    int c = 6;

    // Matrice di input
    int m[] = {0, 1, 1, 0, 0, 0,
               1, 0, 1, 0, 0, 0,
               1, 0, 1, 0, 1, 0,
               0, 1, 1, 0, 0, 0,
               0, 0, 0, 0, 0, 0,
               1, 1, 1, 1, 1, 1};

    // Chiamata alla funzione centering per ottenere la matrice modificata
    int *mtx = centering(m, r, c);

    // Stampa della matrice risultante
    for (int row = 0; row < r; row++) {
        for (int col = 0; col < c; col++) {
            if (col == 0) {
                printf("[%d, ", mtx[row * c + col]);
            } else if (col == c - 1) {
                printf("%d]", mtx[row * c + col]);
            } else {
                printf("%d, ", mtx[row * c + col]);
            }
        }
        printf("\n");
    }

    // Liberazione della memoria allocata per la matrice modificata
    free(mtx);

    return 0;
}