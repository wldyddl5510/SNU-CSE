#include <stdio.h>

int main(void) {
	int a, b, q, r;

	scanf("%d %d", &a, &b);
	q = a / b;
	r = a - b*q;
	printf("%d = %d*%d + %d\n%d/%d = %lf\n", a, b, q, r, a, b, a/(double)b);

	return 0;
}
