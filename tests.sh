#!/bin/bash
make

echo "\n./test_1 - Output should be :"
cat << EOF
t0 start
t1 start
t0 again
t0 bye
Output is:
EOF
./test_1

echo "\n./test_2 - Output should be :"
cat << EOF
t0 start
t1 start
t2 start
t0 again
t1 again
t2 again
t0 bye
Output is:
EOF
./test_2 

echo "\n./test_fib 8 - Output should be :"
cat << EOF
fib(8) = 21
Output is:
EOF
./test_fib 8

echo "\n./test_join1 - Output should be :"
cat << EOF
t0 start
t0 going to join
t1 start
t1 going to yield
t1 again
t1 exiting
t0 again
Output is:
EOF
./test_join1

echo "\n./test_join2 - Output should be :"
cat << EOF
t0
t1
t2
t2 again
t0 bye
Output is:
EOF
./test_join2

echo "\n./test_join3 - Output should be :"
cat << EOF
t0
t1
t2
t1 again
t2 again
t0 bye
Output is:
EOF
./test_join3

echo "\n./test_join4 - Output should be :"
cat << EOF
t0
t1
t2
t1 again
t2 again
t1
t1
t1 again
t1 again
t2 bye
t0 bye
Output is:
EOF
./test_join4

echo "\n./test_merge 15 - Output should be :"
cat << EOF
0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
Output is:
EOF
./test_merge 15

echo "\n./test_passing 5 1 - Output should be :"
cat << EOF
t0 start 5
t0 create 4 
t0 start 4
t0 create 3 
t0 end 5
t0 start 3
t0 create 2 
t0 end 4
t0 start 2
t0 create 1 
t0 end 3
t0 start 1
t0 create 0 
t0 end 2
t0 start 0
t0 end 0
t0 end 1
Output is:
EOF
./test_passing 5 1

echo "\n./test_passing 5 2 - Output should be :"
cat << EOF
t0 start 5
t0 create 4 
t0 start 4
t0 create 3 
t0 start 3
t0 create 2 
t0 start 2
t0 create 1 
t0 start 1
t0 create 0 
t0 start 0
t0 end 0
t0 end 1
t0 end 2
t0 end 3
t0 end 4
t0 end 5
Output is:
EOF
./test_passing 5 2

echo "\n./test_sem1 - Output should be :"
cat << EOF
Root thread start
t1 start
t1 access critical section
t1 done critical section
t2 start
t2 access critical section
t2 done critical section
t3 start
t3 access critical section
t3 done critical section
t4 start
t4 access critical section
t4 done critical section
t5 start
t5 access critical section
t5 done critical section
t6 start
t6 access critical section
t6 done critical section
t7 start
t7 access critical section
t7 done critical section
Root thread exit
Semaphore destroyed successfullly
Output is:
EOF
./test_sem1

echo "\n./test_sem2 - Output should be :"
cat << EOF
Root thread start
t1 start
t2 start
t2 signal
Root thread exit
t1 access critical section
t1 done critical section
Output is:
EOF
./test_sem2

echo "\n./test_sem3 - Output should be :"
cat << EOF
Root thread start
t1 start
t1 access critical section
t1 done critical section
t2 start
t2 access critical section
t2 done critical section
t3 start
Root thread exit
t1 signal
t2 signal
t3 access critical section
t3 done critical section
Output is:
EOF
./test_sem3

echo "\n./test_2sem - Output should be :"
cat << EOF
Output is:
Root thread start
t1 start
t1 access critical section s
t2 start
Root thread exit
t1 done critical section  t
t1 signal t
t1 signal s
t2 access critical section s
t2 done critical section t
t2 signal
t1 signal t
Semaphore s destroyed successfullly
Semaphore t destroyed successfullly
Output is:
EOF
./test_2sem

echo "\n./deadlock - Output should be :"
cat << EOF
Root thread start
t1 start
t1 access critical section s
t2 start
t2 access critical section t
Root thread exit
Sem queue not empty unable to destroy semaphore s
Sem queue not empty unable to destroy semaphore t
Output is:
EOF
./deadlock

echo "\n./deadlock_extra - Output should be :"
cat << EOF
Root thread start
t1 start
t1 access critical section s
t2 start
t2 access critical section t
Root thread exit
Output is:
EOF
./deadlock_extra

echo "\n./test_extra - Output should be :"
cat << EOF
Main start
t1 start
t2 start
Main again and exiting
t1 again
t2 again
Output is:
EOF
./test_extra




