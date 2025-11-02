#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// p = i * col + j
// j = p%col
// i = p/col

float **make_matrice(int, int);
float **make_matrice_esercizio(int, int, float *, int);
void print_matrice(float **, int, int);

void main(int dim, char *args[])
{
    // args[1] = num colonne
    int col, row;
    float val, *a = malloc(sizeof(float) * dim - 2);
    float **m;
    if (sscanf(args[1], "%d", &col) == 0)
    {
        printf("Stringa di help\n");
        return;
    }
    for (int i = 2; i < dim; i++)
    {
        if (sscanf(args[i], "%f", &val) == 1)
        {
            a[i - 2] = val;
        }
        else
        {
            a[i - 2] = 0;
        }
    }
    row = ((dim - 2) / col);
    if ((dim - 2) % col != 0)
    {
        row++;
    }
    m = make_matrice_esercizio(row, col, a, dim - 2);
    print_matrice(m, row, col);
}

float **make_matrice(int row, int col)
{
    float **m = malloc(sizeof(float *) * row);
    if (m == NULL)
        return NULL;
    for (int i = 0; i < row; i++)
    {
        m[i] = malloc(sizeof(float) * col);
        if (m[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(m[j]);
            }
            free(m);
            return NULL;
        }
        for (int j = 0; j < col; j++)
        {
            m[i][j] = i * j + 1;
        }
    }
    return m;
}

void print_matrice(float **m, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        printf("[ ");
        for (int j = 0; j < col; j++)
        {
            printf("%4.1f ", m[i][j]);
        }
        printf("]\n");
    }
}

float **make_matrice_esercizio(int row, int col, float *a, int dim)
{
    float **m = malloc(sizeof(float *) * row);
    int offset;
    if (m == NULL)
        return NULL;
    for (int i = 0; i < row; i++)
    {
        m[i] = malloc(sizeof(float) * col);
        if (m[i] == NULL){
            for (int j = 0; j < i; j++)
            {
                free(m[j]);
            }
            free(m);
            return NULL;
        }
        for (int j = 0; j < col; j++)
        {
            offset = i * col + j;
            if (offset < dim)
                m[i][j] = a[offset];
            else
                m[i][j] = 0;
        }
    }
    return m;
}
