#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n;

	scanf("%d", &n);

	int *score = (int*) malloc(n * sizeof(int));
	int *rank = malloc(n * sizeof(int));

	for(int i = 0 ; i < n ; i++) {
		scanf("%d", &score[i]);
	}

	for(int i = 0 ; i < n ; i++) {
		int cnt = 0;
		for(int j = 0 ; j < n ; j++) {
			if(score[i] < score[j])
				cnt++;
		}
		rank[i] = (cnt + 1);
	}

	for(int i = 0 ; i < n ; i++) {
		printf("%d ", rank[i]);
	}
	printf("\n");

	return 0;
}
