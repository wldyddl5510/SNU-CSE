#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n;
	long long *input;
	long long start_from;
	long long profit = 0;

	scanf("%d",&n);

	input = (long long*) malloc(n * sizeof(long long));

	for(int i = 0; i < n; i++) {
		scanf("%lld", &input[i]);
	}

	start_from = input[n-1];
/*
	for(int i = (n-1) ; i >= 1 ; i--) {
		if(input[i-1] <= input[i]) {
			profit = profit + (start_from - input[i-1]);
			continue;
		}
		else if(input[i-1] > input[i]) {
			start_from = input[i-1];
		}
	}
*/

	for(int i = (n-2) ; i >= 0 ; i--) {
		if(input[i] <= start_from) {
			profit = profit + (start_from - input[i]);
			continue;
		}
		else if(input[i] > start_from) {
			start_from = input[i];
		}
	}

	printf("%lld\n", profit);

	return 0;
}


/*
	for(int i = 0 ; i < (n-1) ; i++) {
		if(amount * input[i] < (amount + 1) * input[(i + 1)])
			amount++;
		else {
			profit = amount * input[i];
			amount = 0;
		}
	}

	printf("%lld\n", profit);

	return 0;
}
*/
