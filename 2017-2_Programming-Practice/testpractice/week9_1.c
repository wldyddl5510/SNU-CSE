#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int n;
	scanf("%d", &n);

	int **a = (int**) malloc(n * sizeof(int));
	int **b = (int**) malloc(n * sizeof(int));
	int **ab = (int**) malloc(n * sizeof(int));

	for(int i = 0 ; i < n ; i++) {
		a[i] = (int*) malloc(n * sizeof(int));
		b[i] = (int*) malloc(n * sizeof(int));
		ab[i] = (int*) malloc(n * sizeof(int));
	}

	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < n ; j++) {
			scanf("%d", &a[i][j]);
		}
	}

	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < n ; j++) {
			scanf("%d", &b[i][j]);
		}
	}
	printf("DEBUG\n");

	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < n ; j++) {
			int sum = 0;
			for(int k = 0 ; k < n ; k++) {
				sum = sum + a[i][k] * b[k][j];
			}
			ab[i][j] = sum;
		}
	}
	printf("DEBUG\n");

	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < n ; j++) {
			printf("%d ", ab[i][j]);
		}
		printf("\n");
	}
	printf("DEBUG\n");

	for(int i = 0 ; i < n ; i++) {
		free(a[i]);
	}

	for(int i = 0 ; i < n ; i++) {
		free(b[i]);
	}

	for(int i = 0 ; i < n ; i++) {
		free(ab[i]);
	}
	printf("DEBUG\n");

	return 0;
}
