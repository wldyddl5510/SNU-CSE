#include <stdio.h>

int main(void){

	int N;
	int A[1000]={0};
	int M;
	int B[1000]={0};
	int count=0;
	int loca[1000]={0};
	int in;

	scanf("%d",&N);

	for(int i=0;i<N;i++)
	{
		scanf("%d",&A[i]);
	}

	scanf("%d",&M);

	for(int i=0;i<M;i++)
	{
		scanf("%d",&B[i]);
	}

	for(int i=0;i<N-M+1;i++)
	{
		in=0;
		for(int j=0;j<M;j++)
		{
			if(A[i+j]==B[j]) continue;
			else in=1;
		}
		if(in!=1) 
		{	
		count++;
		loca[count]=i;
		}
	}

	printf("%d\n",count);
	
	for(int i=1;i<=count;i++)
	{
		//loca[i]=loca[i]-1;
		printf("%d ",loca[i]);
	}
	return 0;
}
