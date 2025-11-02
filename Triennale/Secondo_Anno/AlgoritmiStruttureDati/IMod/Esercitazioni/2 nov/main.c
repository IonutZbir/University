/*
 * Progettare un algoritmo (efficiente) che, dato un array ordinato
 * A[1:n] di n interi e un intero x, trova (se esistono) due indici i e j,
 * i<j, tale che A[i]+A[j]=x.
 */

#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

typedef struct array {
    int len;
    int *data;
} array;

int binarySearch(int *arr, int n, int start, int end) {
    if (start > end)
        return -1;
    int m = (end + start) / 2;
    if (arr[m] == n)
        return m;
    if (arr[m] > n)
        return binarySearch(arr, n, start, m - 1);
    else
        return binarySearch(arr, n, m + 1, end);
}

int *soluzione1(array a, int x) {
    // soluzione banale, in tempo quadratico
    int *output = malloc(sizeof(int) * 2);
    for (int i = 0; i < a.len - 1; i++) {
        for (int j = i + 1; j < a.len; j++) {
            if (a.data[i] + a.data[j] == x) {
                output[0] = i;
                output[1] = j;
                return output;
            }
        }
    }
    output[0] = -1;
    output[1] = -1;
    return output;
}

int *soluzione2(array a, int x) {
    // soluzione meno  banale, in tempo n log n
    int *output = malloc(sizeof(int) * 2);
    int y; // incognita
    int j; // indice incognita
    for (int i = 0; i < a.len - 1; i++) {
        y = x - a.data[i];
        j = binarySearch(a.data, y, 0, a.len);
        if (j > -1) {
            output[0] = i;
            output[1] = j;
            return output;
        }
    }
    output[0] = -1;
    output[1] = -1;
    return output;
}

int *soluzione3(array a, int x) {
    // soluzione lineare, efficiente
    int i = 0;
    int j = a.len - 1;
    int *output = malloc(sizeof(int) * 2);
    while (i < j) {
        if (a.data[i] + a.data[j] == x) {
            output[0] = i;
            output[1] = j;
            return output;
        }
        if (a.data[i] + a.data[j] < x)
            i++;
        else
            j--;
    }
    output[0] = -1;
    output[1] = -1;
    return output;
}

int binarySearchLastOccurence(int *arr, int n, int start, int end) {
    if (start > end)
        return -1;
    int m = (end + start) / 2;
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

int main() {
    int a[] = {1,
               1,
               1,
               1,
               3,
               5,
               6,
               7,
               10};
    int j = binarySearchLastOccurence(a, a[0], 0, ARRAY_SIZE(a));

    printf("[INFO]: Ultima Occorenza di %d è %d \n", a[0], j);
    printf("[INFO]: Ci sono %d minimi\n", j + 1);

    return 0;
}
