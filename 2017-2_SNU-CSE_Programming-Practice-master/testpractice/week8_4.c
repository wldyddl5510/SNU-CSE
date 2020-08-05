#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int swap;
	swap = *b;
	*b = *a;
	*a = swap;
}

int *sort(int n, int *arr1) {
	for(int i = 0 ; i < n-1 ; i++) {
		for(int j = 0 ; j < n-1-i ; j++) {
			if(arr1[j+1] > arr1[j])
				swap(&arr1[j+1], &arr1[j]);
		}
	}
	return arr1;
}

int main(void) {
	int *sorted;
	int original[10] = {2, 1, 3, 4, 5, 8, 10 ,7, 6, 9};
	sorted = sort(10, original);
	for(int i = 0 ; i < 10 ; i++) {
		printf("%d ", sorted[i]);
	}
	return 0;
}
