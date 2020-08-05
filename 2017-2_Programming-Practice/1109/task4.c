#include <stdio.h>
#include <stdlib.h>

struct rect {
		long long x1;
		long long y1;
		long long x2;
		long long y2;
};
typedef struct rect rect;

long long min(long long x, long long y){
		if(x<y) return x;
		else return y;
}
long long max(long long x, long long y){
		if(x<y) return y;
		else return x;
}

rect inter(rect r1, rect r2){
		rect ans;
		if(r2.x2<=r1.x1 || r1.x2<=r2.x1 || r1.y2<=r2.y1 || r2.y2<=r1.y1){
				ans.x1=0;
				ans.y1=0;
				ans.x2=0;
				ans.y2=0;
		}
		else{
				ans.x1=max(r1.x1, r2.x1);
				ans.y1=max(r1.y1, r2.y1);
				ans.x2=min(r1.x2, r2.x2);
				ans.y2=min(r1.y2, r2.y2);
		}
		return ans;
}
/*
rect inter(rect r1, rect r2){
		rect ans;
		if(r1.x1<=r2.x1 && r1.y1<=r2.y1 && r2.x2<= r1.x2 && r2.y2<=r1.y2){
				ans.x1=r2.x1;
				ans.y1=r2.y1;
				ans.x2=r2.x2;
				ans.y2=r2.y2;
		}

		else if(r2.x1<r1.x1 && r2.y1<r1.y1 && r1.x2<r2.x2 && r1.y2<r2.y2){
				ans.x1=r1.x1;
				ans.y1=r1.y1;
				ans.x2=r1.x2;
				ans.y2=r1.y2;
		}

		else if(r1.x1<=r2.x1 && r2.x2<=r1.x2){
				if(r2.y2<=r1.y1 || r1.y2<=r2.y1){
						ans.x1=0;
						ans.y1=0;
						ans.x2=0;
						ans.y2=0;
				}
				else if(r2.y1<=r1.y1 && r1.y2<=r2.y2){
						ans.x1=r2.x1;
						ans.y1=r1.y1;
						ans.x2=r2.x2;
						ans.y2=r1.y2;
				}
				else if(r2.y1<=r1.y1 && r2.y2<=r1.y2){
						ans.x1=r2.x1;
						ans.y1=r1.y1;
						ans.x2=r2.x2;
						ans.y2=r2.y2;
				}
				else if(r1.y1<=r2.y1 && r1.y2<=r2.y2){
						ans.x1=r2.x1;
						ans.y1=r2.y1;
						ans.x2=r2.x2;
						ans.y2=r1.y2;
				}
		}

		else if(r2.x1<=r1.x1 && r1.x2<=r2.x2){
				if(r1.y2<=r2.y1 || r2.y2<=r1.y1){
						ans.x1=0;
						ans.y1=0;
						ans.x2=0;
						ans.y2=0;
				}
				else if(r1.y1<=r2.y1 && r2.y2<=r1.y2){
					ans.x1=r1.x1;
					ans.y1=r2.y1;
					ans.x2=r1.x2;
					ans.y2=r2.y2;
				}
				else if(r1.y1<=r2.y1 && r1.y2<=r2.y2){
						ans.x1=r1.x1;
						ans.y1=r2.y1;
						ans.x2=r1.x2;
						ans.y2=r1.y2;
				}
				else if(r2.y1<=r1.y1 && r2.y2<=r1.y2){
						ans.x1=r1.x1;
						ans.y1=r1.y1;
						ans.x2=r1.x2;
						ans.y2=r2.y2;
				}
		}

		else if(r1.x1<=r2.x1){
				if(r1.x2>=r2.x1){
						if(r1.y1>=r2.y2 || r1.y2<=r2.y1){
								ans.x1=0;
								ans.y1=0;
								ans.x2=0;
								ans.y2=0;
						}

						else if(r1.y1<=r2.y1 && r2.y2<=r1.y2){
								ans.x1=r2.x1;
								ans.y1=r2.y1;
								ans.x2=r1.x2;
								ans.y2=r2.y2;
						}

						else if(r2.y1<=r1.y1 && r1.y2<=r2.y2){
								ans.x1=r2.x1;
								ans.y1=r1.y1;
								ans.x2=r1.x2;
								ans.y2=r1.y2;
						}

						else if(r1.y2<=r2.y2){
								ans.x1=r2.x1;
								ans.y1=r2.y1;
								ans.x2=r1.x2;
								ans.y2=r1.y2;
						}
						else if(r1.y1>=r2.y1){
								ans.x1=r2.x1;
								ans.y1=r1.y1;
								ans.x2=r1.x2;
								ans.y2=r2.y2;
						}
				}
				else{
						ans.x1=0;
						ans.y1=0;
						ans.x2=0;
						ans.y2=0;
				}
		}

		else if(r1.x1>= r2.x1){
				if(r2.x2>=r1.x1){
						if(r1.y1>=r2.y2 || r1.y2<=r2.y1){
								ans.x1=0;
								ans.y1=0;
								ans.x2=0;
								ans.y2=0;
								//area = 0;
						}

						else if(r1.y1<=r2.y1 && r2.y2<=r1.y2){
								ans.x1=r1.x1;
								ans.y1=r2.y1;
								ans.x2=r2.x2;
								ans.y2=r2.y2;
						}

						else if(r2.y1<=r1.y1 && r1.y2<=r2.y2){
								ans.x1=r1.x1;
								ans.y1=r1.y1;
								ans.x2=r2.x2;
								ans.y2=r1.y2;
						}

						else if(r1.y2<=r2.y2){
								ans.x1=r1.x1;
								ans.y1=r2.y1;
								ans.x2=r2.x2;
								ans.y2=r1.y2;
								//area = (r1.y2 - r2.y1) * (r2.x2 - r1.x1);
						}
						else if(r1.y1>=r2.y1){
								ans.x1=r1.x1;
								ans.y1=r1.y1;
								ans.x2=r2.x2;
								ans.y2=r2.y2;
								//area = (r1.x2 - r2.x1) * (r2.y2 - r1.y1);
						}
				}
				else{
						ans.x1=0;
						ans.y1=0;
						ans.x2=0;
						ans.y2=0;
				}
		}

		else {
				ans.x1=0;
				ans.y1=0;
				ans.x2=0;
				ans.y2=0;
		}

		return ans;
}
*/
/*
rect si(rect* r,int i){
		if(i==1){
			return (inter(r[0], r[0]));
		}
		else{
			return (inter(si(r,(i-1)),r[i-1]));
		}
}
*/

