#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n;
	scanf("%d", &n);

	int *score = (int *)malloc(n * sizeof(int));
	int *rank = (int *)malloc(n * sizeof(int));

	for(int i = 0 ; i < n ; i++) {
		scanf("%d", &score[i]);
	}

	for(int i = 0 ; i < n ; i++) {
		int cnt = 0;
		for(int j = 0 ; j < n ; j++) {
			if(i != j && score[i] < score[j])
				cnt++;
		}
		rank[i] = cnt + 1;
	}
/*	for(int i = 0 ; i < n ; i++) {
		printf("%d\n", rank[i]);
	}*/

	int q;
	scanf("%d", &q);

	for(int i = 0 ; i < q ; i++) {
		int a;
		scanf("%d", &a);
		for(int j = 0 ; j < n ; j++) {
			if(a == rank[j]) {
				printf("%d\n", score[j]);
				break;
			}
		}
	}
	return 0;
}
