#include <stdio.h>
#include <stdlib.h>

struct point{	//structure points value
		int x;
		int y;
};
typedef struct point point;

long long l2dis(point p1, point p2){	//define distance function
		long long d;
		d=(p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
		return d;
}

int main(void){

		int n;	//num of points
		point* cor;	//array of points
		int i;
		int j;
		long long min;
		int closest;		//closest point

		scanf("%d",&n);	//scan all length

		cor=(point*) malloc(n*sizeof(point));	//dynamic allocation of array with length n

		for(i = 0; i < n; i++){		//fill the array with points
				scanf("%d %d",&cor[i].x, &cor[i].y);
		}

		for(i = 0 ; i < n ; i++){
				min=10000000000;
				for(j=0;j<n;j++){
						if(i!=j && min>l2dis(cor[i],cor[j])){
								min=l2dis(cor[i],cor[j]);
								closest = j;
						}
				}
				printf("%d\n",closest);
		}
		return 0;
		free(cor);
}


