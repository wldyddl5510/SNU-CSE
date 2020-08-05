#include <stdio.h>

long long fib(int n) {
	if(n == 1 || n == 2)
		return 1;
	else 
		return (fib(n-1) + fib(n-2));
}

int main(void) {
	int n;

	scanf("%d",&n);

	printf("%lld\n",fib(n));

	return 0;
}
