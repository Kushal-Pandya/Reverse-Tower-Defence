#include <stdio.h>
#include <stdlib.h>
#include <curses.h>


#include "pathInterface.h"
#include "unitInterface.h"
#include "towerInterface.h"

#define MAP_X_DISPLACEMENT   50
#define MAP_Y_DISPLACEMENT   0
#define MAP_X_SIZE 30
#define MAP_Y_SIZE 14

typedef enum colour
{
    blue = 1,
    red,
    orange,
    green,
    text
}colours;
 
/*  drawMapBorder
 *
 *  Purpose:  To draw a border around the map
 */
void drawMapBorder(int mapSizeX, int mapSizeY);

/*  drawMap
 *
 *  Requires: A pointer to the path the units are following and its size (int)
 *  Purpose:  To draw the path the units will be following. 
 */
void drawMap (path * P,int size);
 
 /*  drawUnits
 *
 *  Requires: A pointer to the path the units are following (path *), its size (int),
 *            A pointer to the array of units in play (unit **) and its size (int)
 *  Purpose:  To draw the units onto the screen 
 */
void drawUnits (path *P, unit ** U, int uSize, int pSize);

/*  drawTowers
 *
 *  Requires: A pointer to the array of towers (tower **) and its size (int)
 *  Purpose:  To draw the towers onto the map. 
 */
void drawTowers (tower * towerArray, int size);
