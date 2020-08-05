#include <stdio.h>

int main(void) {
	char *str = 
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

	char read[3];

	for(int i = 0 ; i < 2 ; i++) {
		scanf("%c", &read[i]);
	}
	read[2] = '\0';
//	printf("Debug\n");

	int j = 0;
	int cnt = 0;
	while(1) {
		if(str[j] == '\0')
			break;
		else {
			if(str[j] == read[0] && str[j+1] == read[1])
				cnt++;
		}
		j++;
	}

	printf("%d\n", cnt);

	return 0;
}
