#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

typedef struct array {
    int len;
    int max;
    int *data;
} array;

typedef struct oracolo {
    int *data;
    int len;
} oracolo;

void printArr(int *arr, int dim) {
    for (int i = 0; i < dim; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

oracolo makeOracolo(array arr) {
    arr.max++;
    oracolo o;
    o.data = calloc(arr.max, sizeof(int));
    o.len = arr.max;
    for (int i = 0; i < arr.len; i++) {
        o.data[arr.data[i]]++;
    }

    printArr(o.data, o.len);

    for (int i = 1; i < o.len; i++) {
        o.data[i] = o.data[i] + o.data[i - 1];
    }
    return o;
}

int queryOracolo(oracolo o, int a, int b) {
    if (b > o.len)
        b = o.len - 1;
    if (a <= 1)
        return o.data[b];
    else
        return o.data[b] - o.data[a - 1];
}
int main() {
    int n1 = 2;
    int n2 = 30;
    int res;
    int a[] = {1, 10, 4, 5, 5, 20, 3, 3};
    array v;
    v.len = ARRAY_SIZE(a);
    v.max = 20;
    v.data = malloc(sizeof(int) * v.len);
    for (int i = 0; i < v.len; i++) {
        v.data[i] = a[i];
    }

    oracolo o = makeOracolo(v);

    printArr(o.data, o.len);
    printArr(v.data, v.len);

    res = queryOracolo(o, n1, n2);

    printf("Ci sono %d numeri tra %d e %d", res, n1, n2);

    return 0;
}
