#include <stdio.h>
#include <stdlib.h>

int array_cmp(int n, int A[], int B[]) {
	for(int i = 0 ; i < n ; i++) {
		if(A[i] > B[i])
			return -1;
		else if (A[i] < B[i])
			return 1;
	}
	return 0;
}

int main(void) {
	int n;

	scanf("%d", &n);

	int *A = (int *) malloc(n * sizeof(int));
	int *B = (int *) malloc(n * sizeof(int));

	for(int i = 0 ; i < n ; i++) {
		scanf("%d", &A[i]);
	}
	for(int i = 0 ; i < n ; i++) {
		scanf("%d", &B[i]);
	}

	printf("%d\n", array_cmp(n, A, B));
	free(A);
	free(B);
	return 0;
}
