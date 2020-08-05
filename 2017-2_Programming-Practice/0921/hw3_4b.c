#include <stdio.h>

int main(void)
{
	int n;
	int i;

	printf("Input: ");
	scanf("%d", &n);

	for(i=1;i<=n;i++)
	{
		if(n%i != 0) continue;
		else printf("\n%d\n", i);
	}
	return 0;
}

