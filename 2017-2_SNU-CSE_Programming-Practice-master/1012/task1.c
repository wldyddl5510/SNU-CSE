#include <stdio.h>

int main(void)
{
	int n;
	long long sol[50];
	scanf("%d",&n);
	
	sol[0]=0;
	sol[1]=1;
	if(n==0)
	{
		printf("%lld", sol[0]);
		return 0;
	}
	else if(n == 1) 
	{
		printf("%lld", sol[1]);
		return 0;
	}
	else 
	{
		for (int i=2; i<=n; i++)
		{
			sol[i]=sol[i-1]+sol[i-2];
		}
		printf("%lld", sol[n]);
		return 0;
	}
}
