#include <stdio.h>
#include <stdlib.h>

struct element{
		int d;
		struct element *next;
};
typedef struct element element;

struct stack{
		int c;
		element* top;
};
typedef struct stack stack;

void push( int d, stack *a){
		element* p;
		p = malloc(sizeof(element));
		p->d=d;
		p->next = a->top;
		a->top = p;
		a->c++;
}

int pop(stack *a){
		int d;
		element* p;
		d = a->top->d;
		p = a->top;
		a->top=a->top->next;
		a->c--;
		if(p != NULL)free(p);
		return d;
}

int main(void){
		char input;
		stack a;
		int first, second,result;
		int b;

		while(scanf("%c",&input)!=EOF){
				if((input >= '0') && (input <= '9')){
					push((input - '0'),&a);
				}
				else if((input == '+') || (input == '-') || (input == '*')){
						first=pop(&a);
						second=pop(&a);

						if(input == '+'){
							result=first+second;
						}
						else if(input=='-'){
							result = second - first;
						}
						else if(input == '*'){
							result = first*second;
						}

					push(result, &a);
				}
		}
		b=pop(&a);
		printf("%d\n",b);
		return 0;
}
