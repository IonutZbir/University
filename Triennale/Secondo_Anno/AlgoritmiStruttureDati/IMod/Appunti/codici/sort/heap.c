#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

typedef struct heap {
    int heapSize;
    int *heapArr;
} heap;
int left(int i) { return (2 * i) + 1; }

int right(int i) { return (2 * i) + 2; }

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void fixHeap(int pos, heap *H) {
    int sx, dx;
    int max = pos; // indexes in the array
    sx = left(pos);
    dx = right(pos);
    if (sx < H->heapSize && H->heapArr[sx] > H->heapArr[max]) {
        max = sx;
    }
    if (dx < H->heapSize && H->heapArr[dx] > H->heapArr[max]) {
        max = dx;
    }
    if (max != pos) {
        swap(&H->heapArr[pos], &H->heapArr[max]);
        fixHeap(max, H);
    }
}

void heapify_recursive(heap *H, int pos) { // l'array che sta dentro H non è ancora una heap
    int left_child = left(pos);
    int right_child = right(pos);
    if (pos < H->heapSize && H->heapSize > 1) {
        if (left(left_child) <= H->heapSize) {
            heapify_recursive(H, left_child);
        }
        if (right(right_child) <= H->heapSize) {
            heapify_recursive(H, right_child);
        }
        fixHeap(pos, H);
    }
}

void heapify(heap *H) {
    for (int i = H->heapSize / 2 - 1; i >= 0; i--)
        fixHeap(i, H);
}

void heapSort_p(heap *H) {
    // heapify(H);
    heapify_recursive(H, 0);

    for (int i = H->heapSize - 1; i >= 0; i--) {
        swap(&H->heapArr[0], &H->heapArr[i]);
        H->heapSize = i;
        fixHeap(0, H);
    }
}

void heapSort(heap *H) {
    int len = H->heapSize;
    heapSort_p(H);
    H->heapSize = len;
}

void printHeap(heap *H) {
    for (int i = 0; i < H->heapSize; i++)
        printf("%d ", H->heapArr[i]);
    printf("\n");
}

int main() {
    // int a[] = {4, 10, 7, 8, 2, 1, 14, 3, 9, 16};
    // int a[] = {4, 16, 10, 14, 7, 9, 3, 2, 8, 17};
    int a[] = {12, 11, 13, 5, 6, 7, 21};
    int len = ARRAY_SIZE(a);

    heap H;
    H.heapSize = len;
    H.heapArr = malloc(H.heapSize * sizeof(int));

    for (int i = 0; i < H.heapSize; i++) {
        H.heapArr[i] = a[i];
    }

    heapSort(&H);

    printHeap(&H);

    return 0;
}
