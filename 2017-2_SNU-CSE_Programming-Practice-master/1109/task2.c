#include <stdio.h>
#include <stdlib.h>

int main(void){
	int max=-100000;	//recall max value
	int n;	//number of input
	int indicator;	//seperate case big and small
	int* inputarray;	//space for input number
	int sum;	//sum of subarray
	int i,j,k;	//for sentence variables
	int max_end;	//case of big
	int current_start;
	int save_max_start;	//index of subarray
	int save_max_end;	//index of subarray

	scanf("%d",&n);

	inputarray=(int*)malloc(n*sizeof(int));

	for(i=0;i<n;i++){
		scanf("%d",&inputarray[i]);
	}

	if(n<1000){
		printf("small\n");
		indicator=0;
	}

	else{
		printf("big\n");
		indicator=1;
	}

	if(indicator==0){
		for(i=0;i<n;i++){
			for(j=i;j<n;j++){
				sum=0;
				for(k=i;k<=j;k++){
					sum=sum+inputarray[k];
					if(sum>max){
						max=sum;
						save_max_start=i;
						save_max_end=j;
					}
				}
			}
		}

	printf("%d,%d\n", save_max_start,save_max_end);
	}

	else{
		max_end=inputarray[0];
		save_max_start=0;
		save_max_end=0;
		for(i=1;i<n;i++){
			if(max_end+inputarray[i]<inputarray[i]){			//calculating sum: cumsum>0 continue
				max_end=inputarray[i];
				current_start=i;
			}

			else {						//calculating sum: cumsum<=0 reset
				max_end=max_end+inputarray[i];
			}

			if(max<max_end){		//finding end index
				max=max_end;
				save_max_end=i;
				save_max_start=current_start;
			}
		}
		printf("%d,%d\n",save_max_start,save_max_end);
	}

	printf("%d\n", max);

	free(inputarray);
	return 0;
}

