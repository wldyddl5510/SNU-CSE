#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n;
	scanf("%d", &n);

	int *A = (int *)malloc(n * sizeof(int));
	for(int i = 0 ; i < n ; i++) {
		scanf("%d", &A[i]);
	}

	int m;
	scanf("%d", &m);

	int *B = (int *) malloc(m * sizeof(int));
	for(int i = 0 ; i < m ; i++) {
		scanf("%d", &B[i]);
	}

	int k = 0;
	int cnt = 0;
	int *loca = (int *)malloc(n * sizeof(int));
	while(k < n) {
		int l = 0;
		while(l < m) {
			if(A[k+l] != B[l])
				break;
			l++;
		}
		if(l == m) {
			loca[cnt] = k;
			cnt++;
		}
		k++;
	}
	printf("%d\n", cnt);

	for(int i = 0 ; i < cnt ; i++) { 
		printf("%d ", loca[i]);
	}
	printf("\n");
	free(A);
	free(B);
	free(loca);
	return 0;
}
