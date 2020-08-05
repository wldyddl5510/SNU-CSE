#include <stdio.h>

int array_cmp(int N, int *A, int *B){
	for(int i=0;i<N;i++)
	{
			if(A[i]>B[i])
				return -1;
			else if(A[i]<B[i])
				return 1;
	}
	return 0;
}

/*
int main(void)
{
	int N;
	int A[1000];
	int B[1000];

	scanf("%d",&N);

	for(int i=0;i<N;i++)
	{
		scanf("%d",&A[i]);
	}

	for(int i=0;i<N;i++)
	{
		scanf("%d",&B[i]);
	}

	printf("%d\n",array_cmp(N,A,B));
}
*/
