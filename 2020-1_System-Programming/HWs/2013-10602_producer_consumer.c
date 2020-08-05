// 2013-10602 Jiyoung Park
#include <stdlib.h>

//#define N 1000

typedef struct {
	int *buf;
	int n;
	int front;	//first in
	int rear;	//last in
} queue;

void init_queue(queue *q, int n);
void enqueue(queue *q, int item);
int dequeue(queue *q);
void deinit_queue(queue *q);

void init_queue(queue *q, int n) {
	q -> buf = calloc(n, sizeof(int));
	q -> n = n;
	q -> front = 0; // First in
	q -> rear = 0; 	// Last in
}
//Circular Queue


void enqueue(queue *q, int item) {
	int N = q -> n;
	int changed_rear = (q -> rear + 1) % N;

	// busy wait if queue is full
	while(1) {
		if(changed_rear != q -> front) {
			break;
		}
	}
	q -> buf[changed_rear] = item; //enqueue
	q -> rear = changed_rear; // change rear index
}

int dequeue(queue *q) {
	int item;
	int start = q -> front;
	int N = q -> n;
	// busy wait if queue is empty
	while(1) {
		if(start != q -> rear) {
			break;
		}
	}
	item = q -> buf[start]; // get First-In item
	q -> front = (start + 1) % N;	// dequeue & change front index
	return item;	//return dequeued item
}

void deinit_queue(queue *q) {
	free(q -> buf);
}
