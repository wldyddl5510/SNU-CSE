#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int word_cnt(char *s) {
	int cnt = 0;
	
	while( *s != '\0') {
		if(isspace(*s)) {
			s++;
		}

		if(*s != '\0') {
			cnt++;
			if(!isspace(*s) && (*s != '\0'))
				s++;
		}
	}
	printf("%d\n", cnt);
	return cnt;
}
		

int main(void) {
	char *sen;

	int i = 0;

	while(1) {
		if(scanf("%c", sen) == EOF)
			break;
	}
	printf("%d\n", word_cnt(sen));
	return 0;
}
	
