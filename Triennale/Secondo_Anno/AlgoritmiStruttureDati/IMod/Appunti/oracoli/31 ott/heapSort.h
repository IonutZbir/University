#ifndef HEAP_SORT_H
#define HEAP_SORT_H

typedef struct heap{
	int heapSize;
	int *heapArr;
}heap;

int left(int);
int right(int);
void swap(int*, int*);
void fixHeap(int, heap*);
void heapify_recursive(heap*, int);
void heapify(heap*);
void heapSort_p(heap*);
void heapSort(heap*);
void printHeap(heap*);

#endif // HEAP_SORT_H
