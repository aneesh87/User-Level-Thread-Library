#include "mythread.h"
#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>

#define STACK_SIZE 16384

#define error(y) printf("%s\n",y)

typedef struct node {
   void *obj; 
   struct node * next;
} Node;

typedef struct queue {
    Node * front;
    Node * rear;
    int count;
} Queue;

typedef struct _MyThread {
	Queue childq;
	ucontext_t ctx;
	struct _MyThread *block_on_child;
	int block_on_all;
	struct _MyThread *parent;
} Thread;

typedef struct _Semaphore {
  int value;
  Queue semq;
} Semaphore;

// Prototype
void * dequeue(Queue *);
void context_switch ();

// Globals

Thread * running;
Thread * root;
ucontext_t Main;

Queue ready_queue = {NULL, NULL,0}, blocked_queue = {NULL, NULL,0};

void remove_node(Queue * QQ, void * ele) {
	if (QQ->count == 0) {
		return;
	}
	if (QQ->front->obj == ele) {
		(void)dequeue(QQ);
		return;
	}
    Node * n1 =  QQ->front;
    Node * n2 =  QQ->front->next;

    while (n2 != NULL) {
        if (n2->obj == ele) {
          
            if (QQ->rear == n2) {
            	QQ->rear = n1;
            }
            QQ->count--;
            n1->next = n2->next;
            free(n2);
            return;
        }
        n1 = n2;
        n2 = n2->next;
    }
}

int has_element(Queue *QQ, void * ele) {
	Node * temp = QQ->front;
	while (temp != NULL) {
		//printf("%d", *(int *)(temp->obj));
		if (temp->obj == ele) {
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

void insert(Queue * QQ, void * ele) {
    
    Node * temp = calloc(1,sizeof(Node));
    if (temp == NULL) {
    	  error("Out of memory");
    	  return;
    }

    QQ->count++;
    temp->obj = ele;

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
    
    void * obj = QQ->front->obj;
	
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
    return obj;
}

MyThread MyThreadCreate(void(*start_funct)(void *), void *args) {
   if (start_funct == NULL) { error("Invalid Params"); return NULL;}
   //printf("%d\n", *(int *) args);
   Thread * child = calloc(1, sizeof(Thread));
   if (child == NULL) { error("Out of memory"); return NULL;}
   ucontext_t *T = &child->ctx;  
   getcontext(T);
   T->uc_link = 0;
   T->uc_stack.ss_sp= malloc(STACK_SIZE);
   T->uc_stack.ss_size=STACK_SIZE;
   T->uc_stack.ss_flags=0;
   makecontext(T, (void (*)(void))start_funct, 1, args);
   
   child->parent = running;

   insert(&ready_queue, child);
   insert(&running->childq, child);

   return (MyThread)child;  
}

void MyThreadYield(void) {
   // If ready queue is empty no change
   if (ready_queue.count == 0) {return;}
   // Insert running into ready_queue (size => 1 no issues)
   insert(&ready_queue,running);
   context_switch();
}

int MyThreadJoin(MyThread thread) {
   // if thread is NULL or thread is not in running child Q return
   Thread * child = (Thread *) thread;
   if (thread == NULL || 
   	    (has_element(&running->childq, child) == 0)) {
       return -1;
   }   
   // Indicate that running is blocked on a specific child
   running->block_on_child = child;
   // add to blocked queue
   insert(&blocked_queue, running);
   //dequeue from ready queue and put into running queue
   context_switch();
   return 0;
}


void MyThreadJoinAll(void) {

   // If child Queue is empty just return
   if (running->childq.count == 0) {
   	   return;
   }
   // Indicate that this thread is blocked on all child
   running->block_on_all = 1;
   // add to blocked queue
   insert(&blocked_queue, running);
   // if count of ready queue is 0 terminate the thread system
   context_switch();
}

void MyThreadExit(void) {
    
    Thread * parent = running->parent;
    
    if (parent != NULL) {
        remove_node(&parent->childq, running);
        if (has_element(&blocked_queue, parent)) {

            if (parent->block_on_child == running) {
        	    remove_node(&blocked_queue, parent);
        	    insert(&ready_queue, parent);
        	    parent->block_on_child = NULL;

            } else if (parent->block_on_all && 
            	        (parent->childq.count == 0)) {
                remove_node(&blocked_queue, parent);
                insert(&ready_queue, parent);
                parent->block_on_all = 0;
            }
        }
    }
    if (ready_queue.count == 0) {
        setcontext(&Main);
    } else {
      // Thread at head of ready queue becomes the running thread
      // Current thread no longer runs, no needs to save context
        Thread * T = (Thread *)dequeue(&ready_queue);
        running = T;
        setcontext(&running->ctx);
    } 
}

MySemaphore MySemaphoreInit(int initialValue) {
    if (initialValue < 0) { return NULL;}
    Semaphore * sem = calloc(1, sizeof(Semaphore));
    if (sem == NULL) { error("Out of memory"); return NULL;}
    sem->value = initialValue;
    return (MySemaphore) sem;
}

void MySemaphoreSignal(MySemaphore sem) {
    if (sem == NULL) { return; }
    Semaphore * s = (Semaphore *)sem;
    s->value++;
    if (s->semq.count <= 0) {
        Thread * t = (Thread *)dequeue(&s->semq);
        insert(&ready_queue, t);
    }
}

void MySemaphoreWait(MySemaphore sem) {
    if (sem == NULL) { return;}
    Semaphore * s = (Semaphore *)sem;
    s->value--;

    if (s->value < 0) {
        insert(&s->semq, running);
        context_switch();
    }
}

int MySemaphoreDestroy(MySemaphore sem) {
    if (sem == NULL) { return -1;}
    Semaphore * s = (Semaphore *)sem;
    if (s->semq.count > 0) { return -1;}
    free(s);
    return 0;
}

void MyThreadInit(void(*start_funct)(void *), void *args) {
   if (start_funct == NULL) { error("Invalid Params"); return;}
   //printf("%d\n", *(int *) args);
   
   ucontext_t *T;
   root = calloc(1, sizeof(Thread));
   T = &root->ctx;
   getcontext(&Main);  
   getcontext(T);
   T->uc_link = 0;
   T->uc_stack.ss_sp=malloc(STACK_SIZE);
   T->uc_stack.ss_size=STACK_SIZE;
   T->uc_stack.ss_flags=0;
   
   running = root;
   makecontext(T, (void (*)(void))start_funct, 1, args);
   swapcontext(&Main, T);
}

void context_switch () {
   
   if (ready_queue.count == 0) {
       setcontext(&Main);
   } else {
   // Thread at head of ready queue becomes the running thread
       Thread * T = (Thread *)dequeue(&ready_queue);
       Thread * tmp = running;
       running = T;
       swapcontext(&tmp->ctx, &running->ctx);
   }
}