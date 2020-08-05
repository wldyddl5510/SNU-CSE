#include <stdio.h>
#include <string.h>
/*
typedef struct {
	int human;
	int com;
} budget budget;
*/

typedef struct player {
	int budget;
	int bet;
	int order;
	int rank;
	int isover;
} Player;


//win function
void win(Player *winner, Player *loser) {
	winner->budget = winner->budget + winner->bet + loser->bet;
	winner->bet = 0;
	winner->order = 0;
	winner->isover = 0;
	loser->bet = 0;
	loser->order = 0;
	loser->isover = 0;
}

//winner determine function
void determine(Player *a, Player *b) {
	if(a->rank > b->rank) 
		win(a, b);
	else if(a->rank < b->rank) 
		win(b, a);
	else {
		a->budget = a->budget + a->bet;
		b->budget = b->budget + b->bet;
		a->bet = 0;
		a->order = 0;
		a-> isover = 0;
		b->bet = 0;
		b->order = 0;
		b->isover = 0;
	}
}

void start(int s, Player *human, Player *com) {
	if(human->budget < 100 || com->budget < 100) 
		printf("NOT ENOUGH MONEY\n");
	else {
		human->budget = human->budget - 100;
		com->budget = com->budget - 100;
		human->bet = 100;
		com->bet = 100;
		if(s == 1) 
			human->order = 1;
		else 
			com->order = 1;
		human->isover = 0;
		com->isover = 0;
	}
}

//read and com<-0, hu<-1 insert
void add (int s, int a , Player *human, Player *com) {
	if(s == 1) 
		human->budget = ((human->budget) + a);
	else 
		com->budget = ((com->budget) + a);
//	printf("%d\n", human->budget);
}

void minus (int s, int a, Player *human, Player *com) {
	if(s == 1) { 
		if(human->budget >= a)
			human->budget = ((human->budget) - a);
		else 
			printf("NOT ENOUGH MONEY\n");
	}
	else {
		if(com->budget >= a) 
			com->budget = ((com->budget) - a);
		else
			printf("NOT ENOUGH MONEY\n");
	}
}

void value (int s, int a, Player *human, Player *com) {
	if(s == 1)
		human->rank = a;
	else
		com->rank = a;
}

void show (int s, Player *human, Player *com) {
	if(s == 1)
		printf("%d\n", human->budget);
	else
		printf("%d\n", com->budget);
}

void raise (int s, Player *human, Player *com) {
	if(s == 1) {
		if(human->budget >= com->bet - human->bet) {
			human->budget = human->budget - (com->bet - human->bet);
			human->bet = com->bet;
//			human->budget = human->budget - human->bet;
//			human->bet = com->bet;
			if(human->budget >= human->bet) {
				if(com->budget >= human->bet) {
					human->budget = human->budget - human->bet;
//					com->budget = com->budget - human->bet;
					human->bet = 2 * (human->bet);
				}
				else {	//game ends
					win(human, com);
				}
			}
			else 
				printf("NOT ENOUGH MONEY\n");
		}
		else 
			printf("NOT ENOUGH MONEY\n");
	}
	
	else {
		if(com->budget >= human->bet - com->bet) {
			com->budget = com->budget - (human->bet - com->bet);
			com->bet = human->bet;
//			com->budget = com->budget - com->bet;
//			human->bet = com->bet;
			if(com->budget >= com->bet) {
				if(human->budget >= com->bet) {
					com->budget = com->budget - com->bet;
//					human->budget = human->budget - com->bet;
					com->bet = 2 * (com->bet);
				}
				else { 	//game ends
					win(com, human);
				}
			}
			else
				printf("NOT ENOUGH MONEY\n");
		}
		else 
			printf("NOT ENOUGH MONEY\n");
	}
}

void call (int s, Player *human, Player *com) {
	if(s == 1) {
		human->isover = 1;
		human->budget = human->budget - (com->bet - human->bet);
		human->bet = com->bet;
	}
	else {
		com->isover = 1;
		com->budget = com->budget - (human->bet - com->bet);
		com->bet = human->bet;
	}

	if(human->isover == 1 && com->isover == 1)
		determine(human, com);
}

void fold (int s, Player *human, Player *com) {
	if( s == 1) {
		win(com, human);
	}
	else {
		win(human, com);
	}
}

int main(void) {
	Player human = {0, 0, 0, 0, 0};
	Player com = {0, 0, 0, 0, 0};
	while(1) {
		char subject[10];
		char action[10];
		int s = 0;
		int input;

		if(scanf("%s",subject) == EOF)
			break;

		if(strcmp(subject, "HUMAN") == 0)
			s = 1;

		scanf("%s",action);

		if(strcmp("START", action) == 0) {
			start(s, &human, &com);
		}

		else if(strcmp("RAISE", action) == 0) {
			raise(s, &human, &com);
		}

		else if(strcmp("CALL", action) == 0) {
			call(s, &human, &com);
		}

		else if(strcmp("FOLD", action) == 0) {
			fold(s, &human, &com);
		}

		else if(strcmp("SHOW", action) == 0) {
			show(s, &human, &com);
		}

		else if(strcmp("ADD", action) == 0) {
			scanf("%d", &input);
			//printf("%d\n",input);
			add(s, input, &human, &com);
		}

		else if(strcmp("MINUS", action) == 0) {
			scanf("%d", &input);
			minus(s, input, &human, &com);
		}

		else if(strcmp("VALUE",action) == 0) {
			scanf("%d", &input);
			value(s, input, &human, &com);
		}
	}
	return 0;
}
