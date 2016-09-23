#include "mythread.h"

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
