#include <stdio.h>
int main(void)
{
	char input[1000]={0};
	int count=0;
	int i;
	int b;
	int j;
	int k;
	char u;
	char output[1000]={0};

	scanf("%d",&b);
	scanf("%c",&u);
	for(j=0;j<b;j++)
	{
		scanf("%c",&input[j]);
	}
	for(i=0;i<b;i++)
	{
		output[i]=input[(b-i-1)];
	}
	output[b]='\0';
	for(k=0;k<b;k++)
	{
		if(output[k]!=input[k])
	 	{
		printf("False");
		return 0;
		}
	}
	printf("True");
	return 0;
}

