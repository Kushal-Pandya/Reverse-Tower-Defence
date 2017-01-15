//Made by Scott Collier
//CIS 3250
//Reverse Tower Defence: User Interface

#include "userInterface.h"

static void legend(){



/*This part of draws a legend below the map */
    int legx, legy;
    legx = 3;
    legy = 35;



    mvprintw(legy+1,legx+17, "Legend");
    mvprintw(legy+2,legx+1, "Menu Controls: ");
    mvprintw(legy+3,legx+1, "\tw: move up");
    mvprintw(legy+4,legx+1, "\ts: move down");
    mvprintw(legy+5,legx+1, "\tz: select");
    mvprintw(legy+6,legx+1, "Map: ");
    mvprintw(legy+7,legx+1, "\t+: Path             n: Normal Unit");
    mvprintw(legy+8,legx+1, "\tB: Path Begins      f: fast Unit");
    mvprintw(legy+9,legx+1, "\tE: Path Ends        t: Tank Unit");
    mvprintw(legy+10,legx+1, "\tN: Normal Tower");
    mvprintw(legy+11,legx+1, "\tS: Slow Tower");
    mvprintw(legy+12,legx+1, "\tM: Missile Tower");
    mvprintw(legy+13,legx+1, "\tA: Archer Tower");
    mvprintw(legy+14,legx+1, "\t");
    mvprintw(legy+15,legx+1, "Instructions : ");
    mvprintw(legy+16,legx+1, "   Welcome to Reverse Tower Defence! Spend ");
    mvprintw(legy+17,legx+1, "your points effectively to obtain various");
    mvprintw(legy+18,legx+1, "units and battle your way against evil towers ");
    mvprintw(legy+19,legx+1, "to get to the othe side. Note: Each tower ");
    mvprintw(legy+20,legx+1, "and unit has special abilities. Plan ");
    mvprintw(legy+21,legx+1, "strategically to build the best army! Good ");
    mvprintw(legy+22,legx+1, "luck Soldier! ");



    //creating borders
    //right corner is x=85 y= 16
    //left corner is x=48 y= 16

    //top
    mvaddch(legy,legx,ACS_ULCORNER);
    for (int i = legx+1; i < legx+47; ++i)
    {
        mvaddch(legy,i,ACS_HLINE);
    }
    mvaddch(legy,legx+47,ACS_URCORNER);

    //drawing left side

    for (int  i= legy+1; i < legy+25; ++i)
    {
        mvaddch(i,legx,ACS_VLINE);
    }
    mvaddch(legy+25,legx,ACS_LLCORNER);

    //drawing right side

    for (int i = legy+1; i < legy+25; ++i)
    {
        mvaddch(i,legx+47,ACS_VLINE);
    }
    mvaddch(legy+25,legx+47,ACS_LRCORNER);

    //drawing bottom

    for (int i = legx+1; i < legx+47; ++i)
    {
        mvaddch(legy+25,i,ACS_HLINE);
    }
}


void createInterface(int xPos, int yPos)
{
    int i;
    
    i = 0;
    
    //Create menu box

    /*left*/
    for(i = 0; i < UI_LENGTH; i++)
    {
        mvaddch(i + yPos,xPos,ACS_VLINE);
    }
    
    /*right*/
    for(i = 0; i < UI_LENGTH; i++)
    {
        mvaddch(i + yPos,UI_WIDTH - 1 + xPos,ACS_VLINE);
    }
    
    /*top*/
    for(i = 0; i < UI_WIDTH; i++)
    {
        mvaddch(yPos,i + xPos,ACS_HLINE);
        if (i == 0)
        {
            mvaddch(yPos,i + xPos,ACS_ULCORNER);
        }
        if (i == UI_WIDTH - 1)
        {
            mvaddch(yPos,i + xPos,ACS_URCORNER);
        }
    }
    
    /*bottom*/
    for(i = 0; i < UI_WIDTH; i++)
    {
        mvaddch(26 + yPos,i + xPos,ACS_HLINE);
        if (i == 0)
        {
            mvaddch(26 + yPos,i + xPos,ACS_LLCORNER);
        }
        else if (i == 37)
        {
            mvaddch(26 + yPos,i + xPos,ACS_LRCORNER);
        }
    }
    
    //Prints menu contents
    mvprintw(2 + yPos, 3 + xPos, "Money: $");
    mvprintw(4 + yPos, 3 + xPos, "Unit Select:");
    mvprintw(5 + yPos, 3 + xPos, "Normal Unit (n): $%d", NORMAL_COST);
    mvprintw(6 + yPos, 3 + xPos, "HP:%d SPD:%d  DMG:%d", NORMAL_MAX_HEALTH,NORMAL_SPEED,NORMAL_DMG);
    mvprintw(8 + yPos, 3 + xPos, "Speed Unit (f): $%d",FAST_COST);
    mvprintw(9 + yPos, 3 + xPos, "HP:%d SPD:%d  DMG:%d",FAST_MAX_HEALTH,FAST_SPEED,FAST_DMG);
    mvprintw(11 + yPos, 3 + xPos, "Tank Unit (t): $%d",TANK_COST);
    mvprintw(12 + yPos, 3 + xPos, "HP:%d SPD:%d DMG:%d",TANK_MAX_HEALTH,TANK_SPEED,TANK_DMG);
    mvprintw(14 + yPos, 3 + xPos, "Remove Last Unit:");
    mvprintw(16 + yPos, 3 + xPos, "Run Game");
    mvprintw(18 + yPos, 3 + xPos, "Quit Game");
    mvprintw(19 + yPos, 3 + xPos, "Current Units:");
    
    legend();
    refresh();
    
}

