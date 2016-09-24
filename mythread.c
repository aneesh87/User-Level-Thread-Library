
#include "mythread.h"
#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>

#define STACK_SIZE 16384

#define error(x,y) fprintf(stderr, x, y)

typedef struct node {
   void *ctx; 
   struct node * next;
} Node;

typedef struct queue {
    Node * front;
    Node * rear;
    int count;
} Queue;


Queue ready_queue = {NULL, NULL,0}, blocked_queue = {NULL, NULL,0};

void insert(Queue * QQ, void * ele) {
    
    Node * temp = calloc(1,sizeof(Node));
    
    if (temp == NULL) {
    	error("%s","Out of memory");
    	exit(1);
    }

    QQ->count++;
    temp->ctx = ele;

    if (QQ->front == NULL) {
    	QQ->front = temp;
    	QQ->rear = temp;
    	return;
    }
    QQ->rear->next = temp;
    QQ->rear = temp;
}

void * dequeue(Queue *QQ) {
	
	if (QQ->count == 0) {
		return NULL;
	}
    
    void * ctx = QQ->front->ctx;
	
	if (QQ->count == 1) {

		free(QQ->front);
        QQ->rear = NULL;
        QQ->front = NULL;
	
	} else {

		Node * temp = QQ->front;
        QQ->front = QQ->front->next;
        free(temp);
    }

    QQ->count--;
    return ctx;
}

MyThread MyThreadCreate(void(*start_funct)(void *), void *args) {

   return 0;  
}

void MyThreadYield(void) {

}

int MyThreadJoin(MyThread thread) {
   return 0;
}


void MyThreadJoinAll(void)
{


}

void MyThreadExit(void) {

}

MySemaphore MySemaphoreInit(int initialValue) {

}

void MySemaphoreSignal(MySemaphore sem) {

}

void MySemaphoreWait(MySemaphore sem) {

}

int MySemaphoreDestroy(MySemaphore sem) {
   return 0;
}

void MyThreadInit(void(*start_funct)(void *), void *args) {

}

/*

Queue Test 

int main(int argc, char **argv) {
	
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    insert(&ready_queue, &arr[0]);
    insert(&ready_queue, &arr[1]);
    insert(&ready_queue, &arr[2]);
    insert(&ready_queue, &arr[3]);
    
    printf("%d\n", *(int *)dequeue(&ready_queue));
    printf("%d\n", *(int *)dequeue(&ready_queue));
    printf("%d\n", *(int *)dequeue(&ready_queue));
    printf("%d\n", *(int *)dequeue(&ready_queue));
    printf("%p\n", dequeue(&ready_queue));
    printf("%p\n", dequeue(&ready_queue));
    insert(&ready_queue, &arr[8]);
    insert(&ready_queue, &arr[9]);
    printf("%d\n", *(int *)dequeue(&ready_queue));
    printf("%d\n", *(int *)dequeue(&ready_queue));

    return 0;
}
*/

