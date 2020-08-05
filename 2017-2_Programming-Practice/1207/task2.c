#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
/*
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
	int isstr = straight(num);
	int isflu = flush(num);
	int cardnum = samecard(num);
//	for(int i = 0 ; i < 5 ; i ++ ) { printf("%d %d\n", sym[i], num[i]);}
	if((isstr == 1) && (isflu == 1)) {
		if (num[0] == 10) //ro st fl
			return 9;
		else  //st fl
			return 8;
	}
	else {
		if(cardnum == 6)
			return 7;
		else if(cardnum == 4)
			return 6;
		else if(isflu == 1)
			return 5;
		else if(isstr == 1)
			return 4;
		else if(cardnum == 3)
			return 3;
		else if(cardnum == 2)
			return 2;
		else if(cardnum == 1)
			return 1;
		else
			return 0;
	}
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
		return -1;
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
		else {
			printf("NOT ENOUGH MONEY\n");
			return -1;
		}
	}
	else {
		if(com->budget >= a) 
			com->budget = ((com->budget) - a);
		else {
			printf("NOT ENOUGH MONEY\n");
			return -1;
		}
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
			else {
				printf("NOT ENOUGH MONEY\n");
				return -1;
			}
		}
		else {
			printf("NOT ENOUGH MONEY\n");
			return -1;
		}
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
			else {
				printf("NOT ENOUGH MONEY\n");
				return -1;
			}
		}
		else {
			printf("NOT ENOUGH MONEY\n");
			return -1;
		}
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
	// Implement your own function!
    // printf("NOT ENOUGH MONEY\n") --> return -1;
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

int posi_str(int num[3]) {
	if(num[1] == num[0] + 1 && num[2] == num[0] + 2)
		return 1;
	else if(num[1] == num[0] + 1 && num[2] == num[0] + 3) 
		return 1;
	else if(num[1] == num[0] + 1 && num[2] == num[0] + 4)
		return 1;
	else if(num[1] == num[0] + 2 && num[2] == num[0] + 3)
		return 1;
	else if(num[1] == num[0] + 2 && num[2] == num[0] + 4)
		return 1;
	else if(num[1] == num[0] + 3 && num[2] == num[0] + 4)
		return 1;
	else return 0;
}

int posi_flush(int sym[3]) {
	if(sym[0] == sym[1] && sym[0] == sym[2])
		return 1;
	else return 0;
}

int least_triple(int num[3]) {
	if(num[0] == num[1] && num[1] == num[2])
		return 1;
	else return 0;
}

int least_pair(int num[3]) {
	if(num[0] == num[1] || num[1] == num[2])
		return 1;
	else return 0;
}

int infer_hand(char c[3][4]) {
	int num[3];
	int sym[3];
	for(int i = 0 ; i < 3 ; i++) {
		if(c[i][0] == 'S')
			sym[i] = 0;
		else if(c[i][0] == 'C')
			sym[i] = 1;
		else if(c[i][0] == 'D')
			sym[i] = 2;
		else
			sym[i] = 3;
//	}
//	for(int i = 0 ; i < 3 ; i++) {
		if(c[i][1] == '1')
			num[i] = 10;
		else if (c[i][1] == 'J')
			num[i] == 11;
		else if(c[i][1] == 'Q')
			num[i] = 12;
		else if(c[i][1] == 'K') 
			num[i] = 13;
		else if(c[i][1] = 'A')
			num[i] = 14;
		else 
			num[i] = atoi(&c[i][1]);
	}
	mergesort(num, 0, 2);
	if(least_triple(num) == 1) 
		return 3;
	else if(posi_str(num) == 1)
		return 2;
	else if(posi_flush(num) == 1)
		return 1;
	else if(least_pair(num) == 1)
		return 0;
}

	
int choose_command(char human_cards[3][4], char computer_cards[5][4], Player* human, Player* computer){
	// return value : call = 0, raise = 1, fold = 2
	int comrank = determine_hand(computer_cards);
	int posi_humanrank = infer_hand(human_cards);
//read human card
	int human_sym[3], human_num[3], com_sym[5], com_num[5];

	for(int i = 0 ; i < 3; i++) {
		if(human_cards[i][0] == 'S') 
			human_sym[i] = 0;
		else if(human_cards[i][0] == 'C') 
			human_sym[i] = 1;
		else if(human_cards[i][0] == 'D') 
			human_sym[i] = 2;
		else 
			human_sym[i] = 3;

		if(human_cards[i][1] == '1') 
			human_num[i] = 10;
		else if(human_cards[i][1] == 'J') 
			human_num[i] = 11;
		else if(human_cards[i][1] == 'Q') 
			human_num[i] = 12;
		else if(human_cards[i][1] == 'K') 
			human_num[i] = 13;
		else if(human_cards[i][1] == 'A') 
			human_num[i] = 14;
		else 
			human_num[i] = atoi(&human_cards[i][1]);
	}
	mergesort(human_num, 0, 2);

	//read com card

	for(int i = 0 ; i < 5; i++) {
		if(computer_cards[i][0] == 'S') 
			com_sym[i] = 0;
		else if(computer_cards[i][0] == 'C') 
			com_sym[i] = 1;
		else if(computer_cards[i][0] == 'D') 
			com_sym[i] = 2;
		else 
			com_sym[i] = 3;

		if(computer_cards[i][1] == '1') 
			com_num[i] = 10;
		else if(computer_cards[i][1] == 'J') 
			com_num[i] = 11;
		else if(computer_cards[i][1] == 'Q') 
			com_num[i] = 12;
		else if(computer_cards[i][1] == 'K') 
			com_num[i] = 13;
		else if(computer_cards[i][1] == 'A') 
			com_num[i] = 14;
		else 
			com_num[i] = atoi(&computer_cards[i][1]);
	}
	mergesort(com_num, 0, 4);

	if(comrank == 9) {
		if(computer->budget >= (2*human->bet)) {
			return 1;
		}
		else return 0;
	}
	else if(posi_humanrank == 3 && comrank < 3)
		return 2;
	else if(posi_humanrank == 0 && comrank == 0)
		return 2;
	else if(comrank == 5 && posi_humanrank == 1 && com_sym[0] == human_sym[0] ) {
		if(computer->budget >= (2*human->bet)) {
			return 1;
		}
		else return 0;
	}
	else return 0;
*/	
/*	if(human->value > computer->value)
		return 2;
	else if(human->value < computer->value) {
		if(computer->budget >= (2 *human->bet))
			return 1;
		else if( computer->budget >= human->bet)
			return 0;
	}
	else {
		if(computer->budget >= human->bet)
			return 0;
	}*/
