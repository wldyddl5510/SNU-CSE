#include <stdio.h>

int main(void) {
	char a[1000];
	char alpha[26] = {0};
	int i = 0;
	while(scanf("%c",&a[i]) != EOF) {
		if('a' <= a[i] && a[i] <= 'z')
			alpha[(a[i]-'a')]++;
		else if('A' <= a[i] && a[i] <= 'Z')
			alpha[(a[i] - 'A')]++;
		i++;
	}

	for(int i = 0 ; i < 26; i ++) {
		if(alpha[i] != 0) 
			printf("%c %d\n", ('a' + i), alpha[i]);
	}

	return 0;
}
