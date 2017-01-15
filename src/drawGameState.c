#include "drawGameState.h"


void drawMapBorder(int mapSizeX, int mapSizeY)
{
    int drawX, drawY;
    for (int i = -1; i <= mapSizeX; i++)
    {
        for (int j = -1; j <= mapSizeY; j++)
        {
            drawX = i + MAP_X_DISPLACEMENT; 
            drawY = j + MAP_Y_DISPLACEMENT;

            
            /*Up left corner*/
            if (j == 0 && i == -1)
            {
                mvaddch(drawY,drawX,ACS_ULCORNER);
            }
            /*low left corner*/
            else if (j == mapSizeY && i == -1)
            {
                mvaddch(drawY,drawX,ACS_LLCORNER);
            }
            /*Up right corner*/
            else if (i == mapSizeX &&  j == 0)
            {
                mvaddch(drawY,drawX,ACS_URCORNER);
            }
            /*Low Right corner*/
            else if (i == mapSizeX &&  j == mapSizeY)
            {
                mvaddch(drawY,drawX,ACS_LRCORNER);
            }

            /*left/right*/
            else if (j == 0 || j == mapSizeY)
            {
                mvaddch(drawY,drawX,ACS_HLINE);
            }
            /*top/ bottom*/
            else if (i == -1 || i == mapSizeX)
            {
                mvaddch(drawY,drawX,ACS_VLINE);
            }
        }
    }
}
void drawMap (path * P,int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if ( P->isSlowed[i] == 1)
        {
            attron(COLOR_PAIR(blue));
        }

        mvprintw(P->y[i] + MAP_Y_DISPLACEMENT ,P->x[i] + MAP_X_DISPLACEMENT, "+");
        if (i == 0)
        {
            mvprintw(P->y[i] + MAP_Y_DISPLACEMENT ,P->x[i] + MAP_X_DISPLACEMENT, "B");
        }
        else if (i == size-1)
        {
            mvprintw(P->y[i] + MAP_Y_DISPLACEMENT ,P->x[i] + MAP_X_DISPLACEMENT, "E");
        } 

        attron(COLOR_PAIR(text));
    }
}

void drawUnits (path * P, unit ** U,int uSize, int pSize)
{
    int i;
    char unitSymbol;
    double percent = 0;
    int *unitOnPath;
    int drawX, drawY, validDraw;

    unitOnPath = malloc(sizeof(int)*pSize);
    for (i = 0; i < pSize; i++)
    {
        unitOnPath[i] = -1;
    }
    
    for (i = 0; i < uSize; i++)
    {
        validDraw = 1;
        mvprintw(i,0,"            ",U[i]->health);
        mvprintw(i,0,"Health: %d",U[i]->health);
        /*Can't draw is unit is not on the map*/
        /*If this is the case, their path index is negative*/
        if(U[i]->pathIndex < 0)
        {
            validDraw = 0;
            continue;
        }

        /*the location to draw each unit*/
        drawX = P->x[U[i]->pathIndex] + MAP_X_DISPLACEMENT;
        drawY = P->y[U[i]->pathIndex] + MAP_Y_DISPLACEMENT;

        /*Determine type and figure out what to print*/
        /*Calculate percent of health remaining bassed off of Max HP of that unit type*/
        if (U[i]->type == tank)
        {
            unitSymbol = 't';
            percent = (double)U[i]->health / (double) U[i]->maxHealth;
            /*Dont draw if normal is fast unit is occupying the pathIndex*/
            if (unitOnPath[U[i]->pathIndex] == normal || unitOnPath[U[i]->pathIndex] == fast)
            {
                validDraw = 0;
            }
            /* else: add unit to path*/
            else
            {
                unitOnPath[U[i]->pathIndex] = tank;   
            }
        }
        else if (U[i]->type == normal)
        {
            unitSymbol = 'n';
            percent = (double)U[i]->health / (double)U[i]->maxHealth;
            /*Dont draw if fast unit is occupying the pathIndex*/
            if (unitOnPath[U[i]->pathIndex] == fast)
            {
                validDraw = 0;
            }
            /* else: add unit to path*/
            else
            {
                unitOnPath[U[i]->pathIndex] = normal;
            }
        }
        else if (U[i]->type == fast)
        {
            unitSymbol = 'f';
            percent = (double)U[i]->health / (double)U[i]->maxHealth;
            /*Always draw, add unit onto pathIndex*/
            unitOnPath[U[i]->pathIndex] = fast;   
        }

        /*If unit is not dead, and drawing is allowed Draw it*/
        if (percent != 0.00 && validDraw)
        {
            /*Set Colour to draw based on percent*/
            /*LOW HP*/
            if (percent <= .33)
            {
                attron(COLOR_PAIR(red));
            }
            /*MEDIUM HP*/
            else if (percent > .33 && percent <=.66)
            {
                attron(COLOR_PAIR(orange));
            }
            /*GOOD HP*/
            else
            {
                attron(COLOR_PAIR(green));
            }
            /*Draw the unit on the screen based off of path index*/

            mvprintw(drawY,drawX, "%c", unitSymbol);
            attron(COLOR_PAIR(text));
        }
    } 
    free(unitOnPath);  
}

void drawTowers(tower * towerArray, int size)
{

    int i = 0;
    int tempX = 0;
    int tempY = 0;
    

    for(i = 0;i < size; i++) 
    {
        tempX = towerArray[i].x + MAP_X_DISPLACEMENT;
        tempY = towerArray[i].y + MAP_Y_DISPLACEMENT;
        
        /*Draw towers based on type*/
        if (towerArray[i].type == NORMAL)
        {
            mvprintw(tempY,tempX,"N");    
        }
        else if (towerArray[i].type == MISSILE)
        {
            mvprintw(tempY,tempX,"M");
        }
        else if (towerArray[i].type == ARCHER)
        {
            mvprintw(tempY,tempX,"A");
        }
        else if (towerArray[i].type == SLOW)
        {
            mvprintw(tempY,tempX,"S");
        }
    }
}
