#ifndef _USERINTERFACE_H_
#define _USERINTERFACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "unitInterface.h"

#define UI_WIDTH 38
#define UI_LENGTH 27


/*Function: createInterface
 *Takes in a x and y value for positioning reference
 *This function draws to the screen the menu and interface of the user
 */
void createInterface(int xPos, int yPos);

/* Function: manageUserInput
 *  Takes in x and y value for positioning reference
 *  Move up with the "w" key, down with the "s" key, and select with the "z" key
 */
unit ** manageUserInput(int xPos, int yPos, int *sizePointer, int *costPointer);

/*Function: createUnits
 *Is passed the unit array, the selected unit, the amount of points the user has, and the array size
 */
void createUnits(unit ** unitArray, char selectionChar, int * costPointer, int * sizePointer);

/*  getUnitType
 *
 *  Requires: A pointer to a unit.
 *  Purpose:  To determine the unit's type and return it as a character. 
 */
char getTypeChar(uTypes type);

#endif