//}

/**************
	comment out below this line when submitting!
	comment out below this line when submitting!
*************/
/*
// select n random numbers in [0, max_num)
int *pick_rand_nums(int max_num, int n){
	int *nums = (int *)malloc(sizeof(int) * n);
	int cnt = 0;
	int r;
	
	while(cnt < n){
		r = rand()%max_num;
		
		int chk = 1;
		for(int i = 0; i < cnt; i++){
			if(nums[i] == r){
				chk = 0;
				break;
			}
		}
		
		if(chk){
			nums[cnt++] = r;
		}
	}
	
	return nums;
}

// poker cards
char cards[52][4] = {"DA","D2","D3","D4","D5","D6","D7","D8","D9","D10","DJ","DQ","DK",
						"HA","H2","H3","H4","H5","H6","H7","H8","H9","H10","HJ","HQ","HK",
						"SA","S2","S3","S4","S5","S6","S7","S8","S9","S10","SJ","SQ","SK",
						"CA","C2","C3","C4","C5","C6","C7","C8","C9","C10","CJ","CQ","CK"};

// possible bet commands
char commands[2][3][15] = {
	"COMPUTER CALL", "COMPUTER RAISE", "COMPUTER FOLD",
	"HUMAN CALL", "HUMAN RAISE", "HUMAN FOLD"
};

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
	
	srand(time(NULL));

    int n_games = 30; // # of games
    int human_initial_money = 100000000;
    int computer_initial_money = 10000000;
    int win_condition = computer_initial_money / 50; // if player earns more than this, player wins;
    int win_count = 0;
    
    char human_cards[5][4];
    char computer_cards[5][4];
    
    char command[50];
    
    // show intro message and rules
    printf("%s\n", intro);
    printf(explanation, n_games);
    
	// start the game
    Player human = {0,0,0,0};
    Player computer = {0,0,0,0};
    
    // set default budget of HUMAN and COMPUTER
    sprintf(command, "HUMAN ADD %d", human_initial_money);
    call_command(&human, &computer, command);
    sprintf(command, "COMPUTER ADD %d", computer_initial_money);
    call_command(&human, &computer, command);
    
    for(int i = 0; i < n_games; i++){
    	
    	printf("\n***** ROUND %3d *****\n", i+1);
    	
    	// select 10 random cards
    	int* random_numbers = pick_rand_nums(52, 10);
    
    	// set human, computer hand
    	for(int j = 0; j < 5; j++){
    		strcpy(human_cards[j], cards[random_numbers[j]]);
			strcpy(computer_cards[j], cards[random_numbers[j+5]]); 
		}
		
		free(random_numbers);
		
    	int human_score = determine_hand(human_cards);
    	int computer_score = determine_hand(computer_cards);
    	
    	printf("\n# HUMAN CARDS\n\n");
    	printf("| %3s %3s %3s %3s %3s | ==> [ %s ]\n", human_cards[0], human_cards[1], human_cards[2],
									human_cards[3], human_cards[4], score_to_name[human_score]);
		
		
		//printf("\n-- COMPUTER CARDS --\n\n");
   		//printf("| %3s %3s %3s %3s %3s | ==> [ %s ]\n", computer_cards[0], computer_cards[1], computer_cards[2],
		//							computer_cards[3], computer_cards[4], score_to_name[computer_score]);
		
		printf("\n*********************\n\n");
		
        // set value
		sprintf(command, "HUMAN VALUE %d", human_score);
		call_command(&human, &computer, command);
		sprintf(command, "COMPUTER VALUE %d", computer_score);
		call_command(&human, &computer, command);
		
        // start betting
        int human_turn = ((i+1) % 2 == 1);
        int fail;
        
		if(human_turn){
			strcpy(command, "HUMAN START");
			printf("%s\n", command);
			fail = call_command(&human, &computer, command);
		} else{
			strcpy(command, "COMPUTER START");
			printf("%s\n", command);
			fail = call_command(&human, &computer, command);
		}
		
		// NOT ENOUGH MONEY --> game end 
		if(fail == -1)
			break;
			
        // loop until bet ends
		while(1){
			
			int pick;
			int result = -1;
			
			// loop while command returns -1 (NOT ENOUGH MONEY)
			while(result == -1){
				
				// if it is human's turn, you give a command
				if(human_turn){
	            	fgets(command, sizeof(command), stdin);
	            	command[strcspn(command, "\r\n")] = '\0';
	            	result = call_command(&human, &computer, command);
				}
				// if it is computer's turn, AI will give a command
				else{
					pick = choose_command(human_cards+2, computer_cards, &human, &computer);
					strcpy(command, commands[human_turn][pick]);
					printf("%s\n", command);
					result = call_command(&human, &computer, command);
				}
				
				if(result == -1) // NOT ENOUGH MONEY
					continue;
			}
			
            // bet ended
			if(result == 1){
                
                // show results
		    	printf("\n-- HUMAN CARDS --\n\n");
		    	printf("| %3s %3s %3s %3s %3s | ==> [ %s ]\n", human_cards[0], human_cards[1], human_cards[2],
											human_cards[3], human_cards[4], score_to_name[human_score]);
				
				
				printf("\n-- COMPUTER CARDS --\n\n");
		   		printf("| %3s %3s %3s %3s %3s | ==> [ %s ]\n", computer_cards[0], computer_cards[1], computer_cards[2],
											computer_cards[3], computer_cards[4], score_to_name[computer_score]);
			
				printf("\n");
				printf("# HUMAN BUDGET    ==> ");
				strcpy(command, "HUMAN SHOW");
				call_command(&human, &computer, command);
				printf("# COMPUTER BUDGET ==> ");
				strcpy(command, "COMPUTER SHOW");
				call_command(&human, &computer, command);
				break;	
			}
			
			// change order
			human_turn = 1 - human_turn;
		}
	}
	
	printf("\n----- FINAL RESULT -----\n");
	strcpy(command, "HUMAN SHOW");
	printf("# HUMAN     ==> ");
	call_command(&human, &computer, command);
	strcpy(command, "COMPUTER SHOW");
	printf("# COMPUTER  ==> ");
	call_command(&human, &computer, command);
}*/
