#include <stdio.h>
#include <stdlib.h>

long long fib(int n) {
	long long *fibarr = (long long*) malloc(sizeof(long long) * n);
	if(n == 1 || n == 2) 
		return 1;
	else {
		fibarr[0] = 1;
		fibarr[1] = 1;
		for(int i = 2 ; i <= n-1 ; i++) {
			fibarr[i] = fibarr[i-1] + fibarr[i-2];
		}
		return fibarr[(n-1)];
	}
}

int main(void) {
	int n;
	scanf("%d", &n);

	printf("%lld\n", fib(n));
	
	return 0;
}


/*
int main(void) {
	long long fib[50];

	fib[0] == 1;
	fib[1] == 1;

	int n;
	scanf("%d", &n);

	if(n == 1)
		printf("%d\n",fib[0]);

	else if(n == 2)
		printf("%d\n",fib[1]);

	else {
		for(int i = 2 ; i <= n ; i++) {
			fib[i] = fib[i-1] + fib[i-2];
		}

		printf("%d\n",fib[n-1]);
	}

	return 0;
}
*/
