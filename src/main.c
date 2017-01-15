#include "main.h"


int main()
{
    int levelID = 1;
    int pathLength;
    int currency;
    int uiX = 3;
    int uiY = 3;
    int mapSizeX, mapSizeY;
    int winLose;

    int enemyHealth = 10; 
    int nUnits;
    int nTowers;
    int nPairs;

    path thePath;
    tower *towers;
    unit **units;
    void *** unitTowerArray;


   /*start screen*/
    initscr();
    curs_set(0);
    noecho();
    cbreak();
   /*init colors*/
    start_color();

    init_pair(text, 7,0);
    init_pair(blue, 4,0);
    init_pair(red, 1,0);
    init_pair(orange, 3,0);
    init_pair(green, 2,0);
   

   /*main loop*/
    while(levelID != 4)
    {

        /*load levels*/
        towers = loadLevel(levelID, &pathLength, &thePath, &nTowers, &currency, &mapSizeX, &mapSizeY);
        if (towers == NULL){
            //The level could not be initialized
            return 0;
        }

       /*user interface*/
        drawMapBorder(mapSizeX,mapSizeY);
        drawMap(&thePath, pathLength);
        drawTowers(towers, nTowers);
        createInterface(uiX, uiY);
        
        /*null is returned on 'quit game' option*/
        units = manageUserInput(uiX, uiY, &nUnits,&currency);
        if (units == NULL)
        {
            break;
        }
        clear();

       /* returns 1 is you lose, 2 if you win 0 if neither.*/
       while (winLose == 0)
       {
            /*manage map state*/
            unitTowerArray = manageMapState(units,towers,&thePath,nUnits,nTowers,pathLength,&nPairs,&enemyHealth);

            /*manage game state*/
            applyUnitsDamage(unitTowerArray,nPairs,units,nUnits);

            freeTowerUnitArray(unitTowerArray, &nPairs);

            /*draw game state*/
            drawMapBorder(mapSizeX,mapSizeY);
            drawMap(&thePath,pathLength);
            drawTowers(towers,nTowers);

            
            drawUnits(&thePath,units,nUnits,pathLength);
            
            winLose = checkGameOver(enemyHealth, units, nUnits);

            refresh();
            usleep(300000);
        }

        /*if they win, change level*/


        clearLevel(units,&nUnits,towers,&nTowers,&thePath,&pathLength,&enemyHealth);
        clear();
        if (winLose == 2)
        {
            mvprintw(32, 6, "                                       ");
            mvprintw(32, 6, "CONGRATS!! You won. Moved to next level");
            refresh();
            levelID += 1;
        }
        if (winLose == 1){
            mvprintw(32, 6, "                                       ");
            mvprintw(32, 6, "You lost. Lets play again.");
            refresh();
        }
        
        winLose = 0;
    }
    endwin();

    return 0;

}
/*free units*/
void freeUnits (unit **U, int *nUnits)
{
    for(int i = 0; i < *nUnits; i++)
    {
        free(U[i]);
    	U[i] = NULL;
    }
    free(U);
    U = NULL;
    *nUnits = 0;
}

/*free towers*/
void freeTowers (tower *T, int *nTowers)
{
    *nTowers = 0;
    free(T);
}
void clearLevel(unit **U, int *nUnits, tower *T,int *nTowers, path* thePath, int *pathLength, int *enemyHealth)
{
    freeUnits(U,nUnits);
    freeTowers(T,nTowers);
    clearPath(thePath,pathLength);
    *enemyHealth = 10;
}
void clearPath(path *P, int *pathLength)
{
    for (int i = 0; i < *pathLength; i++)
    {
        P->x[i] = 0;
        P->y[i] = 0;
        P->isSlowed[i] = 0;
    }
    *pathLength = 0;
}
