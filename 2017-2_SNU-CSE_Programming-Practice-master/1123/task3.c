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

int hand[4][13];

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

int straight(card arr[5]) {
	//if straight return 1 else 0;
	int indicator = 0;
	for(int i = 0; i < 13 ; i++) {
		(a[][i] == 1)
	}
}

int flush(card arr[5]) {
	//if flush return 1 else 0;
}

int pair(card arr[5]) {
	//if exists pair return 1 else 0;
}

int triple(card arr[5]) {
	//if exists triple return 1 else 0;
}

int fourcard(card arr[5]) {
	//if fourcard return 1
}

int straight_flush(card arr[5]) {
	//straight && Flush == 1
}

int twopair(card arr[5]) {
	//onpair && onepair == 1
}

int fullhouse(card arr[5]) {
	//onepair && triple == 1
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
		else if(pair(hand) == 1)
			printf("One Pair\n");
		else
			printf("No Pair\n");
	}

	return 0;
}
