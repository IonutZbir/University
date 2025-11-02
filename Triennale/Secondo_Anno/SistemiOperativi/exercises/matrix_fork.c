/*
Scrivere un programma che esegue la moltiplicazione tra matrici 3x3 usando la
programmazione parallela.
    - Il primo processo figlio computa la prima colonna.
    - Il secondo processo figlio computa la seconda colonna.
    - Il processo padre computa la terza colonna e riceve dai figli i due
vettori colonna computati e compone la matrice finale e la stampa.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#define N 3
#define PIPE_RD 0
#define PIPE_WR 1

typedef struct Matrix {
    int **data;
    int cols;
    int rows;
} Matrix;

Matrix matrix_product_vector(Matrix *m, Matrix *v);
Matrix matrix_get_column(Matrix *m, int col);
Matrix matrix_init(int rows, int cols);
void matrix_insert_all(Matrix *m, int mul);

Matrix matrix_init(int rows, int cols) {
    Matrix m = {NULL, cols, rows};
    m.data = (int **)calloc(rows, sizeof(int *));
    // primo parametro indica il numero di elementi, il secondo quanti byte
    // allocare per ciascun elemento, inoltre iniziallizza tutto a 0

    if (m.data == NULL) {
        fprintf(stderr, "[ERROR]: BUY MORE RAM!!\n");
        exit(-1);
    }

    for (int i = 0; i < rows; i++) {
        m.data[i] = (int *)calloc(cols, sizeof(int));
        if (m.data[i] == NULL) {
            fprintf(stderr, "[ERROR]: BUY MORE RAM!!\n");
            exit(-1);
        }
    }
    return m;
}

void matrix_insert_all(Matrix *m, int mul) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->data[i][j] = (i + j + 1) * mul;
        }
    }
}

Matrix matrix_product_vector(Matrix *m, Matrix *v) {
    if (m->cols != v->rows || v->cols != 1) {
        fprintf(stderr, "[ERROR]: Can't do product!!\n");
        exit(2);
    }
    Matrix res_col = matrix_init(m->rows, 1);
    for (int r = 0; r < m->rows; r++) {
        int k = 0;
        for (int c = 0; c < m->cols; c++) {
            k = (m->data[r][c] * v->data[c][0]) + k;
        }
        res_col.data[r][0] = k;
    }
    return res_col;
}

Matrix matrix_get_column(Matrix *m, int col) {
    Matrix c = matrix_init(m->rows, 1);
    for (int r = 0; r < m->rows; r++) {
        c.data[r][0] = m->data[r][col];
    }
    return c;
}

void matrix_print(Matrix *m) {
    printf("\nMatrix (%d x %d)\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        printf("[");
        for (int j = 0; j < m->cols; j++) {
            printf("%4d", m->data[i][j]);
        }
        printf("   ]\n");
    }
    printf("\n");
}

int main() {

    Matrix m1 = matrix_init(N, N);
    Matrix m2 = matrix_init(N, N);

    matrix_insert_all(&m1, 1);
    matrix_insert_all(&m2, 2);

    pid_t p1, p2;
    int fd_p1[2], fd_p2[2];
    if (pipe(fd_p1) < 0 || pipe(fd_p2) < 0) {
        fprintf(stderr, "[ERROR]: Could not create pipes");
        exit(2);
    }
    if ((p1 = fork()) < 0) {
        fprintf(stderr, "[ERROR]: Could not create process");
        exit(1);
    }

    if (p1 == 0) {
        close(fd_p1[PIPE_RD]);
        Matrix col = matrix_get_column(&m2, 0);
        Matrix res_col = matrix_product_vector(&m1, &col);
        int buff[] = {*res_col.data[0], *res_col.data[1], *res_col.data[2]};
        write(fd_p1[PIPE_WR], &buff, sizeof(int) * res_col.cols * res_col.rows);
    } else if (p1 > 0) {
        if ((p2 = fork()) < 0) {
            fprintf(stderr, "[ERROR]: Could not create process");
            exit(1);
        }
        if (p2 == 0) {
            close(fd_p2[PIPE_RD]);
            Matrix col = matrix_get_column(&m2, 1);
            Matrix res_col = matrix_product_vector(&m1, &col);
            int buff[] = {*res_col.data[0], *res_col.data[1], *res_col.data[2]};
            write(fd_p2[PIPE_WR], &buff, sizeof(int) * res_col.cols * res_col.rows);
        } else if (p2 > 0) {
            close(fd_p1[PIPE_WR]);
            close(fd_p2[PIPE_WR]);
            int res_col1[N];
            int res_col2[N];

            read(fd_p1[PIPE_RD], &res_col1, sizeof(res_col1));
            read(fd_p2[PIPE_RD], &res_col2, sizeof(res_col2));

            Matrix col = matrix_get_column(&m2, 2);
            Matrix res_col3 = matrix_product_vector(&m1, &col);
            Matrix final_matrix = matrix_init(N, N);
            for (int i = 0; i < final_matrix.rows; i++) {
                final_matrix.data[i][0] = res_col1[i];
                final_matrix.data[i][1] = res_col2[i];
                final_matrix.data[i][2] = res_col3.data[i][0];
            }
            matrix_print(&m1);
            printf(" * \n");
            matrix_print(&m2);
            printf(" = \n");
            matrix_print(&final_matrix);
        }
    }

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);

    return 0;
}
