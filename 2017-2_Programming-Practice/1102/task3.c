#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	
	char dummy[1001]; //dummy variable to read word
	char* str[1001]; //saving strings
	char** str2;	//to save only distinct word
	int diffnum;	//number of diff char
	int* count; //frequecy of words
	int i;	//for sentence variable
	int n;	//number of all word
	int j;	//for sentence variable
	int k;	//number of distinct word
	int length;	//count how many times appear for each words
	char* temp;	//to swap
	char* temp2;	//to swap
	int temp3;	//to swap

	for(i=0 ; scanf("%s",dummy)!=EOF ; i++){ //read text and copy to str	
		str[i]= (char*)malloc(sizeof(char)*(strlen(dummy)+1));	//make str
		strcpy(str[i],dummy);
	}
	n = i;	//number of all words

	for(i=0; i<n-1 ; i++){ //read all words
		for(j=i+1 ; j<n ; j++){ //compare each word with the other

			if(strcmp(str[i],str[j])<0){ //sort by alpahbet by swap
				temp=str[i];
				str[i] = str[j];
				str[j] = temp;
			}
		}
	}

	diffnum = 1;	//solve number of distinct word
	for(i = 0 ; i < n-1 ; i++){
		if(strcmp(str[i], str[i+1])!=0){
			diffnum++;
		}
	}

	count = (int*)malloc(sizeof(int)*diffnum);	//count the words freq of distinct
	str2 = malloc(sizeof(char*)*diffnum);	//array only with different words
	for(i=0;i<diffnum;i++){
		str2[i] = (char*)malloc(sizeof(char)*1001); //words of distinct
	}

	k=0;
	length =1;	//words frequency
	for(j = 0 ; j < n-1 ; j++){
//		printf("%d %d\n ", j, length);
		if(strcmp(str[j],str[j+1])!=0){	//for distinct words, count length
			count[k]=length;
			str2[k]=str[j];
			k++;
			length=1;
		}
		else length++;
	}

	count[k]=length;	//add last one as it is omitted
	str2[k]=str[n-1];
//	for(i=0;i<diffnum;i++) printf("%s\n",str2[i]);

	for(i=0;i<diffnum;i++){	//swap the word based on count
		for(j=i ; j<diffnum; j++){
			if(count[i]<count[j]){
				temp2 = str2[i];
				temp3 = count[i];	//count and str2 is 1-1, so swap both
				str2[i] = str2[j];
				count[i] = count[j];
				str2[j] = temp2;
				count[j] = temp3;
			}
		}
	}

	for(i=0;i<diffnum;i++) printf("%s\n",str2[i]);

	free(count);

	for(i = 0; i < n; i++) free(str[i]);

	for(i = 0; i < k ; i++) free(str2[i]);

	return 0;
}
