#include <stdio.h>
#include "mythread.h"

int resource = 4;
MySemaphore * s;
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


void t7(void * dummy)
{
  printf("t7 start\n");
  MySemaphoreWait(s);
  printf("t7 access critical section\n");
  printf("t7 done critical section\n");
  MySemaphoreSignal(s);
  MyThreadExit();
  printf("t7 did not exit");
}

void t6(void * dummy)
{
  printf("t6 start\n");
  MySemaphoreWait(s);
  printf("t6 access critical section\n");
  printf("t6 done critical section\n");
  MySemaphoreSignal(s);
  MyThreadExit();
  printf("t6 did not exit");
}

void t5(void * dummy)
{
  printf("t5 start\n");
  MySemaphoreWait(s);
  printf("t5 access critical section\n");
  printf("t5 done critical section\n");
  MySemaphoreSignal(s);
  MyThreadExit();
  printf("t5 did not exit");
}

void t4(void * dummy)
{
  printf("t4 start\n");
  MySemaphoreWait(s);
  printf("t4 access critical section\n");
  printf("t4 done critical section\n");
  MySemaphoreSignal(s);
  MyThreadExit();
  printf("t4 did not exit");
}

void t3(void * dummy)
{
  printf("t3 start\n");
  MySemaphoreWait(s);
  printf("t3 access critical section\n");
  printf("t3 done critical section\n");
  MySemaphoreSignal(s);
  MyThreadExit();
  printf("t3 did not exit");
}
void t2(void * dummy)
{
  printf("t2 start\n");
  MySemaphoreWait(s);
  printf("t2 access critical section\n");
  printf("t2 done critical section\n");
  MySemaphoreSignal(s);
  MyThreadExit();
  printf("t2 did not exit");
}

void t1(void * dummy)
{
  printf("t1 start\n");
  MySemaphoreWait(s);
  printf("t1 access critical section\n");
  printf("t1 done critical section\n");
  MySemaphoreSignal(s);
  MyThreadExit();
  printf("t1 did not exit");
}

void t0(void * dummy)
{
  printf("Root thread start\n");
  MyThreadCreate(t1, (void *)1);
  MyThreadCreate(t2, (void *)1);
  MyThreadCreate(t3, (void *)1);
  MyThreadCreate(t4, (void *)1);
  MyThreadCreate(t5, (void *)1);
  MyThreadCreate(t6, (void *)1);
  MyThreadCreate(t7, (void *)1);
  
  MyThreadYield();
  printf("Root thread exit\n");
  /*int t  = MySemaphoreDestroy(s);
  if (t == 0) {
    printf("%s\n", "Semaphore destroyed successfullly" );
  }*/
  MyThreadExit();
}
int main()
{
   s = MySemaphoreInit(resource);
   MyThreadInit(t0, NULL);
   int i  = MySemaphoreDestroy(s);
   if (i == 0) {
      printf("%s\n", "Semaphore destroyed successfullly" );
   } else {
      printf("Unable to destroy semaphore");
   }
}
