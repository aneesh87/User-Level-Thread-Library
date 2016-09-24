all : mythread.a fibtest mergetest

mythread.a : mythread.o
	ar rcs mythread.a mythread.o

mythread.o : mythread.c
	gcc -c mythread.c -o mythread.o

fibtest : fibtest.c
	gcc -o fibtest fibtest.c  mythread.a

fibtest.o : fibtest.c
	gcc -c fibtest.c -o fibtest.o

mergetest : mergetest.c
	gcc -o mergetest mergetest.c mythread.a

clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f fibtest mergetest
