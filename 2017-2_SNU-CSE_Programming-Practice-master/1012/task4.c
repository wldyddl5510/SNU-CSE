#include <stdio.h>

int main(void)
{
	int abs(int x)
	{
		if(x<0) return -x;
		else return x;
	}

	int n;
	scanf("%d", &n);
	
	int p[2500];
	for (int i = 1; i<= 2*n-1; i=i+2)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		p[i]=a;
		p[i+1]=b;
	}

	int min= 999999;
	int max= 0;
	int dist[3000]= {};

	for(int j = 1; j<=2*n-1;j= j+2)
	{
		for(int k = 1; k<=2*n-1; k= k+2)
		{
			if( j== k) continue;
			else
			dist[k]=abs(p[j]-p[k])+abs(p[j+1]-p[k+1]);
		}
		for (int l = 1; l<=2*n-1; l=l+2)
		{
			if(l==j) continue;
			else if(dist[l]<=min) min=dist[l];
			else if(dist[l]>=max) max=dist[l];
			else continue;
		}
	}
	printf("%d\n", min);
	printf("%d\n", max);
	return 0;
}	 
