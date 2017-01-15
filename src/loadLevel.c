#include "loadLevel.h"

/* inRange
 * 
 * Requires: a pointer to a path (path *), a tower (tower), and a path index
 * 
 * Purpose: To check if a path index is in range of a tower.
 *          Returns '1' if in range, '0' if not.
*/
static int inRange(path* P,tower someTower, int index){
    double distance,xDisp,yDisp;
    xDisp = someTower.x - P->x[index];
    yDisp = someTower.y - P->y[index];
    distance = sqrt((xDisp * xDisp) + (yDisp * yDisp));

    if(distance <= someTower.range){
        return 1;
    }else{
        return 0;
    }
}

/* assignSlow
 * 
 * Requires: a pointer to a path (path *), an array of towers (tower *),
 *           the length of the path (int) and the length of the tower arrays (int)
 * 
 * Purpose: To check if a path index is in range of a slow tower and flags it as slowed
 *           by marking the isSlowed[path index]  = 1.
*/
static void assignSlow(path *P, tower * T, int pathLength, int nTowers)
{
    for (int i = 0; i < nTowers; i++)
    {
        /*if slow tower, check if path index is in range*/
        if (T[i].type == SLOW)
        {
            for (int j = 0; j < pathLength; j++)
            {
                if(inRange(P,T[i],j))
                {
                    P->isSlowed[j] = 1;
                }
            }
        }

    }
}

/* isInBounds
 * 
 * Requires: The x coordinate (int), the y coordinate (int), the map height (int) and the map width (int).
 * 
 * Purpose: Checks if the position with coordinates x and y is within the map area.
*/
int isInBounds(int y, int x, int height, int width){
    if (y < 0 || y >= height)
        return 0;
    if (x < 0 || x >= width)
        return 0;
    
    return 1;
}



tower * loadLevel (int levelID, int * pathLength, path * thePath, int * nTowers, int *currency, int *width, int *height){
    char **levelString;     //Level map
    int startX, startY;     //Coordinates of the begining of the path
    
    levelString = readLevelFile(levelID, width, height, nTowers, currency);
    if (levelString == NULL){
		return NULL;
	}
    
    tower * towers = initializeTowers(levelString, *width, *height, nTowers, pathLength, &startX, &startY);
    if (towers == NULL){
        //Some error occured when initializing the towers
        return NULL;
    }
    
    if (!buildMap(levelString, *width, *height, *pathLength, thePath, startX, startY)){
        //The path could not be initialized
        free(towers);
        return NULL;
    }

    assignSlow(thePath,towers,*pathLength,*nTowers);
    return towers;
}

char **readLevelFile(int levelID, int *width, int *height, int *nTowers, int *currency)
{
    char fileName[50] = "res/level";
    char strLevelID[3];
    
    sprintf(strLevelID, "%d", levelID);
    strcat(fileName, strLevelID);
    strcat(fileName, ".txt");
    
    //printf("Loading level %d.", levelID);
    
    FILE * file = fopen(fileName, "r");
    if (file == NULL){
        printf("\nThere was a problem loading the level file %s.", fileName);
        return NULL;
    }
    
    if (fscanf(file, "%d %d", width, height) == EOF) return NULL;
    if (fscanf(file, "%d", nTowers) == EOF) return NULL;
    if (fscanf(file, "%d", currency) == EOF) return NULL;
    
    char **levelString = malloc(sizeof(char*) * *height);
    char temp[*width + 1];
    
    int i;
    for (i = 0; i < *height; i++){
        if (fscanf(file, "%s", temp) == EOF) return NULL;
        levelString[i] = malloc(sizeof(char) * *width);
        strncpy(levelString[i], temp, *width);
    }
    fclose(file);
    return levelString;
}

