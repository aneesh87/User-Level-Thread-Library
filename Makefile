all : clean mythread.a test_fib test_merge test_1 test_2 test_join1 test_join2 test_join3 test_join4 test_passing

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

clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f test_fib test_merge test_1 test_2 test_passing test_join1 test_join2 test_join3 test_join4