unit ** manageUserInput(int xPos, int yPos, int *nUnits, int *costPointer)
{
    //initialize variables
    int i;
    int j;
    char input;
    char uType;
    unit ** unitArray;
    char selectionChar;
    int curserX;
    int curserY;
    
    
    
    i = 0;
    j = 0;
    curserX = 2 + xPos;
    curserY = 5 + yPos;
    input = ' ';
    selectionChar = ' ';
    
    
    //malloc memory for unit array
    unitArray = malloc(sizeof(unit)*45);
    
    mvaddch(curserY, curserX, '>');

    
    //read player input and act upon it
    while (i == 0)
    {
        //print amount of points the user has to purchase units
        mvprintw(2 + yPos, 12 + xPos, "     ");
        mvprintw(2 + yPos, 12 + xPos, "%d", *costPointer);
        move(curserY,curserX);
        
        input = getch();
        
        /*clears the error message printed when trying out run game with no units selected*/
        mvprintw(yPos + UI_LENGTH - 2,xPos + 2,"                        ");
        
        switch (input)
        {
            //move up if 'w' is pressed
            case 'w':
                if(curserY > 14 + yPos)
                {
                    mvaddch(curserY,curserX,' ');
                    curserY = curserY - 2;
                    mvaddch(curserY, curserX, '>');

                }
                else if(curserY - 3 >= 5 + yPos )
                {
                    mvaddch(curserY, curserX,' ');
                    curserY = curserY - 3;
                    mvaddch(curserY, curserX, '>');
                }
                break;
                
            //move down if 's' is pressed
            case 's':
                if(curserY + 3 <= 14 + yPos)
                {
                    mvaddch(curserY,curserX,' ');
                    curserY = curserY + 3;
                    mvaddch(curserY, curserX, '>');
                }
                else if(curserY + 2 <= 18 + yPos)
                {
                    mvaddch(curserY,curserX,' ');
                    curserY = curserY + 2;
                    mvaddch(curserY, curserX, '>');

                }
                break;
                
                
            //Do an action when the action key "z" is selected
            case 'z':
                //add an unit to the array
                /*Can't add if array is full (45)*/
                if (*nUnits < 45)
                {

                    if ((curserX == 2 + xPos)&&(curserY == 5 + yPos))
                    {
                        selectionChar = 'n';
                        createUnits(unitArray,selectionChar,costPointer, nUnits);
                    }
                    if ((curserX == 2 + xPos)&&(curserY == 8 + yPos))
                    {
                        selectionChar = 'f';
                        createUnits(unitArray,selectionChar,costPointer, nUnits);
                    }
                    if ((curserX == 2 + xPos)&&(curserY == 11 + yPos))
                    {
                        selectionChar = 't';
                        createUnits(unitArray,selectionChar,costPointer, nUnits);
                    }
                }
                
                //removes an element of the array
                if  ((curserX == 2 + xPos)&&(curserY == 14 + yPos))
                {
                    if(*nUnits > 0)
                    {
                        if(unitArray[*nUnits - 1]->type == normal)
                        {
                            *costPointer = *costPointer + NORMAL_COST;
                        }
                        if(unitArray[*nUnits - 1]->type == fast)
                        {
                            *costPointer = *costPointer + FAST_COST;
                        }
                        if(unitArray[*nUnits - 1]->type == tank)
                        {
                            *costPointer = *costPointer + TANK_COST;
                        }
                        free(unitArray[*nUnits-1]);
                        *nUnits = *nUnits - 1;
                    }

                    break;
                }
                
                // run game
                if ((curserX == 2 + xPos)&&(curserY == 16 + yPos))
                {

                    if (*nUnits == 0)
                    {
                        mvprintw(yPos + UI_LENGTH - 2,xPos + 2,"ERROR: No units Selected");
                        break;
                    }
                    unitArray = realloc(unitArray, sizeof(unit)**nUnits);
                    return(unitArray);
                    break;
                }
                
                // quit game
                if ((curserX == 2 + xPos)&&(curserY == 18 + yPos))
                {
                    clear();
                    refresh();
                    return (NULL);
                    i = 1;
                    break;
                }
                break;
        }
                
        //display units selectied beside "Units Selected:"

        /*clears output of the units selected*/
        for(j = 0; j <= (*nUnits/15); j++)
        {
            if (j < 3)
            {
                mvprintw(UI_LENGTH - 6 + yPos + j, 2 + xPos, "                              ");
            }
        }

        /*Prints the  units selected*/
        for(j = 0; j < *nUnits; j++)
        {
            uType = getTypeChar(unitArray[j]->type);
            if (j/15 < 3)
            {
                mvaddch(UI_LENGTH - 6 + yPos + (j/15), xPos + 2 + (j%15)*2, uType);
            }
        }
        
        move (curserY + yPos,curserX + xPos);
        refresh();
    }
    return(NULL);
}

