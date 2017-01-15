#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include "pathInterface.h"
#include "testEnvironment.h"
#include "DrawGameState.h"

typedef enum uTypes
{
  normal,
  fast,
  tank

}uTypes;
typedef enum hi
{
    text = 1,
    red,
    orange,
    green,
    blue
}hi;

int main (void)
{

    
    char uInput= ' ';
    path *P;
    unit ** U;
    int i;
    int tSize = 3;
    int uSize = 20;
    int pSize = 20;

    U = malloc(sizeof(unit*) * uSize);
    P = createPath(pSize, 3);

    /*Create  units for testing*/
    for (i = 0; i < 10; i++)
    {
        U[i] = createUnit(0,P->x[i],P->y[i]);
        U[i]->health = U[i]->health - (i * 10);
        U[i]->pathIndex = i;

        U[i]->type = i%3;
    }
    for (i = 10; i < 20; i++)
    {
        U[i] = createUnit(0,P->x[i],P->y[i]);
        U[i]->health = U[i]->health - (i * 10);
        U[i]->pathIndex = 20-i;

        U[i]->type = tank;
    }


    tower ** towerArray = malloc(sizeof(tower)*3);

    towerArray[0]=malloc(sizeof(tower));
    towerArray[0]->x = 2;
    towerArray[0]->y = 0;
    towerArray[1]=malloc(sizeof(tower));
    towerArray[1]->x = 3;
    towerArray[1]->y = 0;
    towerArray[2]=malloc(sizeof(tower));
    towerArray[2]->x = 5;
    towerArray[2]->y = 0;

    towerArray[0]->type = 0;
    towerArray[1]->type = 1;
    towerArray[2]->type = 2;
    




    getch();
    initscr();
    start_color();

    init_pair(text, 7,0);
    init_pair(blue, 4,0);
    init_pair(red, 1,0);
    init_pair(orange, 3,0);
    init_pair(green, 2,0);

    while (uInput != 'q')
    {
        drawMap(P,pSize);
        drawUnits(P,U,uSize,pSize);
        drawTowers(towerArray, tSize);
        refresh();
        uInput = getch();
    }
    endwin();
    
 
    free(P);
    for (i = 0; i < uSize; i++)
    {
        free(U[i]);
    }

    free(U);
    for (i = 0; i < tSize; i++)
    {
        free(towerArray[i]);
    }
    free(towerArray);
    return(0);
}