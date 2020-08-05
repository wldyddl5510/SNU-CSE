#include <stdio.h>
#include <string.h>

int main(void) {
	FILE *dict, *input, *output;
	char c;
	char s;
	char dummy[51];
	char dummy2[51];
	int indi;
	char dicword[100][51];
	int cnt = 0;
	char str[128];
	int i = 0;
	int j = 0;

	dict = fopen("dict.txt","r");
	input = fopen("input.txt","r");
	output = fopen("output.txt","w");

	while((s = getc(dict)) != EOF) {
		if(s != '\n') {
			dicword[cnt][j++] = s;
		}
		else {
			dicword[cnt][j] = '\0';
			j = 0;
			cnt++;
		}
	}

	while((c = getc(input)) != EOF) {
		if('A' <= c && c <= 'Z') {
			dummy2[i] = c + 32;
			dummy[i] = c;
			i++;
		}
		else if('a' <= c && c <= 'z') {
			dummy[i] = c;
			dummy2[i] = c;
			i++;
		}
		else {
			dummy[i] = '\0';
			dummy2[i] = '\0';
			i = 0;
			indi = 0;
/*			for(int k = 0 ; k < strlen(dummy) ; k++) {
				printf("%c", dummy[k]);
			}*/

/*			while((s = getc(dict)) != EOF) {
				if(s != '\n') {
					dicword[j++] = s;
				}
				else {
					dicword[j] = '\0';
					j = 0;
					if(strcmp(dummy2, dicword) == 0) {
						indi = 1;
						break;
					}
				}
			}
			if(indi == 0) {
				for(int k = 0 ; k < strlen(dummy) ; k++) {
					putc(dummy[k],output);
					printf("%c", dummy[k]);
				}
				printf("\n");
				putc('\n',output);
			}
*/
			for(int k = 0 ; k < cnt ; k++) {
				if(strcmp(dummy2, dicword[k]) == 0) {
					indi = 1;
					break;
				}
			}
			if(indi == 0) {
				for(int k = 0 ; k < strlen(dummy) ; k++) {
					putc(dummy[k], output);
//					printf("%c",dummy[k]);
				}
				if(strlen(dummy) > 0) {
					putc('\n',output);
//					printf("\n");
				}
			}
		}
	}
	fclose(dict);
	fclose(input);
	fclose(output);
	return 0;
}
