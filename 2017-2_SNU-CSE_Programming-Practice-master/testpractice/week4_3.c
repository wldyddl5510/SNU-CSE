#include <stdio.h>

int main(void) {
	int arr[1000];
	int cnt = 0;
	while(1) {
		if(scanf("%d", &arr[cnt]) == EOF)
			break;
		cnt++;
	}
	for(int i = cnt-1 ; i >= 0 ; i--) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
