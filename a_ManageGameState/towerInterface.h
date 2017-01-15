#ifndef TOWER_HEADER
#define TOWER_HEADER

	enum {NORMAL,MISSILE,ARCHER,SLOW} type;
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
