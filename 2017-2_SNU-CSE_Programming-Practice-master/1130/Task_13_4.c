#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// do not modify this struct!!!!
typedef struct player {
	int budget;
	int value;
	int call;
	int bet;
} Player;

void merge(int arr[], int l, int m, int r) {
	int i = 0;
	int j = 0;
	int start = l;
	int *arr1 = (int*) malloc(sizeof(int) * (m-l+1));
	int *arr2 = (int*) malloc(sizeof(int) * (r-m));

	for(int k = l ; k <= m ; k++) {
		arr1[k-l] = arr[k];
	}
	for(int k = (m+1) ; k <= r ; k++) {
		arr2[k-(m+1)] = arr[k];
	}

	while(i < (m-l+1) && j < (r-m)) {
		if(arr1[i] >= arr2[j]) 
			arr[start++] = arr2[j++];
		else 
			arr[start++] = arr1[i++];
	}

	while(i < (m-l+1)) {
		arr[start++] = arr1[i++];
	}
	while(j < (r - m)) {
		arr[start++] = arr2[j++];
	}
}

void mergesort(int arr[], int l, int r) {
	int m = (l + r) / 2;
	if(l != r) {
		mergesort(arr, l, m);
		mergesort(arr, (m+1), r);
		merge(arr, l, m, r);
	}
}

int samecard(int num[5]) {
	int cnt = 0;
	for(int i = 0 ; i < 4 ; i++) {
		for(int j = (i+1) ; j < 5 ; j++) {
			if(num[i] == num[j])
				cnt++;
		}
	}
	return cnt;		//6 for 4card, 4 for full, 3 for tri, 2 for 2pa, 1 for 1pa
}

int straight(int num[5]) {
	if((num[1] == num[0] + 1) && (num[2] == num[0] + 2) && (num[3] == num[0] + 3) && (num[4] == num[0] + 4))
		return 1;
	else return 0;
}

int flush(int sym[5]) {
	if((sym[0] == sym[1]) && (sym[0] == sym[2]) && (sym[0] == sym[3]) && (sym[0] == sym[4]))
		return 1;
	else return 0;
}


int determine_hand(char c[5][4]){
//   return 0;
	int num[5];
	int sym[5];
	
	for(int i = 0; i < 5 ; i++) {
		if(c[i][0] == 'S')
			sym[i] = 0;
		else if(c[i][0] == 'C')
			sym[i] = 1;
		else if(c[i][0] == 'D')
			sym[i] = 2;
		else 
			sym[i] = 3;
	}

	for(int i = 0 ; i < 5 ; i++) {
		if( c[i][1] == '1') 
			num[i] = 10;
		else if(c[i][1] == 'J')
			num[i] = 11;
		else if(c[i][1] == 'Q')
			num[i] = 12;
		else if(c[i][1] == 'K')
			num[i] = 13;
		else if(c[i][1] == 'A')
			num[i] = 14;
		else {
			num[i] = atoi(&c[i][1]);
		}
	}
	mergesort(num, 0, 4);
//	for(int i = 0 ; i < 5 ; i ++ ) { printf("%d %d\n", sym[i], num[i]);}
	if((straight(num) == 1) && (flush(sym) == 1) && (num[0] == 10)) //ro st fl
		return 9;
	else if((straight(num) == 1) && (flush(sym) == 1)) //st fl
		return 8;
	else if(samecard(num) == 6)
		return 7;
	else if(samecard(num) == 4)
		return 6;
	else if(flush(sym) == 1)
		return 5;
	else if(straight(num) == 1)
		return 4;
	else if(samecard(num) == 3)
		return 3;
	else if(samecard(num) == 2)
		return 2;
	else if(samecard(num) == 1)
		return 1;
	else
		return 0;
}

//win function
void win(Player *winner, Player *loser) {
	winner->budget = winner->budget + winner->bet + loser->bet;
	winner->bet = 0;
	winner->call = 0;
//	winner->value = 0;
	loser->bet = 0;
	loser->call = 0;
//	loser->value = 0;
}

//winner determine function
void determine(Player *a, Player *b) {
	if(a->value > b->value) 
		win(a, b);
	else if(a->value < b->value) 
		win(b, a);
	else {
		a->budget = a->budget + a->bet;
		b->budget = b->budget + b->bet;
		a->bet = 0;
		a->call = 0;
//		a->value = 0;
		b->bet = 0;
		b->call = 0;
//		b->value = 0;
	}
}

