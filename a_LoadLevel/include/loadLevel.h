#ifndef _DEF_LOADLEVEL_H
#define _DEF_LOADLEVEL_H

#include <towerInterface.h>
#include <pathInterface.h>

/*
 * Asks the user to select a level. Reads and parses the level file,
 * initializes the path and towers.
 * Returns the towers array or NULL if there was any problem loading the file.
 */
tower * loadLevel (int * pathLength, path * thePath, int * nTowers, int *currency);

#endif
