#include <stdio.h>
#include "mythread.h"

int resource = 1;
MySemaphore * s;
MySemaphore * t;

/*
Output:
	t0 start
	t1 start
	t2 start
	t0 again
	t1 again
	t2 again
	t0 bye
*/

void t2(void * dummy)
{
  printf("t2 start\n");
  MySemaphoreWait(s);
  printf("t2 access critical section s\n");
  MyThreadYield();
  MySemaphoreWait(t);
  printf("t2 done critical section t\n");
  
  printf("t2 signal\n");
  MySemaphoreSignal(t);
  printf("t1 signal t\n");
  MySemaphoreSignal(s);
  
  MyThreadExit();
  printf("t2 did not exit");
}

void t1(void * dummy)
{
  printf("t1 start\n");
  MySemaphoreWait(s);
  printf("t1 access critical section s\n");
  MyThreadYield();
  MySemaphoreWait(t);
  printf("t1 done critical section  t\n");
  
  printf("t1 signal t\n");
  MySemaphoreSignal(t);
  printf("t1 signal s\n");
  MySemaphoreSignal(s);
  
  MyThreadExit();
  printf("t1 did not exit");
}

void t0(void * dummy)
{
  printf("Root thread start\n");
  MyThreadCreate(t1, (void *)1);
  MyThreadCreate(t2, (void *)1);  
  MyThreadYield();
  printf("Root thread exit\n");
  MyThreadExit();
}
int main()
{
   s = MySemaphoreInit(resource);
   t = MySemaphoreInit(resource);
   MyThreadInit(t0, NULL);
   
   int i = MySemaphoreDestroy(s);
   if (i == 0) {
       printf("%s\n", "Semaphore s destroyed successfullly" );
   } else {
       printf("%s\n", "Sem queue not empty unable to destroy semaphore s" );
   }
  
   int j = MySemaphoreDestroy(t);
   if (j == 0) {
       printf("%s\n", "Semaphore t destroyed successfullly" );
   } else {
       printf("%s\n", "Sem queue not empty unable to destroy semaphore t" );
   }
}
