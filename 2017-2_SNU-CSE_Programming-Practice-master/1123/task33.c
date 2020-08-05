#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
typedef struct cardnum {
	//need to fill: reorder the number by j=11,q=12,k=13,a=14
} cardnum;

typedef struct card {
	char symbol;
	cardnum number;
} card;
*/
int deck[4][13];

int royal_straight_flush(int arr[4][13]) {
	int indicator = 0;
	for(int i = 0; i < 4; i++) {
		for(int j = 8 ; j < 13 ; j++) {
			if(arr[i][j] != 1) {
				indicator = 1;
				break;
			}
		}
	}
	if(indicator ==0) 
		return 1;
	else return 0;
}

int straight(int arr[4][13]) {
	//if straight return 1 else 0;
	int indicator = 0;
	for(int i = 0; i < 13 ; i++) {
		for(int j = 0; j < 4 ; j++) {
			if(a[j][i] == 1) {
				for(int k = 0; k < 4 ; k++) {
					if(k != j) {
						if(a[k][(i+1)] == 1 ) {
							indicator++;
						}
						if(indicator != 1) 
							return 0;
						else { 

	}
}
/*
int flush(card arr[5]) {
	//if flush return 1 else 0;
	int indicator = 0;
	for(int i = 0 ; i < 4 ; i++) {
		int cnt = 0;
		for(int j = 0 ; j < 13 ; j++) {
			if(a[i][j] != 0)
				cnt++;
		}
		if(cnt == 5) 
			indicator++;
	}
	if(indicator == 1)
		return 1;
	else
		return 0;
}
*/
//int pair(card arr[5]) {
	//if exists pair return 1 else 0;
void numofsame (int *two, int *three, int *four, int arr[4][13]) {
	int cnt[13] = 0;
	int twocard = 0;
	int triple = 0;
	int fourcard = 0;
	for(int i = 0; i < 13 < i ++ ) {
		for( int j = 0 ; j < 4 ; j++ ) {
			if(a[j][i] == 1) {
				for(int k = 0 ; k < 4 ; k++) {
					if(k != j) {
						if(a[k][i] == 1) {
							cnt[i]++;
						}
					}
				}
			}
		}
	}
	for( int i = 0 ; i < 13 ; i++) {
		if(cnt[i] == 1 )
			twocard++;
		else if(cnt[i] == 2) {
			triple++;
		}
		else if(cnt[i] == 3) {
			fourcard++;
			break;
		}
	}
	*two = twocard;
	*three = triple;
	*four = fourcard;
}

int triple(int arr[4][13]) {
	int two, three, four;
	numofsame(&two, &three, &four, arr[4][13]);
	if((three == 1) && (two != 1)) 
		return 1;
	else return 0;
}

int fourcard(int arr[4][13]) {
	int two, three, four;
	numofsame(&two, &three, &four, arr[4][13]);
	if(four == 1)
		return 1;
	else return 0;
}

int onepair(int arr[4][13]) {
	int two, three, four;
	numofsame(&two, &three, &four, arr[4][13]);
	if((two == 1) & (three != 1))
		return 1;
	else return 0;
}

int twopair(int arr[4][13]) {
	int two, three, four;
	numofsame(&two, &three, &four, arr[4][13]);
	if(two == 2)
		return 1;
	else return 0;
}

int fullhouse(int arr[4][13]) {
	int two, three, four;
	numofsame(&two, &three, &four, arr[4][13]);
	if((two == 1) && (three == 1))
		return 1;
	else return 0;
}

int straight_flush(card arr[5]) {
	//straight && Flush == 1
}

int main(void) {
	int n;
	scanf("%d", &n);
	int i = 0;

	while(i < n) {
		card hand[5];
		
		for(int j = 0, j < 5 ; j++) {
			scanf("%c %d", hand[j].symbol, hand[j].number);
		}

		if(royal_straight_flush(hand) == 1)
			printf("Royal Straight Flush\n");
		else if(straight_flush(hand) == 1)
			printf("Straight Flush\n");
		else if(fourcard(hand) == 1)
			printf("Four Card\n");
		else if(fullhouse(hand) == 1)
			printf("Full House\n");
		else if(flush(hand) == 1)
			printf("Flush\n");
		else if(straight(hand) == 1)
			printf("Straight\n");
		else if(triple(hand) == 1)
			printf("Three Card\n");
		else if(twopair(hand) == 1)
			printf("Two Pair\n");
		else if(onepair(hand) == 1)
			printf("One Pair\n");
		else
			printf("No Pair\n");
	}
	return 0;
}
