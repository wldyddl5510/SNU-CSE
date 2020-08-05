#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct node {
	int element;
	struct node *next;
	struct node *prev;
} node;

typedef struct {
	char *name;
	int size;
	node tail;
	node head;
} linked_list;

linked_list all_lists[1000];
int num_lists = 0;

linked_list *search(char *name) {
	for (int i = 0; i < num_lists; i++) {
		if (strcmp(name, all_lists[i].name) == 0) {
			return &all_lists[i];
		}
	}
	return NULL;
}

node *location(linked_list *list, int n) {
	if(list->head.next == &(list->tail))
		return NULL;
	else {
		int i = 0;
		node *d;
		d = list->head.next;
		if((list->size) <= n) 
			return NULL;
		else {
			while(i<n) {
				i++;
				d = d->next;
			}
		return d;
		}
	}
}

void make(char *name) {
	linked_list list;
	int len = strlen(name);
	list.name = malloc((len + 1) * sizeof(char));
	strcpy(list.name, name);
	list.name[len] = '\0';
	list.size = 0;
	list.head.element = 0;
	list.head.next = &(list.tail);
	list.head.prev = NULL;
	list.tail.element = 0;
	list.tail.next = NULL;
	list.tail.prev = &(list.head);
	all_lists[num_lists++] = list;
}

void push_front(char *name, int element) {
	linked_list *list = search(name);
	node *front = (node*) malloc(sizeof(node));
	front->element = element;
	front->next = list->head.next;
	front->prev = &(list->head);
	list->head.next->prev = front;
	list->head.next = front;
	list->size++;
}

void push_back(char *name, int element) {
	linked_list *list = search(name);
	node *back = (node*) malloc(sizeof(node));
	back->element = element;
	printf("%d \n", list->head.next->element);
	printf("%d \n", list->tail.prev->element);
	back->next = &(list->tail);
	back->prev = list->tail.prev;
	printf("%d ", list->tail.prev->element);
	list->tail.prev->next = back;
	list->tail.prev = back; 
	list->size++;
	printf("%d ", list->head.element);
	printf("%d ", list->head.next->element);
	printf("%d ", list->head.next->next->element);
	printf("%d ", list->tail.prev->element);
}


void print_front(char *name) {
	linked_list *list = search(name);
	int d;
	d = list->head.next->element;
	printf("%d\n",d);
}

void print_back(char *name) {
	linked_list *list = search(name);
	int d;
	d = location(list, (list->size)-1)->element;
//	d = list->tail.prev->element;
	printf("%d\n",d);
}

void insert(char *name, int index, int element) {
	linked_list *list = search(name);
	if(index == 0)
		push_front(name, element);
	else if(index == (list->size))
		push_back(name, element);
	else {
		node *d1 = (node*) malloc(sizeof(node));
		node *d;
		d1->element = element;
		d = location(list, (index-1));
		d1->prev = d;
		d->next->prev = d1;
		d1->next = d->next;
		d->next = d1;
		list->size++;
	}
}

void delete(char *name, int index) {
	linked_list *list = search(name);
	if(index == 0) {
		list->head.next->next->prev = &(list->head);
		list->head.next->next = NULL;
		list->head.next->prev = NULL;
		list->head.next = list->head.next->next;
		list->size--;
	}
	else if(index == ((list->size)-1)) {
		list->tail.prev->prev->next = &(list->tail);
		list->tail.prev->prev = NULL;
		list->tail.prev->next = NULL;
		list->tail.prev = list->tail.prev->prev;
		list->size --;
	}
	else {
		node *d = (node*) malloc(sizeof(node));
		d = location(list, (index-1));
		d->next->next->prev = d;
		d->next->next = NULL;
		d->next->prev = NULL;
		d->next = d->next->next;
		list->size--;
	}
}

void concat(char *a, char *b) {
	linked_list *list1 = search(a);
	linked_list *list2 = search(b);
	list1->tail.prev->next = list2->head.next;
	list2->head.next->prev = list1->tail.prev;
	list1->size = (list1->size) + (list2->size);
	list1->tail.prev = NULL;
	list2->head.next = NULL;
	list1->tail = list2->tail;
}

void print_element(char *name, int index) {
	linked_list *list = search(name);
	node *d;
	d = list->head.next;
	if(index == 0) 
		printf("%d\n", list->head.next->element);
	else if(index == ((list->size)-1))
		printf("%d\n", list->tail.prev->element);
	else {
		d = location(list, index);
		printf("%d\n", d->element);
	}
}

void print(char *name) {
	linked_list *list = search(name);
	int i = 0;
	node *d;
	d = list->head.next;
	while(i < (list->size)) {
		printf("%d ",d->element);
		d = d->next;
		i++;
	}
	printf("\n");
}

/*	if(d != &(list->tail)){
		while(1) {
			printf("%d ",d->element);
			if(d->next == &(list->tail))
				break;
			d = d->next;
		}
		printf("\n");
	}
}
*/
void print_size(char *name) {
	linked_list *list = search(name);
	printf("%d\n", list->size);
}

void pop_front(char *name) {
	linked_list *list = search(name);
	assert(list->head.next != &(list->tail));
	printf("%d\n",list->head.next->element);
	list->head.next->next->prev = &(list->head);
	list->head.next = list->head.next->next;
	list->size--;
}

void pop_back(char *name) {
	linked_list *list = search(name);
	assert(list->head.next != &(list->tail)); 
	printf("%d\n", list->tail.prev->element);
	list->tail.prev->prev->next = &(list->tail);
	list->tail.prev = list->tail.prev->prev;
	list->size--;
}

int main(void) {
	while(1) {
		char op[30], opA[10], opB[10],  dummy[10];
		int n, m;

		if(scanf("%s",op) == EOF)
			break;

		if(strcmp(op, "MAKE") == 0) {
			scanf("%s",opA);
			make(opA);
		}

		if(strcmp(op, "PUSH_FRONT") == 0) {
			scanf("%s", opA);
			scanf("%d", &n);
			push_front(opA, n);
		}

		if(strcmp(op, "PUSH_BACK") == 0) {
			scanf("%s", opA);
			scanf("%d", &n);
			push_back(opA, n);
		}

		if(strcmp(op, "PRINT_FRONT") == 0) {
			scanf("%s", opA);
			print_front(opA);
		}

		if(strcmp(op, "PRINT_BACK") == 0) {
			scanf("%s", opA);
			print_back(opA);
		}

		if(strcmp(op, "INSERT") == 0) {
			scanf("%s", opA);
			scanf("%d %d", &n, &m);
			insert(opA, n, m);
		}

		if(strcmp(op, "DELETE") == 0) {
			scanf("%s", opA);
			scanf("%d", &n);
			delete(opA, n);
		}

		if(strcmp(op, "CONCAT") == 0) {
			scanf("%s", opA);
			scanf("%s", opB);
			concat(opA, opB);
		}

		if(strcmp(op, "PRINT_ELEMENT") == 0) {
			scanf("%s", opA);
			scanf("%d", &n);
			print_element(opA, n);
		}

		if(strcmp(op, "PRINT") == 0) {
			scanf("%s", opA);
			print(opA);
		}

		if(strcmp(op, "PRINT_SIZE") == 0) {
			scanf("%s", opA);
			print_size(opA);
		}

		if(strcmp(op, "POP_FRONT") == 0) {
			scanf("%s", opA);
			pop_front(opA);
		}

		if(strcmp(op, "POP_BACK") == 0) {
			scanf("%s", opA);
			pop_back(opA);
		}
	}
}
