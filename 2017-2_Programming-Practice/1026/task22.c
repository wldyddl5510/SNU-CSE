#include <stdio.h>

int my_strlen(char *str){
	int count=0;
	int i=0;

	while(str[i]!='\0'){
	count++;
	i++;
	}
	
	return(count);
}

void my_strrev(char *str1, char *str2){
	int n=my_strlen(str1);
	int i;

	for(i=0;i<n;i++){
	str2[i]=str1[n-i-1];
	}
	str2[n]='\0';
}
/*
int main(void)
{
	char str1[100] = "Arsenal";
	char str2[100];
	my_strrev(str1, str2);
	printf("%d\n", my_strlen(str1));
	printf("%s\n",str2);
}
*/
