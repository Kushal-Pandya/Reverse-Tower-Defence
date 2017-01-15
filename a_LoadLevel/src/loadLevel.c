#include <curses.h>
#include <towerInterface.h>
#include <pathInterface.h>
#include <string.h>
#include <stdlib.h>


char **readLevelFile(int *width, int *height, int *nTowers, int *currency);
tower *initializeTowers(char **levelString, int width, int height, int *nTowers, int *pathLength, int *startX, int *startY);
int buildMap(char **levelString, int width, int height, int pathLength, path *thePath, int startX, int startY);


////////////////////////////////////////////////////FUNCTION DEFINITIONS
int isInBounds(int y, int x, int height, int width){
    if (y < 0 || y >= height)
        return 0;
    if (x < 0 || x >= width)
        return 0;
    
    return 1;
}

tower * loadLevel (int * pathLength, path * thePath, int * nTowers, int *currency){
    char **levelString;     //Level map
    int width;              //Width of the map
    int height;             //Height of the map
    int startX, startY;     //Coordinates of the begining of the path
    
    levelString = readLevelFile(&width, &height, nTowers, currency);
    
    tower * towers = initializeTowers(levelString, width, height, nTowers, pathLength, &startX, &startY);
    if (towers == NULL){
        //Some error occured when initializing the towers
        return NULL;
    }
    
    if (!buildMap(levelString, width, height, *pathLength, thePath, startX, startY)){
        //The path could not be initialized
        free(towers);
        return NULL;
    }
    
    return towers;
}

char **readLevelFile(int *width, int *height, int *nTowers, int *currency)
{
    char fileName[100];
    int levelID = 0;
    
    do
    {
        printf("\nInput the level number (1, 2 or 3): ");
        scanf("%d", &levelID);
        fflush(stdin);
        if (levelID < 1 || levelID > 3)
            printf("\nInvalid input. Please input a number (1, 2 or 3).");
    } while (levelID < 1 || levelID > 3);
    
    switch (levelID)
    {
        case 1:
            strcpy(fileName, "level1.txt");
            break;
        case 2:
            strcpy(fileName, "level2.txt");
            break;
        case 3:
            strcpy(fileName, "level3.txt");
            break;
    }
    
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
                towers[numT].fireRate = 5;
                towers[numT].counter = 1;
                towers[numT].damage = 5;
                towers[numT].range = 5;
                numT++;
            }
            else if (levelString[y][x] == 'M'){
                towers[numT].type = MISSILE;
                towers[numT].x = x;
                towers[numT].y = y;
                towers[numT].fireRate = 3;
                towers[numT].counter = 1;
                towers[numT].damage = 10;
                towers[numT].range = 8;
                numT++;
            }
            else if (levelString[y][x] == 'A'){
                towers[numT].type = ARCHER;
                towers[numT].x = x;
                towers[numT].y = y;
                towers[numT].fireRate = 7;
                towers[numT].counter = 1;
                towers[numT].damage = 3;
                towers[numT].range = 10;
                numT++;
            }
            else if (levelString[y][x] == 'S'){
                towers[numT].type = SLOW;
                towers[numT].x = x;
                towers[numT].y = y;
                towers[numT].fireRate = 5;
                towers[numT].counter = 1;
                towers[numT].damage = 0;
                towers[numT].range = 7;
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
