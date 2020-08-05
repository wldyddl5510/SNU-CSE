#include <stdio.h.>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int element;
	struct node *next;
} node;

typedef struct list {
	char *name;
	int size;
	node head;
	node tail;
} list;

list all_lists[1000];
int num_lists = 0;

list *search(char *name) {
	for(int i = 0; i < num_lists; i++) {
		if (strcmp(name, all_lists[i].name) == 0)
			return %all_lists[i];
	}
	return NULL;
}

node *location(list *list, int n) {
	if(list.size == 0)
		return NULL;
	else {
		int i = 0;
		node *d;
		d = list->head.next;
		if((list->size) <= n)
			return NULL;
		else {
			while(i < n) {
				i++;
				d = d->next;
			}
			return d;
		}
	}
}

void make(char *name) {
	list *list;
	int len = strlen(name);
	list.name = malloc((len+1) * sizeof(char));
	strcpy(list.name, name);
	list.name[len] = '\0';
	list.size = 0;
	list.head.element = 0;
	list.head.next = &(list.tail);
	list.tail.element = 0;
	list.tail.next = NULL;
	all_lists[num_lists++] = list;
}

void insert(char *name, int index, int element) {
	list *list = search(name);
	node *d = (node*) malloc(sizeof(node));
	d->element = element;
	assert(index <= list->size-1);
	if((list->size) == 0) {
		d = list->head.next; 
		d->next = &(list->tail);
	}
	else {
		d->next = location(list, index-1)->next;
		location(list, index - 1)->next = d;
	}
	list->size++;
}

void delete(char *name, int index) {
	list *list = search(name);
	if(index == 0) {
		list->head.next = list->head.next->next;
	}
	else {
		location(list, index-1)->next = location(list, index-1)->next->next;
	}
	list->size --;
}

void concat(char *a, char *b) {
	list *list1 = search(a);
	list *list2 = search(b);
	location(list1, list1->size - 1)->next = list2->head.next;
	list1->size = list1->size + list2->size;
	list1->tail = list2->tail;
}

void print_element(char *name, int index) {
	list *list = search(name);
	node *d;
	d = list->head.next;
	if(index == 0)
		printf("%d\n", list->head.next->element);
	else {
		printf("%d\n", location(list, index)->element);
	}
}

void print_size(char *name) {
	list *list = search(name);
	printf("%d\n",list->size);
}

int main(void) {
	while(1) {
		char op[30], opA[10], opB[10], dummy[10];
		int n, m;

		if(scanf("%s",op) == EOF)
			break;

		if(strcmp(op,"MAKE") == 0) {
			scanf("%s",opA);
			make(opA);
		}

		if(strcmp(op, "PUSH_FRONT") == 0) {
			scanf("%s",opA);
			scanf("%d",&n);
			insert(opA, 0, n);
		}

		
