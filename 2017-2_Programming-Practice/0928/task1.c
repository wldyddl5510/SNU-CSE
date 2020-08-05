#include <stdio.h>

int main(void)
{
	int count[26]={0};
	int i;
	char c;
	while((c = getchar())!=EOF)
	{
		if('a'<=c && c<='z')
		{
			count[c-'a']++;
		}
		else if('A'<=c && c<='Z')
		{
			count[c-'A']++;
		}
	}
	for(i=0;i<26;i++)
	{
		if(count[i]!=0)
		{
			printf("%c %d\n",('a'+i),count[i]);
		}
	}
	return 0;
}