int main(void){
		int n; 		//num of rect
		rect* r;
		rect* r1; 	//for s_i
		int i;
		//long long area;
		long long* area;

		scanf("%d",&n);

		r = (rect*)malloc(n*sizeof(rect));
		r1 = (rect*)malloc(n*sizeof(rect));
		area = (long long*)malloc(n*sizeof(long long));

		for(i=0;i<n;i++){
				scanf("%lld %lld %lld %lld", &r[i].x1, &r[i].y1, &r[i].x2, &r[i].y2);
		}
		
		r1[0]=r[0];
		for(i = 1; i<n ; i++){
				r1[i]=inter(r1[i-1],r[i]);
				//printf("%lld %lld %lld %lld\n", r1[i].x1, r1[i].y1, r1[i].x2, r1[i].y2);
		}
		
		for(i=0;i<n;i++){
				area[i]=(r1[i].x2-r1[i].x1)*(r1[i].y2-r1[i].y1);
				printf("%lld\n",area[i]);
		}

		free(area);
		free(r);
		free(r1);
		
		/*		
		for(i=0;i<n;i++){
				area=(si(r,(i+1)).x2-si(r,(i+1)).x1) * (si(r,(i+1)).y2 - si(r,(i+1)).y1);
				//printf("%d %d %d %d\n",si(r,i+1).x1, si(r,i+1).y1, si(r,i+1).x2, si(r,i+1).y2);
				printf("%lld\n", area);
		}

		free(r);
		*/

		return 0;
}

