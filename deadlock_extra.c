#include <stdio.h>
#include "mythreadextra.h"

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
  MySemaphoreWait(t);
  printf("t2 access critical section t\n");
  MyThreadYield();
  MySemaphoreWait(s);
  printf("t2 done critical section s\n");
  
  printf("t2 signal\n");
  MySemaphoreSignal(s);
  printf("t1 signal t\n");
  MySemaphoreSignal(t);
  
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

int main()
{
   s = MySemaphoreInit(resource);
   t = MySemaphoreInit(resource);
   MyThreadInitExtra();
   printf("Root thread start\n");
   MyThreadCreate(t1, (void *)1);
   MyThreadCreate(t2, (void *)1);  
   MyThreadYield();
   printf("Root thread exit\n");
   MyThreadExit();
}
