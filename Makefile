all : clean mythread.a test_fib test_merge test_1 test_2 test_join1 test_join2 test_join3 test_join4 test_passing test_sem1 test_sem2 test_sem3 deadlock test_2sem deadlock_extra test_extra

mythread.a : mythread.o
	ar rcs mythread.a mythread.o

mythread.o : mythread.c
	gcc -c mythread.c -o mythread.o

test_fib : test_fib.c
	gcc -o test_fib test_fib.c mythread.a

test_merge : test_merge.c
	gcc -o test_merge test_merge.c mythread.a

test_1 : test_1.c
	gcc -o test_1 test_1.c mythread.a

test_2 : test_2.c
	gcc -o test_2 test_2.c mythread.a

test_passing : test_passing.c
	gcc -o test_passing test_passing.c mythread.a

test_join1 : test_join1.c
	gcc -o test_join1 test_join1.c mythread.a

test_join2 : test_join2.c
	gcc -o test_join2 test_join2.c mythread.a

test_join3 : test_join3.c
	gcc -o test_join3 test_join3.c mythread.a

test_join4 : test_join4.c
	gcc -o test_join4 test_join4.c mythread.a

test_sem1 : test_sem1.c
	gcc -o test_sem1 test_sem1.c mythread.a

test_sem2 : test_sem2.c
	gcc -o test_sem2 test_sem2.c mythread.a

test_sem3 : test_sem3.c
	gcc -o test_sem3 test_sem3.c mythread.a

deadlock : deadlock.c
	gcc -o deadlock deadlock.c mythread.a

test_2sem : test_2sem.c
	gcc -o test_2sem test_2sem.c mythread.a

deadlock_extra : deadlock_extra.c
	gcc -o deadlock_extra deadlock_extra.c mythread.a

test_extra : test_extra.c
	gcc -o test_extra test_extra.c mythread.a

clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f test_fib test_merge test_1 test_2 test_passing test_join1 test_join2 test_join3 test_join4 test_sem1 test_sem2 test_sem3 deadlock test_2sem deadlock_extra test_extra
