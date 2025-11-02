#include "heapSort.h"
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

typedef struct oracolo {
    int len;
    int *data;
} oracolo;

int binarySearchLastOccurence(int *arr, int n, int start, int end) {
    if (start > end)
        return -1;
    int m = (end - start) / 2;
    if (arr[m] == n) {
        int nextInstance = binarySearchLastOccurence(arr, n, m + 1, end);
        if (nextInstance == -1)
            return m; // Questo è l'ultimo elemento uguale a n
        else
            return nextInstance; // Restituisci l'indice dell'ultima istanza trovata nella parte destra
    }
    if (arr[m] > n)
        return binarySearchLastOccurence(arr, n, start, m - 1);
    else
        return binarySearchLastOccurence(arr, n, m + 1, end);
}

int binarySearchFirstOccurence(int *arr, int n, int start, int end) {
    if (start > end)
        return -1;
    int m = (start + end) / 2;
    if (arr[m] == n)
        return m;
    if (arr[m] > n)
        return binarySearchFirstOccurence(arr, n, start, m - 1);
    else
        return binarySearchFirstOccurence(arr, n, m + 1, end);
}

oracolo *makeOracolo(int *arr, int len) {
    // usando un algoritmo di ordinamento O(n log n)
    heap *heapOracolo = malloc(sizeof(heap));
    heapOracolo->heapSize = len;
    heapOracolo->heapArr = malloc(heapOracolo->heapSize * sizeof(int));
    for (int i = 0; i < heapOracolo->heapSize; i++) {
        heapOracolo->heapArr[i] = arr[i];
    }

    //	printHeap(&heapOracolo);
    heapSort(heapOracolo);
    //	printHeap(&heapOracolo);

    oracolo *newOracolo = malloc(sizeof(oracolo));
    newOracolo->len = heapOracolo->heapSize;
    newOracolo->data = malloc(newOracolo->len * sizeof(int));

    for (int i = 0; i < newOracolo->len; i++) {
        newOracolo->data[i] = heapOracolo->heapArr[i];
    }

    free(heapOracolo->heapArr);
    return newOracolo;
}

int queryOracolo(oracolo *o, int a, int b) {
    // TODO verificare cosa restituisce la binarySearch
    int i, j, res;
    if (a < b) {
        i = binarySearchFirstOccurence(o->data, a, 0, o->len);
        j = binarySearchLastOccurence(o->data, b, 0, o->len);
        res = j - i + 1;
    } else if (a > b) {
        i = binarySearchLastOccurence(o->data, a, 0, o->len);
        j = binarySearchFirstOccurence(o->data, b, 0, o->len);
        res = j - j + 1;
    }
    printf("i: %d, j: %d\n", i, j);

    return res;
}

int main() {

    int a[] = {1, 10, 4, 5, 5, 20, 3, 3, 10};
    int len = ARRAY_SIZE(a);
    int x = 3;
    int y = 10;
    oracolo *o = makeOracolo(a, len);

    printf("%d\n", o->len);

    for (int i = 0; i < o->len; i++) {
        printf("%d ", o->data[i]);
    }
    printf("\n");

    int res = queryOracolo(o, x, y);
    printf("Ci sono %d numeri tra %d, %d\n", res, x, y);

    int k[] = {1, 1, 1, 1, 2, 2, 2, 2, 2, 2};
    int j = binarySearchFirstOccurence(k, 2, 0, 10);
    printf("%d\n", j);

    return 0;
}
