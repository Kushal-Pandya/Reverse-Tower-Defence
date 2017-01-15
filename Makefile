CC = gcc -Wall -pedantic -std=gnu99 -Iinclude 


main: loadLevel.o userInterface.o drawGameState.o manageMapState.o manageGameState.o
	$(CC) src/main.c loadLevel.o userInterface.o drawGameState.o manageMapState.o manageGameState.o -o bin/runme -lncurses -lm
	
loadLevel.o: src/loadLevel.c
	$(CC) -c src/loadLevel.c -lncurses -lm

userInterface.o: src/userInterface.c
	$(CC) -c src/userInterface.c -lncurses

drawGameState.o: src/drawGameState.c
	$(CC) -c src/drawGameState.c -lncurses

manageMapState.o: src/manageMapState.c
	$(CC) -c src/manageMapState.c -lm

manageGameState.o: src/manageGameState.c
	$(CC) -c src/manageGameState.c

clean:
	rm *.o bin/runme	
