
mythread.a : mythread.c
	gcc -c mythread.c -o mythread.o
	ar rcs mythread.a mythread.o


clean:
	-rm -f *.o
	-rm -f *.a
