#include <stdio.h>
#include <stdlib.h>

void integerSort(int *array, int k, int dim) {
    k++;
    int *y = calloc(k, sizeof(int));

    for (int i = 0; i < dim; i++) {
        y[array[i]]++;
    }

    int j = 0;
    for (int i = 0; i < k; i++) {
        while (y[i] > 0) {
            array[j] = i;
            j++;
            y[i]--;
        }
    }
    free(y);
}

int main() {
    int a[] = {5, 1, 6, 8, 6};
    int dim = sizeof(a) / sizeof(a[0]);

    integerSort(a, 8, dim);

    printf("Sorted array: \n");
    for (int i = 0; i < dim; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");

    return 0;
}
