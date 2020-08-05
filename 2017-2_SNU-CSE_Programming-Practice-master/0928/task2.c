#include <stdio.h>


int main(void)
{
	char* str =
	"\
	P-P-A-P\
	I have a pen, I have a apple\
	Uh! Apple-Pen!\
	I have a pen, I have pineapple\
	Uh! Pineapple-Pen!\
	Apple-Pen, Pineapple-Pen\
	Uh! Pen-Pineapple-Apple-Pen\
	Pen-Pineapple-Apple-Pen\
	";

	char a[3];
	int i=0;
	int j=0;
	int count=0;

	while((a[i++]=getchar())!=EOF);

	for(j=0;j<1000;j++)
	{
		if(str[j] == '\0')
		{
			break;
		}
		else if((str[j]==a[0]) && (str[j+1] == a[1]))
		{
			count++;
		}

	}

	printf("%d",count);
	return 0;
}

