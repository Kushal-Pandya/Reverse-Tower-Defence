#ifndef TEST_ENVIRONMENT_H
#define TEST_ENVIRONMENT_H

#include "unitInterface.h"
#include "pathInterface.h"
#include "towerInterface.h"
#include <stdlib.h>
#include <stdio.h>

/*createUnit:
This function creates a generic unit by:
    1.) taking basic information (speed,xpos and ypos)
    2.) allocating memory for the unit,
    3.) then returning the memory address of the unit with the values assigned
    **Add parameters, such as health etc, to create values for them***/
unit* createUnit(int speed,int x, int y);



/*createTower:
this function creates a generic tower with basic information.
as above, add any parameters you need to assign.*/

tower* createTower(int x,int y, int range);


/*createPath:
this function creates a path of specified length(size) 
it will turn the path once every corner
(e.g. corner = 4, path = +
                         +
                         +
                         +
                         +++++
                             +
                             +
                             +
                             +++++
*The path only brances left and down right now*/

path* createPath(int size, int corner);


/*printUnits:
used to test if units are in correct positions without drawing board
prints all values associated with units to screen in a table
assumes: unit array contains n elemtents (n =numUnits) 
and each of these elements is previously created with a create function
TLDR:units must be malloc'd already*/
void printUnits(unit** unitArray,int numUnits);


/*printTowers:
used to test if towers are in correct positions without drawing board
prints all values associated with towers to the screen
Makes same assumptions as above function*/
void printTowers(tower** towerArray,int numTowers);

/*displays the path positions in a table
same assumptions as above*/
void printPath(path* pathway,int pathSize);
#endif
