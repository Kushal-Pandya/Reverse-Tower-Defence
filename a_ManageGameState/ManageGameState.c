/*ManageGameState file*/

#include "ManageGameState.h"
#include "unitInterface.h"
#include "towerInterface.h"

#define TOWER_INDEX 5
#define UNIT_INDEX 10
#define NUM_UNITS 10
#define NUM_TOWERS 5
#define NUM_PAIRS 1
#define MAX_HEALTH 10
#define MAX_SPEED 2

static void printDamage(void *** unitTowerArray, int numPairs) {

	int i;
	unit* someUnit;
    
    for(i=0;i<numPairs;i++){
        someUnit = (unit*) unitTowerArray[i][1];
        printf("Damage: %d Speed:%d \n",
           someUnit->health,
           someUnit->speed);
    }
}

int main (void) {

	int numPairs = NUM_PAIRS;
	int checkDead = 0;
	int i;
    tower T;
    unit U;
    U.health = 5;
    U.speed = 2;
    T.type = NORMAL;
    T.damage = 5;


	void*** unitTowerArray= malloc(sizeof(void*)*NUM_PAIRS);

	unitTowerArray[0] = malloc(sizeof(unit*)+sizeof(tower*));

    unitTowerArray[0][0] = &T;
    unitTowerArray[0][1] = &U;



    checkDead = ApplyUnitsDamage(unitTowerArray, numPairs);
    printDamage(unitTowerArray, numPairs);
    printf("!!!!!%d!!!!!!!!!!\n",checkDead);

    for(i=0;i<numPairs;i++){
        free(unitTowerArray[i]);
    }
    free(unitTowerArray);
}


int ApplyUnitsDamage(void*** unitTowerArray,int numPairs) {

	unit * currentUnit;
	tower * currentTower;;
	int checkDead = 0;
	int i;

	for(i=0;i<numPairs;i++){
        currentTower= (tower*) unitTowerArray[i][0];
        currentUnit=(unit*) unitTowerArray[i][1];

		
    	if (currentUnit->health > 0)
    	{
			currentUnit->health -= currentTower->damage;
    	}
		else
		{
			checkDead = 1;
		} 

		/*Checking to see if speed is already at its lowest*/
		if (currentUnit->speed != 1) {
			currentUnit->speed = currentUnit->speed-1;
		}
	}
	return checkDead;
}

void checkGameOver() {
	
}