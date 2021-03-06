#include <stdio.h>
#include "mythread.h"

int resource = 2;
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
  MyThreadYield();
  printf("t2 signal\n");
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
  MyThreadYield();
  printf("t1 signal\n");
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
}
