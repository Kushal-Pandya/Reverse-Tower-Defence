all: manage

manage: ManageGameState.o 

	gcc ManageGameState.o -lm

manageGameState.o: ManageGameState.c

	gcc -std=c99 -pedantic ManageGameState.c -lm -c -o ManageGameState.o

clean:
	rm -f *.o
	rm a.out
run:
	./a.out
