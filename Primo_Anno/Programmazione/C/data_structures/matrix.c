#include <stdio.h>
#include <stdlib.h>

struct matrix
{
    int **data;
    int rows;
    int cols;
    int det;     
};

typedef struct matrix matrix;
matrix matrix_init(int rows, int cols);
matrix append(matrix m, int elem);
matrix insert(matrix m, int elem, int pos);
matrix ladder(matrix m);
matrix determinat(matrix m);
matrix insert_all(matrix m, int mul);
void print_matrix(matrix m);

void main(){
    matrix m = matrix_init(1,1);
    m = insert_all(m, 2);
    print_matrix(m);
    m = determinat(m);
    printf("Il determinante e': %d\n", m.det);

}


matrix matrix_init(int rows, int cols){
    matrix m = {NULL, rows, cols, 0};
    m.data = calloc(rows , sizeof(int)); // primo parametro indica il numero di elementi, il secondo quanti byte allocare per ciascun elemento, inoltre iniziallizza tutto a 0
    for(int i = 0; i < rows; i++){
        m.data[i] = malloc(cols * sizeof(int));
    }
    return m;
}

matrix insert_all(matrix m, int mul){
    for(int i = 0; i < m.rows; i++){
        for(int j = 0; j < m.cols; j++){
           m.data[i][j] = (i + j + 1) * mul;
        }
    }
    return m;
}

matrix determinat(matrix m){
    int det = 0;
    if(m.rows == 1 && m.cols == 1){
        det = m.data[0][0];
    }
    if(m.rows == 2 && m.cols == 2){
        det = (m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0]);
    }
    m.det = det;
    return m;
}

void print_matrix(matrix m){
    printf("Matrix %d x %d\n", m.rows, m.cols);
    for(int i = 0; i < m.rows; i++){
        printf("[");
        for(int j = 0; j < m.cols; j++){
            printf(" %d ", m.data[i][j]);
        }
        printf("]\n");
    }
}

