#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

/*This function no longer exists in ManageGameState as it is already
	in ManageMapState*/ 
//void FireTowerAttacks(tower ** towerArray);

/*This function takes in the unit/tower array and calculates and applies
the damage to the units accordingly*/
int ApplyUnitsDamage(void *** unitTowerArray, int numPairs);

void checkGameOver();