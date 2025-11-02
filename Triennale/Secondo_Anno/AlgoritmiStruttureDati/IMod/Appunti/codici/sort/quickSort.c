#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0])) 


typedef struct array{
	int len;
	int* data;
	
}array;

void swp(int *n1, int *n2){
	int temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

int partition(int* arr, int start, int end)
{
	int x = arr[start];
	int inf = start;
	int sup = end;
	while (1) {
		do {
			inf++;
		}while (inf <= end && arr[inf] <= x);
		do {
			sup--;
		}while(arr[sup] > x);
		if (inf < sup) {
			swp(&arr[inf], &arr[sup]);
		}else
			break;	
	}
	swp(&arr[start], &arr[sup]);
	return sup;
}

void quickSort_private(int *arr, int start, int end){
	if(start < end){
		int m = partition(arr, start, end);
		quickSort_private(arr, start, m);
		quickSort_private(arr, m + 1, end);
	}
}

void quickSort(array a){
	quickSort_private(a.data, 0, a.len - 1);
}

int main(){
	array a;
	int numeri[] = {5, 5, 6, 7, 1, 2, 3, 4};
	a.len = ARRAY_SIZE(numeri);
	a.data = malloc(a.len * sizeof(int));

	for (int i = 0; i < a.len; i++) {
		a.data[i] = numeri[i];	
	}
	
	quickSort(a);
	for (int i = 0; i < a.len; i++) {
		printf("%d " ,a.data[i]);	
	}
	free(a.data);
	return 0;
}
