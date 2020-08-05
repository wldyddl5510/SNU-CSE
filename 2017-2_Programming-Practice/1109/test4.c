#include <stdio.h>

int main(void){
		int i;
		printf("10000\n");
		for(i=39999;i>-1;i=i-1){
				if(i%4==3 || i%4==2){
						printf("-1000000000 ");
				}
				else if(i%4==1){
						printf("1000000000 ");
				}
				else if(i%4==0){
						printf("1000000000\n");
				}
		}
		return 0;
}


