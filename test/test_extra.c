#include <stdio.h>
#include "mythreadextra.h"

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
  MyThreadYield();
  printf("t1 again\n");
  MyThreadExit();
  printf("t1 did not exit");
}

void t2(void * dummy)
{
  printf("t2 start\n");
  MyThreadYield();
  printf("t2 again\n");
  MyThreadExit();
}
int main()
{
  MyThreadInitExtra();
  printf("Main start\n");
  MyThreadCreate(t1, (void *)1);
  MyThreadCreate(t2, (void *)1);
  MyThreadYield();
  printf("Main again and exiting\n");
  MyThreadExit();
}
