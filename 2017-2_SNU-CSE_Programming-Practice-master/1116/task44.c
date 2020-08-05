#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int element;
	struct node *next;
} node;

typedef struct list {
	char *name;
	int size;
	node *head;
	node *tail;
} list;

list all_lists[1000];
int num_lists = 0;

list *search(char *name) {
	for(int i = 0; i < num_lists; i++) {
		if (strcmp(name, all_lists[i].name) == 0) {
			return &all_lists[i];
		}
	}
	return NULL;
}

node *location(list *list, int n) {
	if(list.size == 0)
		return NULL;
	else {
		int i = 0;
		node *d = (node*) malloc(sizeof(node));
		d= list->head.next;
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
	list list;
	int len = strlen(name);
	list.name = malloc((len+1) * sizeof(char));
	strcpy(list.name, name);
	list.name[len] = '\0';
	list.size = 0;
	list.head.element = 0;
	list.head.next = &(list.tail);
	all_lists[num_lists++] = list;
}

void push_front(char *name, int element) {
	list *list = search(name);
	node *front = (node*) malloc(sizeof(node));
	front->element = element;
	front->next = list->next;
	list->head.next = front;
	list->size++;
}

void push_back(char *name, int element) {
	list *list = search(name);
	node *back =(node*) malloc(sizeof(node));
	node *d =(node*) malloc(sizeof(node));
	back->element = element;
	d = location(list, (list->size)-1);
	d->next = back;
	back->next = &(list->tail);
}

int print_front(char *name) {
	list *list = search(name);
	if(list->head.next != &(list->tail)) {
		printf("%d\n", list->head.next->element);
	}



