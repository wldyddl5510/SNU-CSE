#include <stdio.h>

int main(void) {
	int max1 = -99999;
	int max2 = -99999;
	int max3 = -99999;
	int n;
	int sum = 0;
	int cnt = 0;

	while(scanf("%d",&n) != EOF) {
		if(n > max1) {
			max2 = max1;
			max1 = n;
		}
		else if(n > max2 & n != max1) { 
			max3 = max2;
			max2 = n;
		}
		else if(n > max3 & n != max2 & n != max1) 
			max3 = n;
		else 
			continue;
		sum = sum + n;
		cnt++;
	}
	double mean = sum / (double)cnt;
	if(max2 == -99999) 
		max2 = -1;
	if(max3 == -99999)
		max3 = -1;
	printf("%d %d %lf\n", max2, max3, mean); 
	return 0;
}
