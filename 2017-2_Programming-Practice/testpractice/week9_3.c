#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxword 1000
#define N 10000

void swap(char **p, char **q) {
	char *temp;
	temp = *p;
	*p = *q;
	*q = temp;
}

void sort_words(char *w[], int n) {
	for(int i = 0 ; i < n ; i++) {
		for(int j = i+1 ; j < n ; j++) {
			if(strcmp(w[i], w[j]) > 0)
				swap(&w[i], &w[j]);
		}
	}
}

int main(void) {
	char word[maxword]; //read each word
	char *w[N]; //all words set
	int n;

	char *net_word[N]; //real word w/o intersection
	int net_word_count[N] = {0,};
	int net_count = 0;

	int i = 0, j = 0;
	while(scanf("%s", word) != EOF) {
		w[i] = (char*)malloc((strlen(word) + 1) * sizeof(char)); //
		strcpy(w[i], word);
		i++;
	}
	n = i; //total word cnt
	sort_words(w,n);
	n = i;

	for(int j = 0 ; j < n ; j++) {
		if(net_count != 0 && strcmp(w[j], net_word[net_count - 1]) == 0) //not distinct
			net_word_count[net_count - 1]++;
		else {
			net_count++;
			net_word[net_count - 1] = (char*) malloc((strlen(w[j]) + 1) * sizeof(char));
			strcpy(net_word[net_count - 1], w[j]);
			net_word_count[net_count - 1]++;
		}
	}

	for(int j = 0 ; j < net_count - 1 ; j++) {
		for(int k = 0 ; k < net_count - i - 1 ; k++) {
			if(net_word_count[j] < net_word_count[j+1]) {
				int temp;
				temp = net_word_count[j];
				net_word_count[j] = net_word_count[j+1];
				net_word_count[j+1] = temp;

				swap(&net_word[j], &net_word[j+1]);
			}
		}
	}
	for(int i = 0 ; i < net_count ; i++) {
		printf("%s\n", net_word[i]);
	}
}

