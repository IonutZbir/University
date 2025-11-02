#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

typedef struct array {
    int len;
    int *arr;
} array;

void merge(int *arr, int sx, int cx, int rx) {
    int i = 0;
    int k1 = sx;
    int k2 = cx;
    int *aux = malloc((rx - sx) * sizeof(int));

    while (k1 < cx && k2 < rx) {
        if (arr[k1] <= arr[k2]) {
            aux[i] = arr[k1];
            k1++;
        } else {
            aux[i] = arr[k2];
            k2++;
        }
        i++;
    }
    while (k1 < cx) {
        aux[i] = arr[k1];
        k1++;
        i++;
    }
    while (k2 < rx) {
        aux[i] = arr[k2];
        k2++;
        i++;
    }

    for (int j = 0; j < rx - sx; j++) {
        arr[sx + j] = aux[j];
    }

    free(aux);
}

void mergeSort_p(int *arr, int i, int f) {
    if (f - i < 2)
        return; // f == i || f == i + 1
    int m = (f + i) / 2;
    mergeSort_p(arr, i, m);
    mergeSort_p(arr, m, f);
    merge(arr, i, m, f);
}

void mergeSort(array *a) {
    mergeSort_p(a->arr, 0, a->len);
}

int main() {
    int a[] = {7, 6, 5, 4, 4, 3, 2, 1, 1};
    // int a[] = {7, 2, 4, 5, 3, 1, 5, 6};

    array *v = malloc(sizeof(array));
    int len = ARRAY_SIZE(a);
    v->len = len;
    v->arr = malloc(sizeof(int) * v->len);
    for (int i = 0; i < v->len; i++) {
        v->arr[i] = a[i];
    }

    mergeSort(v);

    for (int i = 0; i < v->len; i++) {
        printf("%d ", v->arr[i]);
    }
    printf("\n");

    free(v->arr);
    free(v);

    return 0;
}
