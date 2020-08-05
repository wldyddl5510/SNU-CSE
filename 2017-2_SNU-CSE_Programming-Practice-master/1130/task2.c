#include <stdio.h>

long long diag (int n) {
	if(n == 1) 
		return 1;
	else {
		return (diag(n-2) + (4*n*n) - (6*n) + 6);
	}
}

int main(void) {
	int n;

	scanf("%d", &n);

	printf("%lld\n", diag(n));

	return 0;
}

