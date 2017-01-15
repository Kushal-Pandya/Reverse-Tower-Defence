#include "testEnvironment.h"

/*the create functions only ask for what i needed for my testing when making
manage map state. feel free to add parameters to modify relevant values for
your own testing*/

unit* createUnit(int speed, int x, int y){
    unit* someUnit = malloc(sizeof(unit));
    someUnit->type=1;
    someUnit->health = 100;
    someUnit->maxHealth = 100;
    someUnit->speed = speed;
    someUnit->x = x;
    someUnit->y = y;
    someUnit->pathIndex = 0;

    return someUnit;
}

tower* createTower(int x,int y,int range){
    tower* someTower = malloc(sizeof(tower));
    someTower->type =1;
    someTower->x = x;
    someTower->y = y;
    someTower->fireRate = 1;
    someTower->counter =1;
    someTower->damage = 10;
    someTower->range = range;
    
    return someTower;
}

path* createPath(int size,int corner){
    int i,lastY,lastX;
    
    path * pathway = malloc(sizeof(path));

    for(i=0,lastY=3,lastX=3; i<size;i++){
       //half the time, go down, half the time go right (cycle)
       if(i%(corner * 2) < corner){
            pathway->x[i] = lastX;
            pathway->y[i] = lastY + 1;
        }
        else
        {
            pathway->x[i] = lastX + 1;
            pathway->y[i] = lastY;
        }
        
        lastY = pathway->y[i];
        lastX = pathway->x[i];
    }
    return pathway;
}

void printUnits(unit** unitArray,int numUnits){
    int i;
    
    printf("There are %d units, as follows:\n",numUnits);
    printf("#\ttype\thealth\tspeed\tx\ty\tpathIndex\n");
    for(i =0;i<numUnits;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
              i,
              unitArray[i]->type,
              unitArray[i]->health,
              unitArray[i]->speed,
              unitArray[i]->x,
              unitArray[i]->y,
              unitArray[i]->pathIndex);
    }
}

void printTowers(tower** towerArray,int numTowers){
    int i;
    printf("There are %d towers, as follows:\n",numTowers);
    printf("#\ttype\tx\ty\tfRate\tcounter\tdamage\trange\n");
    for(i =0;i<numTowers;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
              i,
              towerArray[i]->type,
              towerArray[i]->x,
              towerArray[i]->y,
              towerArray[i]->fireRate,
              towerArray[i]->counter,
              towerArray[i]->damage,
              towerArray[i]->range);
    }
}

void printPath(path* pathway,int pathSize){
    int i;
    printf("The path is of size: %d, and is located as follows\n",pathSize);
    printf("Index\tx\ty\n");
    for(i=0;i<pathSize;i++){
        printf("%d\t%d\t%d\n",i,pathway->x[i],pathway->y[i]);
    }
}
