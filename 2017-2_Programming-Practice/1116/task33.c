#include <stdio.h>
#include <stdlib.h>

int main(void){
	int n, m, i, j, k;
	int *arr1;
	int *arr2;

	scanf("%d %d", &n, &m);

	arr1 = (int *)malloc(sizeof(int) * n);
	arr2 = (int *)malloc(sizeof(int) * m);

	for (k = 0; k < n; k++)
		scanf("%d", &arr1[k]);

	for (k = 0; k < m; k++)
		scanf("%d", &arr2[k]);

	i = 0;
	j = 0;
	while ((i < n) && (j < m)) {
		if (arr1[i] < arr2[j]) 
			printf("%d ", arr1[i++]);
		else 
			printf("%d ", arr2[j++]);
	}

	while (i < n)
		printf("%d ",arr1[i++]);
	while (j < m)
		printf("%d ",arr2[j++]);

	printf("\n");

	free(arr1);
	free(arr2);

	return 0;
}
