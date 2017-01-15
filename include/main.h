#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>

#include "pathInterface.h"
#include "towerInterface.h"
#include "unitInterface.h"

#include "loadLevel.h"
#include "userInterface.h"
#include "drawGameState.h"
#include "manageMapState.h"
#include "manageGameState.h"

void freeUnits (unit **U, int *nUnits);
void freeTowers (tower *T, int *nTowers);
void clearLevel(unit **U, int *nUnits, tower *T,int *nTowers, path* thePath, int *pathLength, int *enemyHealth);
void clearPath(path *P, int *pathLength);



