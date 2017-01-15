#include "manageMapState.h"

static int inRange(unit* someUnit,tower someTower){
    double distance,xDisp,yDisp;
    xDisp = someTower.x - someUnit->x;
    yDisp = someTower.y - someUnit->y;
    distance = sqrt((xDisp * xDisp) + (yDisp * yDisp));

    if(distance <= someTower.range){
        return 1;
    }else{
        return 0;
    }
}

int updateUnitPositions(unit** units, path* pathway,int numUnits, int pathSize, int *enemyHealth){
    int i;
    int unitEnteredMap = 0;
    for(i=0;i<numUnits;i++){
        if(units[i]->pathIndex == -1)
        {
            unitEnteredMap = 1;
            units[i]->pathIndex = 0;
            units[i]->x= pathway->x[0];
            units[i]->y= pathway->y[0];
            i = numUnits;
        }else if(units[i]->pathIndex >= 0 && units[i]->pathIndex <pathSize){
            /*Move units (implements slow tower)*/
            for (int j = 0; j < units[i]->speed; j++)
            {
                units[i]->pathIndex += 1;
                if (pathway->isSlowed[units[i]->pathIndex] == 1)
                {
                    j++;
                }
            }
            /*if unit makes it to end of path, subtract health form enemy*/
            if(units[i]->pathIndex >= pathSize){
                units[i]->pathIndex = -2;
               
		if(units[i]->type == normal)
		{
		    *enemyHealth -= NORMAL_DMG;
		}
		else if(units[i]->type == fast)
		{
	           *enemyHealth -=FAST_DMG;
		}
		else if(units[i]->type == tank)
                {
		   *enemyHealth -=TANK_DMG;
                }
            }else{
                units[i]->x = pathway->x[units[i]->pathIndex];
                units[i]->y = pathway->y[units[i]->pathIndex];
            }
        }else if(units[i]->pathIndex >= pathSize){
            units[i]->pathIndex = -2;
        }
    }


    return unitEnteredMap;
}

int  updateUnitsWithinRange(void*** unitTowerArray,unit** unitArray, 
    tower* towerArray,int numUnits, int numTowers){

    void** unitTowerPair;
    int i,j,highestIndex;
    int numPairs =0;
    int pairCreated=0;

    for( i=0;i<numTowers;i++){
        highestIndex = 0;
        pairCreated=0;
        if(towerArray[i].counter == towerArray[i].fireRate){
            towerArray[i].counter = 1;    

            for(j=0;j<numUnits;j++){
                if(inRange(unitArray[j],towerArray[i])){
                    if(unitArray[j]->pathIndex > highestIndex){
                        if(!pairCreated){
                            unitTowerPair = malloc(sizeof(unit*)+sizeof(tower*));
                        }
                        /*NOTE: CHANGED TOWER ** to TOWER *
                         * ADDED '&' on line 65 to continue setting
                         * unitTowerPair to a Tower * 
                         */
                        unitTowerPair[0]=&towerArray[i];
                        unitTowerPair[1]=unitArray[j];
                        highestIndex=unitArray[j]->pathIndex;
                        unitTowerArray[numPairs]=unitTowerPair;
                        pairCreated = 1;
                    }
                }
            }
        }else{
            towerArray[i].counter++;
        }

        
        if(pairCreated){
             numPairs++;
        }            
    }
    return numPairs;
}


void *** manageMapState(unit** unitArray, tower* towerArray, path* pathway,
    int numUnits, int numTowers, int pathSize, int *numPairs, int *enemyHealth){
    
    void*** unitTowerArray= malloc(sizeof(void*)*numTowers);
    *numPairs = 0;
    
    
    updateUnitPositions(unitArray,pathway,numUnits,pathSize,enemyHealth);
        
    *numPairs =  updateUnitsWithinRange(unitTowerArray,unitArray,towerArray,numUnits, numTowers);
    return(unitTowerArray);        
}
void freeTowerUnitArray(void*** unitTowerArray, int *numPairs)
{
    for(int i = 0; i < *numPairs; i++)
    {
        free(unitTowerArray[i]);
        unitTowerArray[i] = NULL;
    }
    free(unitTowerArray);
    unitTowerArray = NULL;
    *numPairs = 0;

}

















