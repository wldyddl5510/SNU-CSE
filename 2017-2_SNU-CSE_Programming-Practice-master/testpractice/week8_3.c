#include <stdio.h>
#include <stdlib.h>

int *number_malloc(int n) {
	int *ans = (int *)malloc(n *sizeof(int));
	for(int i = 0 ; i < n ; i++) {
		ans[i] = i+1;
	}
	return ans;
}

int main(void) {
	int *arr;
	int num;
	scanf("%d", &num);
	arr = number_malloc(num);
	int i;
	for(int i = 0 ; i < num ; i++) {
		printf("%d ", arr[i]);
	}
}
