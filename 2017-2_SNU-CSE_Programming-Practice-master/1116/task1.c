#include <stdio.h>
#include <stdlib.h>

int bitcount(int x){		//num of 1
	int count=0;
	for(int i=0;i<31;i++){
		if((x & (1<<i)) != 0){
			count++;
		}
	}
	return count;
}
int cnt(int x){		//jarisu
	int k=0;
	for(int i = 30; i>0;i--){
		if(((1<<i) & x) !=0){
			k=i;
			break;
		}
	}
	return k;
}

int main(void){
		//printf("%d\n",cnt(10));
		
		int n;
		int* output;
		int* input;
		int i,j;

		scanf("%d",&n);

		input = (int*)malloc(sizeof(int)*n);
		output = (int*)malloc(sizeof(int)*n);

		for(i=0;i<n;i++){
				scanf("%d",&input[i]);
		}
		for(i=0;i<n;i++){
				output[i]=-1;
		}

		for(i=0;i<n;i++){
				for(j=(input[i]-cnt(input[i]));j<input[i];j++){
						if((j+bitcount(j))==input[i]){
								output[i]=j;
								break;
						}
				}
		}
		for(i=0;i<n;i++){
				printf("%d\n",output[i]);
		}
		
				
		return 0;
}