tower *initializeTowers(char **levelString, int width, int height, int *nTowers, int *pathLength, int *startX, int *startY)
{
    tower *towers = (tower*)malloc (sizeof (tower) * *nTowers);
    int numT = 0;   //Conter for towers
    int num = 0;    //Number of path positions
    
    //Initialize towers
    int x, y;
    for (x = 0; x < width; x++){
        for (y = 0; y < height; y++){
            if (levelString[y][x] == '+'){
                num++;
            }
            else if (levelString[y][x] == '='){
                *startX = x;
                *startY = y;
                num++;
            }
            else if (levelString[y][x] == '$'){
                num++;
            }
            else if (levelString[y][x] == 'N'){
                towers[numT].type = NORMAL;
                towers[numT].x = x;
                towers[numT].y = y;
                towers[numT].fireRate = NORMAL_FIRE_RATE;
                towers[numT].counter = NORMAL_COUNTER;
                towers[numT].damage = NORMAL_DAMAGE;
                towers[numT].range = NORMAL_RANGE;
                numT++;
            }
            else if (levelString[y][x] == 'M'){
                towers[numT].type = MISSILE;
                towers[numT].x = x;
                towers[numT].y = y;
                towers[numT].fireRate = MISSILE_FIRE_RATE;
                towers[numT].counter = MISSILE_COUNTER;
                towers[numT].damage = MISSILE_DAMAGE;
                towers[numT].range = MISSILE_RANGE;
                numT++;
            }
            else if (levelString[y][x] == 'A'){
                towers[numT].type = ARCHER;
                towers[numT].x = x;
                towers[numT].y = y;
                towers[numT].fireRate = ARCHER_FIRE_RATE;
                towers[numT].counter = ARCHER_COUNTER;
                towers[numT].damage = ARCHER_DAMAGE;
                towers[numT].range = ARCHER_RANGE;
                numT++;
            }
            else if (levelString[y][x] == 'S'){
                towers[numT].type = SLOW;
                towers[numT].x = x;
                towers[numT].y = y;
                towers[numT].fireRate = SLOW_FIRE_RATE;
                towers[numT].counter = SLOW_COUNTER;
                towers[numT].damage = SLOW_DAMAGE;
                towers[numT].range = SLOW_RANGE;
                numT++;
            }
        }
    }
    
    *pathLength = num;
    
    return towers;
}

int buildMap(char **levelString, int width, int height, int pathLength, path *thePath, int startX, int startY)
{
    //Build path
    int index = 0;      //Index of the path position
    int y = startY;
    int x = startX;
    int nextY, nextX;   //Next neighbour position being checked
    int deltaY, deltaX; //Current position - previous position (direction from previous to current)
    
    //Initialize search direction
    if (startX == 0){
        //Path starts at left side and goes to the right
        deltaY = 0;
        deltaX = 1;
    }
    else if (startX == width-1){
        //Path starts at right side and goes to the left
        deltaY = 0;
        deltaX = -1;
    }
    else if (startY == 0){
        //Path starts at top side and goes to the bottom
        deltaY = 1;
        deltaX = 0;
    }
    else{
        //Path starts at bottom side and goes to the top
        deltaY = -1;
        deltaX = 0;
    }
    
    //Store starting position of the path
    thePath->x[index] = x;
    thePath->y[index] = y;
    thePath->isSlowed[index] = 0;
    index++;

    while (index < pathLength){
        //Check position directly opposite from previous path position
        if (isInBounds((nextY = y+deltaY), (nextX = x+deltaX), height, width)){
            if (levelString[nextY][nextX] == '+' || levelString[nextY][nextX] == '$'){
                //Found next position
                y = nextY;
                x = nextX;
                thePath->x[index] = x;
                thePath->y[index] = y;
                index++;
                continue;  //Continue search
            }
        }
        
        //Check positions in each side of current position
        if (isInBounds((nextY = y+deltaX), (nextX = x+deltaY), height, width)){
            if (levelString[nextY][nextX] == '+' || levelString[nextY][nextX] == '$'){
                //Found next position
                deltaY = nextY - y;
                deltaX = nextX - x;
                y = nextY;
                x = nextX;
                thePath->x[index] = x;
                thePath->y[index] = y;
                index++;
                continue;  //Continue search
            }
        }
        if (isInBounds((nextY = y-deltaX), (nextX = x-deltaY), height, width)){
            if (levelString[nextY][nextX] == '+' || levelString[nextY][nextX] == '$'){
                //Found next position
                deltaY = nextY - y;
                deltaX = nextX - x;
                y = nextY;
                x = nextX;
                thePath->x[index] = x;
                thePath->y[index] = y;
                index++;
                continue;  //Continue search
            }
        }
        
        return 0;  //The path is segmented. Level file malformed
    }
    
    return 1;
}
