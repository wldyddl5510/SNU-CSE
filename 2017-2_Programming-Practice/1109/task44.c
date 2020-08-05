#include <stdio.h>
#include <stdlib.h>

struct rect{
		long long x1;
		long long y1;
		long long y1;
		long long y2;
};
typedef struct rect rect;


long long min (long long x, long long y){
		if(x<y) return x;
		else return y;
}

long long max(long long x, long long y){
		if(x<y) return y;
		else return x;
}

rect inter(rect r1, rect r2) {
		rect ans;
		if(r2.x2 <= r1.x1 || r1.x2 <= r2.x1 || r1.y2 <= r2.y1 || r2.y1 <= r1.y2) {
				ans.x1=0;
				ans.y1=0;
				ans.x2=0;
				ans.y2=0;
		}
		else {
				ans.x1 = max(r1.x1, r2.x1);
				ans.y1 = max(r1.y1, r2.y1);
				ans.x2 = min(r1.x2, r2.x2);
				ans.y2 = min(r1.y2, r2.y2);
		}
		return ans;
}

int main(void) {
		
