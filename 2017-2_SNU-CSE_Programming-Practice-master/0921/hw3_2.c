#include <stdio.h>

int main(void)
{
	float n;
	int m;
	float l;

	printf("Input: ");
	scanf("%f", &n);

	m =(int)n;
	l=n-m;

	printf("\n%d\n",(int)(m+2*l));
	
	return 0;
}
