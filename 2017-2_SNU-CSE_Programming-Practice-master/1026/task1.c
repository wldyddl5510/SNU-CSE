#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int word_cnt( char *s){
	int count = 0;
	
	while(*s!='\0')
	{
		while(isspace(*s)) s++;

		if(*s!='\0')
			{
				count++;
				while(!isspace(*s)&&(*s != '\0')) ++s;
			}
	}
	printf("%d\n", count);
	return(count);
}

int main(void){
	char a[1000];
	int i;
	int count=0;

	for(i=0;i<1000 && (a[i]=getchar())!=EOF;i++)
	{
		scanf("%s", a);
		printf("%s\n",a);
	}	

	printf("%d\n", word_cnt(a));
	return 0;
}

