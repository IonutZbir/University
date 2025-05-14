#include <stdio.h>
#include <stdlib.h>

struct point{
    float x, y;
};
typedef struct point point;

struct segment
{
    point *a;
    point *b;
};
typedef struct segment segment;

segment *new_segment(float ax, float ay, float bx, float by){
    point *p_a = malloc(sizeof(point));
    point *p_b = malloc(sizeof(point));
    segment *new_seg = malloc(sizeof(new_seg));
    p_a->x = ax;
    p_a->y = ay;
    p_b->x = bx;
    p_b->y = by;
    new_seg->a = p_a;
    new_seg->b = p_b;
    return new_seg;
}

void main(){
    segment *seg;
    seg = new_segment(2, 3.3, 4.5, 6.7);
    printf("A: (%f, %f)\n", seg->a->x, seg->a->y);
    printf("B: (%f, %f) \n", seg->b->x, seg->b->y); 
}

int *centering(int *mat, int r, int c)
{
    int *n_mat = calloc(c * r, sizeof(int));
    int mod = 0;
    if (c % 2 == 0)
        mod = 1;
    for (int row = 0; row < r; row++)
    {
        int half = c / 2;
        int ones_row = 0; // quanti 1 ci sono per riga
        for (int col = 0; col < c; col++)
        {
            if (mat[c * row + col] == 1)
            {
                ones_row++;
            }
        }
        if (ones_row == c || ones_row == 0)
        {
            for (int col = 0; col < c; col++)
            {
                n_mat[row * c + col] = mat[row * c + col];
            }
        }
        else
        {
            n_mat[row * c + half] = 1;
            ones_row--;
            int l = 0; // flag
            int k = 1; // offset index half
            for (int j = 0; j < ones_row; j++)
            {
                half = c/2;
                if(l == 2)
                    k++;
                if (j % 2 == mod)
                {
                    half = half + k;
                    n_mat[row * c + half] = 1;
                    l++;
                }
                else
                {
                    half = half - k;
                    n_mat[row * c + half] = 1;
                    l++;
                }
            }
        }
    }
    return n_mat;
}
void ciao()
{
    int r = 6;
    int c = 5;
    int m[] = {0, 1, 1, 0, 0,
               1, 0, 1, 0, 0,
               1, 0, 1, 0, 1,
               0, 1, 1, 0, 0,
               0, 0, 0, 0, 0,
               1, 1, 1, 1, 1};
    int *mtx = centering(m, r, c);
    for (int row = 0; row < r; row++)
    {
        for (int col = 0; col < c; col++)
        {
            if (col == 0)
            {
                printf("[%d, ", mtx[(c * row) + col]);
            }
            else if (col == c - 1)
            {
                printf("%d]", mtx[(c * row) + col]);
            }
            else
            {
                printf("%d, ", mtx[(c * row) + col]);
            }
        }
        printf("\n");
    }
}