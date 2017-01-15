#include <stdio.h>
#include <stdlib.h>

#include "unitInterface.h"
#include "towerInterface.h"



/*This function takes in the unit/tower array and calculates and applies
the damage to the units accordingly*/
void applyUnitsDamage(void *** unitTowerArray, int numPairs,unit** unitsArray,int numUnits);

int checkGameOver(int enemyHealth, unit **U, int nUnits);
