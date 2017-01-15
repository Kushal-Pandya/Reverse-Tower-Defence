#ifndef manageMapState_H
#define manageMapState_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "towerInterface.h"
#include "pathInterface.h"
#include "unitInterface.h"

//Returns 1 if a unit entered the map, 0 mean no more units are entering the map
int updateUnitPositions(unit** units,path* pathway, int numUnits, int pathSize, int *enemyHealth);

//Returns the number of unit tower pairs in the array
int updateUnitsWithinRange(void*** unitTowerArray,unit** unitArray,
    tower* towerArray,int numUnits,int numTowers);

//updates unit positions, checks if units are in range of towers,
//calls manageGameState with an array of unit and tower pairs
void *** manageMapState(unit** unitArray,tower* towerArray,path* pathway,
    int numUnits, int numTowers, int pathSize, int *numPairs, int *enemyHealth);

void freeTowerUnitArray(void*** unitTowerArray, int *numPairs);


#endif
