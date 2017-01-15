#ifndef _DEF_LOADLEVEL_H
#define _DEF_LOADLEVEL_H

#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "towerInterface.h"
#include "pathInterface.h"

/*
 * Asks the user to select a level. Reads and parses the level file,
 * initializes the path and towers.
 * Returns the towers array or NULL if there was any problem loading the file.
 */
tower * loadLevel (int levelID, int * pathLength, path * thePath, int * nTowers, int *currency, int *width, int *height);

/* readLevelFile
 * 
 * Requires: The level number (int), an empty variable to store
 * 
 * Purpose: Opens and reads the file corresponding to 
 * 
*/
char **readLevelFile(int levelID, int *width, int *height, int *nTowers, int *currency);

tower *initializeTowers(char **levelString, int width, int height, int *nTowers, int *pathLength, int *startX, int *startY);

int buildMap(char **levelString, int width, int height, int pathLength, path *thePath, int startX, int startY);

#endif
