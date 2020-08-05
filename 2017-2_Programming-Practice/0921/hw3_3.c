#include <stdio.h>

int main(void)
{
	int a, b;
	int c, d;
	printf("Input: ");
	scanf("%d %d", &a, &b);

	c = a/b;
	d = a-(b*c);
	printf("\n%d = %d*%d+%d, %f\n", a, c, b, d, a/(float)b);

	return 0;
}

	
