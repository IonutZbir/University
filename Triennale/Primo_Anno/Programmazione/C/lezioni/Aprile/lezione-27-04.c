#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// p = i * col + j
// j = p%col
// i = p/col


float *make_matrice(int, int);
void print_elem_pos(float *, int, int);
void print_matrice(float *, int, int);

void main(){
    int col = 5, row = 7;
    float *m = make_matrice(row, col);
    print_matrice(m, col, row);
    print_elem_pos(m, col, 4);
}

float *make_matrice(int row, int col){
    float *m = malloc(sizeof(int) * (row * col));
    int offset, j = 0;
    if(m == NULL)
        return NULL;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++ ){
            offset = col * i + j;
            m[offset] = i * j + 1;
        }
    }
    return m;
}

void print_matrice(float *m, int row, int col){
    int offset;
    for (int i = 0; i < row; i++)
    {   
        printf("[ ");
        for (int j = 0; j < col; j++)
        {
            offset = col * i + j;
            printf("%4.1f ", m[offset]);
        }
        printf("]\n");
    }
}

void print_elem_pos(float *m, int col, int pos){
    /*
    stampa l'elemento in posizione pos di m e le sue coordinata
    (riga, colonna) nella matrice m
    */
    int r = pos/col;
    int c = pos%col;
    printf("(%d , %d) -> %0.2f\n", r, c, m[pos]);
}