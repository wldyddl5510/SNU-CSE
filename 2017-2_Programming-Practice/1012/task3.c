#include <stdio.h>

int main(void)
{
	int n;
	scanf("%d", &n);
	int s[1500];
	for(int i = 1; i<=n; i++)
	{
		int k;
		scanf("%d", &k);
		s[i]=k;
	}
	int count[1500] = {};
	for (int j = 1; j <=n; j++)
	{
		for(int l = 1; l<=n; l++)
			{
				if (s[j] <s[l]) count[j] = count[j]+1;
				else continue; 
			}
		printf("%d ", count[j]+1);
	}
	return 0;
}

