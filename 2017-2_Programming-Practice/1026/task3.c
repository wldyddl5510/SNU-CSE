#include <stdio.h>
#include <stdlib.h>

int* number_malloc(int n){
	int* len;
	len =(int*) malloc(n*sizeof(int));
	int i;

	for(i=0;i<n;i++)
	{
		len[i]=i+1;
	}

	return(len);
}
/*
int main()
{
	int* arr;
	int num;
	scanf("%d",&num);
	arr = number_malloc(num);
	int i;
	for(i = 0; i<num; i++)
	{
		printf("%d ",arr[i]);
	}
}
*/
