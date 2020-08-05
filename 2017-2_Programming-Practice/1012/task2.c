#include <stdio.h>

int main(void)
{
	long long bin(int n, int k)
	{
		if (k<0) return 0;
		else if(n>=25) return 0;
		else if(k==n) return 1;
		else if(k==0) return 1;
		else
		return (bin((n-1),(k-1))+bin((n-1),k));
	}
	int a, b;
	scanf("%d %d",&a, &b);
	printf("%lld", bin(a,b));
	return 0;
}

