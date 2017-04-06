CC=g++
CFLAGS= -g -Wall
KnightsTour:Node.o Stack.o main.o
	$(CC) $(CFLAGS) Node.o Stack.o main.o -o KnightsTour
Node.o:Node.cpp Node.h
	$(CC) $(CFLAGS) -c Node.cpp
Stack.o:Stack.cpp Stack.h
	$(CC) $(CFLAGS) -c Stack.cpp
main.o:main.cpp Stack.h Node.h
	$(CC) $(CFLAGS) -c main.cpp
clean:
	rm *.o KnightsTour  output.text 

run: KnightsTour
	./KnightsTour

memTest: KnightsTour
	valgrind --leak-check=full ./KnightsTour
