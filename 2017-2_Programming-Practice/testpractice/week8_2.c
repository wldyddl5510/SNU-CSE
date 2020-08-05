#include <stdio.h>

int my_strlen(char *str) {
	int cnt = 0;
	while(1) {
		if (*str == '\0' || *str == ' ')
			break;
		else {
			cnt++;
			str++;
		}
	}
	return cnt;
}

void my_strrev(char *str1, char *str2) {
	int n = my_strlen(str1);
	for(int i = n-1 ; i >= 0 ; i--) {
		*str2 = str1[i];
		str2++;
	}
}

int main(void) {
	char str1[100] = "Arsenal";
	char str2[100];

	my_strrev(str1, str2);

	printf("%d\n", my_strlen(str1));
	printf("%s\n", str2);
}
