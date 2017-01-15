/*ManageGameState file*/

#include "manageGameState.h"


void applyUnitsDamage(void*** unitTowerArray,int numPairs,unit** unitArray,int numUnits) {

	unit * currentUnit;
	tower * currentTower;;
	int i,row,col,k;

    int x,y;
	for(i=0;i<numPairs;i++){
        currentTower= (tower*) unitTowerArray[i][0];
        currentUnit=(unit*) unitTowerArray[i][1];

	    if(currentTower->type == MISSILE){
            x=currentUnit->x-1;
            y=currentUnit->y-1;
            for(row=x;row<x+3;row++){
                for(col = y; col<y+3; col++){
                    for(k=0;k<numUnits;k++){
                        if(unitArray[k]->x == row && unitArray[k]->y == col){
                            unitArray[k]->health-= currentTower->damage;
                        }
                    }
                }
            }
        }
        else
        {
           currentUnit->health -= currentTower->damage;
        }
        if(currentUnit->health<0){
                currentUnit->health = 0;
        }

    	if (currentUnit->health == 0)
    	{
			currentUnit->pathIndex = -3;
    	}

		/*Checking to see if speed is already at its lowest*/
		/*if (currentUnit->speed != 1) {
			currentUnit->speed = currentUnit->speed-1;
		}*/

	}
}

int checkGameOver(int enemyHealth, unit **U, int nUnits)
{
	int unitsLeft = 0;
    int healthLeft = 1;
    if (enemyHealth <= 0)
    {
        healthLeft = 0;
    }
    for (int i = 0; i < nUnits; i++)
    {
    	/*if units are not on the */
    	if (U[i]->pathIndex >= 0)
    	{
            unitsLeft = 1;
    	}
    }
    
    /*if the enemy has no hp, you win*/
    if (!healthLeft)
    {
    	/*return win*/
    	return (2);
    }
    /*if they have units, keep playing*/
    else if (unitsLeft)
    {
    	return(0);
    }
    /*no units left, you lose*/
    else
    {
    	/*return loss*/
        return(1);
    }
}
