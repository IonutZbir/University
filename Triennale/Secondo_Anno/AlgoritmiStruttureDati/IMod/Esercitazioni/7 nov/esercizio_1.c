#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

typedef struct array {
    int len;
    int *data;
} array;

int maxRic(int *arr, int start, int end) { // trova l ultima occorenza
    if (start > end)
        return -1;
    int m = (start + end) / 2;
    if (arr[m] > arr[m + 1] && arr[m] > arr[m - 1])
        return m;
    if (arr[m] > arr[m + 1])
        return maxRic(arr, start, m - 1);
    else
        return maxRic(arr, m + 1, end);
}

int max(array *a) {
    int n = a->len;
    if (a->data[0] > a->data[1])
        return 0;
    if (a->data[n - 1] > a->data[n - 2])
        return n - 1;
    return maxRic(a->data, 1, n - 2);
}

int main() {
    int a[] = {20, 45, 33, 30, 50, 22, 20, 5};
    int len = ARRAY_SIZE(a);
    array *v = malloc(sizeof(array));
    v->len = len;
    v->data = malloc(sizeof(int) * v->len);
    for (int i = 0; i < v->len; i++) {
        v->data[i] = a[i];
    }
    int m = max(v);
    printf("Il massimo %d si trova in posizione %d:\n", v->data[m], m);

    return 0;
}