void createUnits(unit ** unitArray, char selectionChar, int * costPointer, int * sizePointer)
{
    
    unit * unitVar;
    
    int isAllowed;
    
    isAllowed = 0;
    
    switch(selectionChar)
    {
            //create normal unit
        case 'n':
            
            //If the user has enough points, create the unit
            if (*costPointer - NORMAL_COST >= 0)
            {
                *costPointer = *costPointer - NORMAL_COST;
                isAllowed = 1;
                unitVar = malloc(sizeof(unit));
            
                unitVar->type = normal;
                unitVar->maxHealth = NORMAL_MAX_HEALTH;
		        unitVar->health = NORMAL_MAX_HEALTH;
                unitVar->speed = NORMAL_SPEED;
                unitVar->x = 0;
                unitVar->y = 0;
                unitVar->pathIndex = -1;
            }
            
            break;
            
            //create fast unit
        case 'f':
            if (*costPointer - FAST_COST >= 0)
            {
                *costPointer = *costPointer - FAST_COST;
                isAllowed = 1;
                unitVar = malloc(sizeof(unit));
                
                unitVar->type = fast;
                unitVar->maxHealth = FAST_MAX_HEALTH;
		        unitVar->health = FAST_MAX_HEALTH;
                unitVar->speed = FAST_SPEED;
                unitVar->x = 0;
                unitVar->y = 0;
                unitVar->pathIndex = -1;
            }
            
            break;
            
            //create tank unit
        case 't':
            if (*costPointer - TANK_COST >= 0)
            {
                *costPointer = *costPointer - TANK_COST;
                isAllowed = 1;
                unitVar = malloc(sizeof(unit));
                
                unitVar->type = tank;
                unitVar->maxHealth = TANK_MAX_HEALTH;
		        unitVar->health = TANK_MAX_HEALTH;
                unitVar->speed = TANK_SPEED;
                unitVar->x = 0;
                unitVar->y = 0;
                unitVar->pathIndex = -1;
            }
            
            break;
    }
    
    //add unit to array
    if(isAllowed == 1)
    {
        unitArray[*sizePointer] = unitVar;
        *sizePointer = *sizePointer + 1;

    }
}

char getTypeChar(uTypes type)
{
    if (type == normal)
    {
        return('n');
    }
    else if (type == fast)
    {
        return('f');
    }
    else if (type == tank)
    {
        return('t');
    }
    else
    {
        return('!');
    }
}
