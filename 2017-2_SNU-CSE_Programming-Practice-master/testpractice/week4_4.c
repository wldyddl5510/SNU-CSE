#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n;
	char blank;
	scanf("%d", &n);
	scanf("%c", &blank);
	char *word = (char*) malloc((n+1) * sizeof(char));

	for(int k = 0 ; k < n ; k++) {
		scanf("%c", &word[k]);
	}
	word[n] = '\0';
/*
	for(int k = 0; k < n ; k++) {
		printf("%c ", word[k]);
	}
*/
	int j = n-1;
	int i = 0;
//	int indicator == 0;
	while(j >= 0 && i <= n-1) {
		if(word[j--] != word[i++]) {
			printf("FALSE\n");
//			indicator == 1;
			break;
		}
		else 
			continue;
	}
	if(j < 0 && i > n-1)
		printf("TRUE\n");
	return 0;
}
