#include <stdio.h>

int main(void)
{
	char a[1000];
	int count=0;
	int i=0;

	while(scanf("%s",a)!=EOF){
	count++;
	i++;
	}

	printf("%d\n", count);
	return 0;
}

