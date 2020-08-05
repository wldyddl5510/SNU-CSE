#include <stdio.h>

void swap(int *a, int *b) {
	int swap = *a;
	*a = *b;
	*b = swap;
}
/*
int main(void) {
	int a, b;
	scanf("%d %d", &a, &b);

	swap(&a, &b);
	printf("%d %d\n", a, b);

	return 0;
}*/
