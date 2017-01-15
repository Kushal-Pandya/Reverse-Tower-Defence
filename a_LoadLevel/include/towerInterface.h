#ifndef TOWER_HEADER
#define TOWER_HEADER

#define NORMAL 0
#define MISSILE 1
#define ARCHER 2
#define SLOW 3

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
