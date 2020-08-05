#include <stdio.h>

int main(void)
{
	int n;
	int max1=-0	//max num
	int max2=-1	//2nd max num
	while(scanf("%d", &n)!=EOF)
		{if(n<max2)
			{max=max, max2=max2}
		else if(max2=<n && n<max)
			{max=max, max2=n}
		else{max=n}
		}
	printf(%d, max2);
	return 0;
}
		
