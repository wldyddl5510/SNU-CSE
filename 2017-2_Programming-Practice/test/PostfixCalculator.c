#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int d;
	struct node *next;
} node;

typedef struct stack {
	int cnt;
	node *top;
} stack;

void push(int n, stack *a) {
	node *p = (node *)malloc(sizeof(node));
	p->d = n;
//	printf("2");
	p->next = a->top;
//	printf("3");
	a->top = p;
//	printf("4");
	a->cnt++;
}

int pop(stack *a) {
//	printf("a");
	node *p = (node *)malloc(sizeof(node));
//	printf("B");
	p = a->top;
//	printf("c");
	a->top = a->top->next;
//	printf("d");
	a->cnt--;
//	printf("e");
	int n = p->d;
//	printf("%d ",n);
	free(p);
//	printf("g");
	return n;
}

int main(void) {
	char *input[1100000];
	char dummy[30];
	int i = 0;
	int num[110000];
	char *transform;
	char op[1100000];
	int number;
	stack a;

	while(scanf("%s", dummy) != EOF) {
		input[i] = (char*)malloc((strlen(dummy) + 1) * sizeof(char));
		strcpy(input[i] , dummy);
//		printf("%s\n", input[i]);
		i++;
	}
	int length = i;
	//test
//	printf("1111\n");
//	num = (int *) malloc(length * sizeof(int));
	
	int opcnt = 0;
	int numcnt = 0;

	for(int j = 0 ; j < length ; j++) {
//		printf("333\n");
		if((input[j][0] == '+' || input[j][0] == '-' || input[j][0] == '*') && strlen(input[j]) == 1) {
//			printf("44\n");
			op[opcnt] = input[j][0];
//			printf("55\n");
			int y = pop(&a);
//			printf("wtf");
			int x = pop(&a);
			int xy;
//			printf("66");
			if(op[opcnt] == '+') {
//				printf("7");
				xy = x + y;
			}
			else if(op[opcnt] == '-') 
				xy = x - y;
			else
				xy = x * y;
//			printf("8");
			push(xy, &a);
//			printf("xy : %d\n", xy);
			opcnt++;
//			printf("66\n");
		}
		else if(input[j][0] == '-') {
//			printf("asd ");
			transform = (char*)malloc(strlen(input[j]) * sizeof(char));
			for(int k = 1 ; k < strlen(input[j])+1 ; k++) {
				transform[k-1] = input[j][k];
			}
			number = -1 * atoi(transform);
//			printf("%d when -\n", number);
			push(number, &a);
		}
		else {
//			printf("@#$");
			transform = (char*)malloc((strlen(input[j]) + 1) * sizeof(char));
			for(int k = 0 ; k < strlen(input[j])+1 ; k++) {
//				printf("%c ", input[j][k]);
				transform[k] = input[j][k];
//				printf("%c ",transform[k]);
			}
			number = atoi(transform);
//			printf("%d\n", number);
			push(number, &a);
		}
	}
//	printf("2222\n");
	
	/*
	char input[1000];
	char *number;
	stack a;
	int i = 0;
	int indicator = 0;
	while(scanf("%c", &input[i]) != EOF) {
		if(input[i] == " "
	}*/

	/*
	while(scanf("%c", &input[i]) != EOF) {
		int j = 0;
		while(!(isspace(input[i])) && input[i] != '+' && input[i] != '*') {
			j++;
		}
		if(i != 0 &&input[i] == '-') {
			if(!isspace(input[i-1])
				indicator = 1;
		}
		number = (char*) malloc((j+1) *sizeof(char));
		int num = atoi(number);
		if(indicator == 1) 
			num = num * (-1);
		push(num, &a);

		if(input[i] == '+') {
			int x = pop(&a);
			int y = pop(&a);
			int xy = x + y;
		}
		else if(input[i] == '-') {
			int x = pop(&a);
			int y = pop(&a);
			int xy = x - y;
		}
		else if(input[i] == '*') {
			int x = pop(&a);
			int y = pop(&a);
			int xy = x * y;
		}
		push(xy, &a);
	}
	*/
	printf("%d\n", pop(&a));
	return 0;
}
			

