#ifndef _DEF_GAMESTRUCTS_H
#define _DEF_GAMESTRUCTS_H

#define ARRAY_SIZE 1000
#define NORMAL 0
#define MISSILE 1
#define ARCHER 2
#define SLOW 3

typedef struct path{
    int x[ARRAY_SIZE];
    int y[ARRAY_SIZE];
} path;

typedef struct tower{
    int type;
    int x;
    int y;
    int fireRate;
    int counter;
    int damage;
    int range;
} tower;

#endif
