#include <stdio.h>
#include <stdlib.h>

#define abs(x) ((x) > 0 ? (x) : (-(x)))

typedef struct point {
	int x;
	int y;
} point;

long long l1dist(point a, point b) {
	return (abs((a.x - b.x)) + abs((a.y - b.y)));
}


int main(void) {
	int n;
	scanf("%d", &n);

	point *cor = (point *) malloc(n * sizeof(point));

	for(int i = 0 ; i < n ; i++) {
		scanf("%d %d", &cor[i].x, &cor[i].y);
	}
	long long min = 99999;
	long long max = 0;

	for(int i = 0 ; i < n ; i++) {
		for(int j = i+1 ; j < n ; j++) {
			if(l1dist(cor[i], cor[j]) > max)
				max = l1dist(cor[i], cor[j]);
			else if(l1dist(cor[i], cor[j]) < min)
				min = l1dist(cor[i], cor[j]);
			else 
				continue;
		}
	}
	printf("%lld\n%lld\n", min, max);
	return 0;
}
