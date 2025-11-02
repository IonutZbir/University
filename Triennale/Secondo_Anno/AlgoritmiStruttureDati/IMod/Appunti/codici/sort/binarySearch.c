#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *arr, int n, int start, int end) {
    if (start > end)
        return -1;
    int m = (start + end) / 2;
    if (arr[m] == n)
        return m;
    if (arr[m] > n)
        return binarySearch(arr, n, start, m - 1);
    else
        return binarySearch(arr, n, m + 1, end);
}
int binary_search(int arr[], int low, int high, int x) {
    if (low > high) {
        return -1; // Element not found
    }

    int mid = (low + high) / 2;

    // Check if x is present at mid
    if (arr[mid] == x) {
        return mid;
    }

    // If x is greater, ignore left half
    if (arr[mid] < x) {
        return binary_search(arr, mid + 1, high, x);
    }

    // If x is smaller, ignore right half
    return binary_search(arr, low, mid - 1, x);
}
int main() {
    int a[] = {1, 1, 1, 1, 2, 2, 2, 2, 2, 2};
    printf("il numero sta nella posizione:%d\n", binary_search(a, 0, 10, 1));
}
