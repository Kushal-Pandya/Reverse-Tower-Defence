#include "interfaceManageMapState.h"
#include "testEnvironment.h"
#include <math.h>
#define NUM_UNITS 10
#define NUM_TOWERS 2
#define PATH_SIZE 10
#define CORNER 4 //# of spaces before a corner
    
static int inRange(unit* someUnit,tower* someTower){
    double distance,xDisp,yDisp;
    xDisp = someTower->x - someUnit->x;
    yDisp = someTower->y - someUnit->y;
    distance = sqrt((xDisp * xDisp) + (yDisp * yDisp));

    if(distance <= someTower->range){
        return 1;
    }else{
        return 0;
    }

}

static void printUnitTowerArray(void*** unitTowerArray,int numPairs){
    int i;
    tower* someTower;
    unit* someUnit;
    
    for(i=0;i<numPairs;i++){
        someTower= (tower*) unitTowerArray[i][0];
        someUnit=(unit*) unitTowerArray[i][1];
        printf("tower at x: %d y:%d fired at unit at pathIndex %d \n",
           someTower->x,
           someTower->y,
           someUnit->pathIndex);
    }
}

int main(void){
    
    int corner = CORNER;
    int pathSize = PATH_SIZE;
    int numUnits = NUM_UNITS;
    int numTowers = NUM_TOWERS;
    unit ** unitArray = malloc(sizeof(unit*)*NUM_UNITS);
    tower ** towerArray = malloc(sizeof(tower*)*NUM_TOWERS);
    path * pathway = createPath(pathSize,corner);
    int next =0;
    int i,j,posX,posY;
    //memory for each unit in the array
    for(i=0;i<numUnits;i++){
        //speed,x,y,pathIndex
        if(i%4){
            unitArray[i] = createUnit(2,8,11,-1);
        }
        else
        {
            unitArray[i] = createUnit(1,8,11,-1);
        }
    }
    //place towers near corners
    for(i=0;i<numTowers;i++){
        for(j =next; j<pathSize-1; j++){
                
            if(pathway->y[j] != pathway->y[j+1])
            {
                posX =pathway->x[j] - 2;
                posY =pathway->y[j] + 2;
                towerArray[i] = createTower(posX,posY,3);
                next = j+corner; //place a tower 2 away from each corner
                j = pathSize;
            }
        }
    }
    
    manageMapState(unitArray,towerArray,pathway,numUnits,numTowers,pathSize);
    
    for(i=0;i<numUnits;i++){
        free(unitArray[i]);
    }
    
    for(i=0;i<numTowers;i++){
        free(towerArray[i]);
    }

    free(unitArray);
    free(towerArray);
    free(pathway);
    return 0;
}

int updateUnitPositions(unit** units, path* pathway,int numUnits, int pathSize){
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
            units[i]->pathIndex += units[i]->speed;
            if(units[i]->pathIndex >= pathSize){
                units[i]->pathIndex = -2;
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
    tower** towerArray,int numUnits, int numTowers){

    void** unitTowerPair;
    int i,j,highestIndex;
    int numPairs =0;
    int pairCreated=0;

    for( i=0;i<numTowers;i++){
        highestIndex = 0;
        pairCreated=0;
        for(j=0;j<numUnits;j++){
            if(inRange(unitArray[j],towerArray[i])){
                if(unitArray[j]->pathIndex > highestIndex){
                    if(!pairCreated){
                        unitTowerPair = malloc(sizeof(unit*)+sizeof(tower*));
                    }
                    unitTowerPair[0]=towerArray[i];
                    unitTowerPair[1]=unitArray[j];
                    highestIndex=unitArray[j]->pathIndex;
                    unitTowerArray[numPairs]=unitTowerPair;
                    pairCreated = 1;
                }
            }
        }
        if(pairCreated){
             numPairs++;
        }
                
    }

    return numPairs;
}


void manageMapState(unit** unitArray, tower** towerArray, path* pathway,
    int numUnits, int numTowers, int pathSize){
    
    void*** unitTowerArray= malloc(sizeof(void*)*NUM_TOWERS);
    int numPairs =0;
   
    printUnits(unitArray,numUnits);
    printTowers(towerArray,numTowers);
    printPath(pathway,pathSize);
    
    
    while(updateUnitPositions(unitArray,pathway,numUnits, pathSize)){
        
        printUnits(unitArray,numUnits);

        numPairs=  updateUnitsWithinRange(unitTowerArray,unitArray,towerArray,
            numUnits, numTowers);
            
        printUnitTowerArray(unitTowerArray,numPairs);
    }
      
    printUnits(unitArray,numUnits);
        numPairs=  updateUnitsWithinRange(unitTowerArray,unitArray,towerArray,
            numUnits, numTowers);
    printUnitTowerArray(unitTowerArray,numPairs);

}

















