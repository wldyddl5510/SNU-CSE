#include <stdio.h>
#include <stdlib.h>

struct element{
		int d;
		struct element* next;
};
typedef struct element element;

struct stack{
		int c;
		element* top;
};
typedef struct stack stack;

void push(int input, stack* s){
		element* p;
		p=malloc(sizeof(element));
		p->d=input;
		p->next=s->top;
		s->top=p;
		s->c++;
}

int pop(stack* s){
		int d;
		element* p;
		d=s->top->d;
		p=s->top;
		s->top = s->top->next;
		s->c--;
		if(p!=NULL) free(p);
		return d;
}

int main(void){
		int n,m;
		int* first;
		int* second;
		stack s;
		int i;
		int a;

		scanf("%d %d", &n,&m);

		first=(int*)malloc(n*sizeof(int));
		second=(int*)malloc(m*sizeof(int));

		for(i=0;i<n;i++){
				scanf("%d",&first[i]);
		}

		for(i=0;i<m;i++){
				scanf("%d",&second[i]);
		}


		if(n>=m){
				for(i=(m-1);i>=0;i--){
						if(first[(i+(n-m))]>second[i]){
								push(first[(i+(n-m))],&s);
						}
						else{
								push(second[i],&s);
						}
				}
				if((n-m)!=0){
					for(i=(n-m-1);i>=0;i--){
							push(first[i],&s);
					}
				}
		}
		else{
				for(i=(n-1);i>=0;i--){
						if(second[(i+m-n)]>first[i]){
								push(second[i+m-n],&s);
						}
						else{
								push(first[i],&s);
						}
				}
				if((m-n)!=0){
						for(i=(m-n-1);i>=0;i--){
								push(second[i],&s);
						}
				}
		}

		while(1){
				a=pop(&s);
				printf("%d ",a);
				if((s.c)==0){break;}
		}

		free(first);
		free(second);
		return 0;
}


