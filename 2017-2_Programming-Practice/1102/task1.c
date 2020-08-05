#include <stdio.h>
#include <stdlib.h>

int main(void){

	int N;
	int** A;
	int** B;
	int** AB;
	int i,j,k;
	int sum;

	scanf("%d",&N);

	A=(int**)malloc(sizeof(int*)*N);
	B=(int**)malloc(sizeof(int*)*N);
	AB=(int**)malloc(sizeof(int*)*N);

	for(i = 0; i < N; i++){ //make matrix
		A[i] = (int *)malloc(sizeof(int) * N);
		B[i] = (int*)malloc(sizeof(int)*N);
		AB[i] = (int *)malloc(sizeof(int) * N);
	}

	for(i=0;i<N;i++){ /* get A*/
		for(j=0;j<N;j++){
			scanf("%d", &A[i][j]);
		}
	}

	for(i=0;i<N;i++){ /* get B */
		for(j=0;j<N;j++){
			scanf("%d",&B[i][j]);
		}
	}

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			sum=0;/*sigma a_ik*b_kj */ /*need  initailization for each ij*/

			for(k=0;k<N;k++){
				sum=sum+A[i][k]*B[k][j];
			}
			AB[i][j]=sum;
		}
	}

	for(i=0;i<N;i++){ /*print AB matrix*/
		for(j=0;j<N;j++){
			printf("%d ",AB[i][j]);
		}
		printf("\n"); //each row space
	}
	
	free(A);	/*free malloc */
	free(B);
	free(AB);
	return 0;
}

