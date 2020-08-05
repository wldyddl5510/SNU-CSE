#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int arr[], int l, int m, int r) {
	int i = 0;
	int j = 0;
	int a = l;
	int *arr1 = (int*) malloc((m - l + 1) * sizeof(int));
	int *arr2 = (int*) malloc((r - m) * sizeof(int));

	for(int k = l; k < (m + 1) ; k++) {
		arr1[(k-l)] = arr[k];
	}
	for(int k = (m+1) ; k <= r ; k++) {
		arr2[(k - (m + 1))] = arr[k];
	}

	while(i < (m - l + 1) && j < (r - m) ) {
		if(arr1[i] < arr2[j])
			arr[a++] = arr1[i++];
		else
			arr[a++] = arr2[j++];
	}

	while(i < (m - l + 1))
		arr[a++] = arr1[i++];
	while(j < (r - m))
		arr[a++] = arr2[j++];
}

int mergesort(int arr[], int l, int r, int cnt) {
	int m;
	m = (l + r) / 2;
	cnt++;
	printf("%d ", cnt);

	if(l != r) {
		cnt = mergesort(arr, l, m, cnt);
		printf("%d ", cnt);
		cnt = mergesort(arr, (m+1), r, cnt);
		printf("%d ",cnt);
		merge(arr, l, m, r);
	}
	cnt--;
	printf("%d\n", cnt);
	return cnt;
}

#define length 32

int main(void) {
	
	int A[length];
	
	for(int i = 0 ; i < length ; i++) {
		A[i] = length - i;
	}

	int a = mergesort(A, 0, length-1, 0);

//	for(int i = 0 ; i < length ; i++){
//		printf("           %d       ", A[i]);
//	}

	return 0;
}
/*
void swap (int *x , int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}
void bubble (int arr[5]) {
	int temp;
	for(int i = 0 ; i < 5 ; i++) {
		for(int j = 0 ; j < (4 - i) ; j++) {
			if(arr[j] > arr[j+1]) {
				swap(&arr[j], &arr[j+1]);
			}
		}
	}
}
*/
/*
int samecard(int num[5]) {
	int cnt = 0;
	for(int i = 0 ; i < 4 ; i++) {
		for(int j = (i + 1) ; j < 5 ; j++) {
			if(num[i] == num[j])
				cnt++;
//			printf("when i = %d, count = %d\n",i, cnt);
		}
//		printf("%d\n",cnt);
	}
		if (cnt == 1)
			return 1; //onepair
		else if(cnt == 2)
			return 2; //2pair
		else if(cnt == 3)
			return 3; //triple
		else if(cnt == 4)
			return 4; //fullhouse
		else if(cnt == 6)
			return 5; //fourcard
}

int straight(int num[5]) {
	mergesort(num, 0, 4); 
//	bubble(num);
	if((num[1] == num[0] + 1) && (num[2] == num[0] + 2) && (num[3] == num[0] + 3) && (num[4] == num[0] + 4) )
		return 1;
	else return 0;
}

int flush(int sym[5]) {
	if((sym[0] == sym[1]) && (sym[0] == sym[2]) && (sym[0] == sym[3]) && (sym[0] == sym[4]))
		return 1;
	else return 0;
}

int straight_flush(int sym[5], int num[5]) {
	if((flush(sym) == 1) && (straight(num) == 1))
		return 1;
	else return 0;
}

int royal_straight_flush(int sym[5], int num[5]) {
	mergesort(num, 0, 4);
//	bubble(num);
	if((straight_flush(sym, num) == 1) && (num[0] == 10))
		return 1;
	else return 0;
} 

int main(void) {
	int n;
	scanf("%d", &n);

	while(n--) {
		int sym[5];
		char dummy[5][4];
		int num[5];

		for(int j = 0 ; j < 5 ; j++) {
			scanf("%s", dummy[j]);
		}

		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 4 ; j++) {
				printf("%c\n",dummy[i][j]);
			}
			//printf("\n");
		}

		for(int j = 0; j < 5 ; j++) {
			if(dummy[j][0] == 'S')
				sym[j] = 0;
			else if(dummy[j][0] == 'C')
				sym[j] = 1;
			else if(dummy[j][0] == 'D')
				sym[j] = 2;
			else
				sym[j] = 3;
		}

		for(int j = 0 ; j < 5 ; j++) {
			if(dummy[j][1] == '1') {
				num[j] = 10;
			}
			else if(dummy[j][1] == 'J') {
				num[j] = 11;
			}
			else if(dummy[j][1] == 'Q') {
				num[j] = 12;
			}
			else if(dummy[j][1] == 'K') {
				num[j] = 13;
			}
			else if(dummy[j][1] == 'A') {
				num[j] = 14;
			}
			else {
				num[j] = dummy[j][1] - '0';
			}
		}
		for(int i = 0 ; i < 5 ; i++) {
			printf("sym : %d , num = %d\n", sym[i], num[i]);
		}
		mergesort(num, 0, 4);

//		bubble(num);

		for(int i = 0 ; i < 5 ; i++) {
			printf("%d ", num[i]);
		}
		
		if(straight(num) == 1) {
			printf("straight\n");
		}
		*/
/*
		if(royal_straight_flush(sym, num) == 1)
			printf("Royal Straight Flush\n");
		else if(straight_flush(sym, num) == 1)
			printf("Straight Flush\n");
		else if(samecard(num) == 5)
			printf("Four Card\n");
		else if(samecard(num) == 4)
			printf("Full House\n");
		else if(flush(sym) == 1)
			printf("Flush\n");
		else if(straight(num) == 1)
			printf("Straight\n");
		else if(samecard(num) == 3)
			printf("Three Card\n");
		else if(samecard(num) == 2)
			printf("Two Pair\n");
		else if(samecard(num) == 1)
			printf("One Pair\n");
		else
			printf("No Pair\n");		
*/
//	}
	
//	printf("\n");
//	return 0;
//}