int start(int s, Player *human, Player *com) {
	if(human->budget < 100 || com->budget < 100) {
		printf("NOT ENOUGH MONEY\n");
		return 1;
	}
	else {
		human->budget = human->budget - 100;
		com->budget = com->budget - 100;
		human->bet = 100;
		com->bet = 100;
		human->call = 0;
		com->call = 0;
		return 0;
	}
}

//read and com<-0, hu<-1 insert
int add (int s, int a , Player *human, Player *com) {
	if(s == 1) 
		human->budget = ((human->budget) + a);
	else 
		com->budget = ((com->budget) + a);
//	printf("%d\n", human->budget);
	return 0;
}

int minus (int s, int a, Player *human, Player *com) {
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
	return 0;
}

int value (int s, int a, Player *human, Player *com) {
	if(s == 1)
		human->value = a;
	else
		com->value = a;
	return 0;
}

int show (int s, Player *human, Player *com) {
	if(s == 1)
		printf("%d\n", human->budget);
	else
		printf("%d\n", com->budget);
	return 0;
}

int raise (int s, Player *human, Player *com) {
	if(s == 1) {
		if(human->budget >= com->bet - human->bet) {
			human->budget = human->budget - (com->bet - human->bet);
			human->bet = com->bet;
//			human->budget = human->budget - human->bet;
//			human->bet = com->bet;
			if(human->budget >= human->bet) {
				if(com->budget >= human->bet) {
					com->call = 0;
					human->budget = human->budget - human->bet;
//					com->budget = com->budget - human->bet;
					human->bet = 2 * (human->bet);
				}
				else {	//game ends
					win(human, com);
					return 1;
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
					human->call = 0;
					com->budget = com->budget - com->bet;
//					human->budget = human->budget - com->bet;
					com->bet = 2 * (com->bet);
				}
				else { 	//game ends
					win(com, human);
					return 1;
				}
			}
			else
				printf("NOT ENOUGH MONEY\n");
		}
		else 
			printf("NOT ENOUGH MONEY\n");
	}
	return 0;
}

int call (int s, Player *human, Player *com) {
	if(s == 1) {
		human->call = 1;
		human->budget = human->budget - (com->bet - human->bet);
		human->bet = com->bet;
	}
	else {
		com->call = 1;
		com->budget = com->budget - (human->bet - com->bet);
		com->bet = human->bet;
	}

	if(human->call == 1 && com->call == 1) {
		determine(human, com);
		return 1;
	}
	else return 0;
}

int fold (int s, Player *human, Player *com) {
	if(s == 1) {
		win(com, human);
	}
	else {
		win(human, com);
	}
	return 1;
}


int call_command(Player* human, Player* computer, char* command){
//  return 1;
	char *subject = strtok(command," ");
	char *action = strtok(NULL, " ");
	char *amount = strtok(NULL, " ");
	int money = 0;
	if (amount != NULL)
		money = atoi(amount);
	int s = 0;
//	printf("DEBUG: %s, %s, %d\n", subject, action, money);
	if (strcmp(subject,"HUMAN") == 0)
		s = 1;

	if(strcmp(action, "START") == 0) 
		return start(s, human, computer);
	else if(strcmp(action, "RAISE") == 0) 
		return raise(s, human, computer);
	else if(strcmp(action, "CALL") == 0)
		return call(s, human, computer);
	else if(strcmp(action, "FOLD") == 0)
		return fold(s, human, computer);
	else if(strcmp(action, "SHOW") == 0)
		return show(s, human, computer);
	else if(strcmp(action, "ADD") == 0) 
		return add(s, money, human, computer);
	else if(strcmp(action, "MINUS") == 0)
		return minus(s, money, human, computer);
	else if(strcmp(action, "VALUE") == 0)
		return value(s, money, human, computer);
}

