#include <stdio.h>

int main(void)
{
	int input[1000]={0};
	int i;
	int count=0;
	int output[1000]={0};
	int a;

	while(1){
	a=scanf("%d",&input[count]);
	if(a!=EOF)
	{
		count++;
	}
	else 
	{break;}
	}

	for(i=0;i<count;i++)
	{
		output[i]=input[(count-i-1)];
		printf("%d ",output[i]);
	}
	
	return 0;
}
