all: manage

manage: manageMapState.o testEnvironment.o 

	gcc manageMapState.o testEnvironment.o -lm
testEnvironment.o: testEnvironment.c

	gcc -std=c99 -Wall -pedantic testEnvironment.c -c -o testEnvironment.o

manageMapState.o: manageMapState.c

	gcc -std=c99 -Wall -pedantic manageMapState.c -lm -c -o manageMapState.o

clean:
	rm -f *.o
	rm a.out
run:
	./a.out