// comment out line below this when submitting!
/*
char *intro = "\
*************************\n\
|     W E L C O M E     |\n\
|          T O          |\n\
|         T H E         |\n\
|   P O K E R G A M E   |\n\
*************************\
";

char *explanation = "\n\
********* RULES *********\n\
1. [The Poker Game] consists of %d rounds.\n\
2. On each round, HUMAN and COMPUTER takes 5 cards.\n\
3. If round number is odd, HUMAN starts betting first, if not, COMPUTER starts first.\n\
*************************\n\
";

char score_to_name[10][25] = {
	"No Pair",
	"One Pair",
	"Two Pair",
	"Three Card",
	"Straight",
	"Flush",
	"Full House",
	"Four Card",
	"Straight Flush",
	"Royal Straight Flush",
};

int main(){
	
    int n_games = 10; // # of games
    int human_initial_money = 2000;
    int computer_initial_money = 2000;
    
    // these cards must be changed to random in the final game!
    char human_cards[10][5][4] = {
		"C9","H4","CQ","HK","SQ",
		"DK","D5","DJ","DQ","H4",
		"HJ","DK","D2","CQ","C6",
		"D6","H3","S10","SJ","H7",
		"D7","S2","H10","SJ","DQ",
		"D7","S4","CA","D9","D10",
		"S2","H3","HJ","H10","C3",
		"DK","DJ","C8","HK","C7",
		"C9","C8","H4","DQ","SQ",
		"CQ","C7","C3","SA","D4"
    };
    char computer_cards[10][5][4] = {
		"SJ","CJ","S10","DK","D7",
		"H9","S3","C4","C2","D7",
		"S9","H10","HQ","SJ","CK",
		"D2","C3","S5","S3","C6",
		"SA","DK","H4","C9","HK",
		"C3","S5","HJ","DJ","H10",
		"S5","SQ","D10","C4","CK",
		"D3","S7","H3","CA","DA",
		"H9","HA","H5","CQ","C4",
		"HK","H4","C5","C2","C8"
    };
    
    static Player human;
    static Player computer;
    
    char command[50];
    
    // show intro message and rules
    printf("%s\n", intro);
    printf(explanation, n_games);
    
    // start the game
    
    // set default budget of HUMAN and COMPUTER
    sprintf(command, "HUMAN ADD %d", human_initial_money); // cmd "HUMAN ADD 2000"
    call_command(&human, &computer, command);
    sprintf(command, "COMPUTER ADD %d", computer_initial_money); // cmd = "COMPUTER ADD 2000"
    call_command(&human, &computer, command);
    
    for(int i = 0; i < n_games; i++){
    	printf("\n***** ROUND %3d *****\n", i+1);
    	
    	int human_score = determine_hand(human_cards[i]);
    	int computer_score = determine_hand(computer_cards[i]);
    	
    	printf("\n# HUMAN CARDS\n\n");
    	printf("| %3s %3s %3s %3s %3s | ==> [ %s ]\n", human_cards[i][0], human_cards[i][1], human_cards[i][2],
									human_cards[i][3], human_cards[i][4], score_to_name[human_score]);
		
		
		printf("\n-- COMPUTER CARDS --\n\n");
   		printf("| %3s %3s %3s %3s %3s | ==> [ %s ]\n", computer_cards[i][0], computer_cards[i][1], computer_cards[i][2],
									computer_cards[i][3], computer_cards[i][4], score_to_name[computer_score]);
		
		
		printf("\n*********************\n\n");

        // set value
		sprintf(command, "HUMAN VALUE %d", human_score);
		call_command(&human, &computer, command);
		sprintf(command, "COMPUTER VALUE %d", computer_score);
		call_command(&human, &computer, command);
		printf("%d %d \n", human.value, computer.value);

        // start betting
		if((i+1) % 2 == 1)
			strcpy(command, "HUMAN START");
		else
			strcpy(command, "COMPUTER START");		
	
		printf("%s\n", command);
		call_command(&human, &computer, command);
		
        // loop until bet ends
		while(1){
            
            if(!fgets(command, sizeof(command), stdin) && feof(stdin)) break;
            command[strcspn(command, "\r\n")] = '\0';
            
			int result = call_command(&human, &computer, command);
			
            // bet ended
			if(result != 0){
                
                // show results
		    	printf("\n-- HUMAN CARDS --\n\n");
		    	printf("| %3s %3s %3s %3s %3s | ==> [ %s ]\n", human_cards[i][0], human_cards[i][1], human_cards[i][2],
											human_cards[i][3], human_cards[i][4], score_to_name[human_score]);
				
				
				printf("\n-- COMPUTER CARDS --\n\n");
		   		printf("| %3s %3s %3s %3s %3s | ==> [ %s ]\n", computer_cards[i][0], computer_cards[i][1], computer_cards[i][2],
											computer_cards[i][3], computer_cards[i][4], score_to_name[computer_score]);
			
				printf("\n");
				printf("# HUMAN BUDGET    ==> ");
				strcpy(command, "HUMAN SHOW");
				call_command(&human, &computer, command);
				printf("# COMPUTER BUDGET ==> ");
				strcpy(command, "COMPUTER SHOW");
				call_command(&human, &computer, command);
				break;	
			}
		}
	}
}
*/
