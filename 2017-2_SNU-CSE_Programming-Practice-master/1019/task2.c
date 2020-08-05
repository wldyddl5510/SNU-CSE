#include <stdio.h>

int main(void)
{
	int n;
	int score[1000]={0};
	int Q;
	int rank[1000]={0};
	int my_rank[1000]={0};
	
	scanf("%d",&n);
	
	for(int i=0;i<n;i++)
	{
		scanf("%d", &score[i]);
	}
	
	scanf("%d",&Q);

	for(int i=0;i<Q;i++)
	{
		scanf("%d", &rank[i]);
	}

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(score[i]<score[j])
				my_rank[i]++;
			else continue;
		}
		my_rank[i]=my_rank[i]+1;
	}

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(rank[i]==my_rank[j])
				printf("%d\n",score[j]);
			else continue;
		}
	}

return 0;
}
