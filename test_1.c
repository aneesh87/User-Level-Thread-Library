#include <stdio.h>
#include "mythread.h"

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
void t1(void * dummy)
{
  printf("t1 start\n");
  MyThreadExit();
  printf("t1 did not exit");
}

void t0(void * dummy)
{
  printf("t0 start\n");
  MyThreadCreate(t1, (void *)1);
  MyThreadYield();
  printf("t0 again\n");
  printf("t0 bye\n");
  MyThreadExit();
}
int main()
{
  MyThreadInit(t0, NULL);
}
