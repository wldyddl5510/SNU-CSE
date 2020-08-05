#include <stdio.h>

void swap(int *a, int*b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
/*
int main(void)
{
	int a,b;
	scanf("%d %d", &a, &b);
	swap(&a, &b);
	printf("%d %d\n",a,b);
	return 0;
}
*/


