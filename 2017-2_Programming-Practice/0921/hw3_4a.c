#include <stdio.h>

int main(void)
{
	int N;
	int i=1;

	printf("Input: ");
	scanf("%d",&N);

	for(i=1;i<=9;i++)
	{
		printf("\n%d*%d = %d\n",N,i,N*i);
	}

	return 0;
}

