#ifndef UNIT_HEADER
#define UNIT_HEADER

typedef enum uTypes
{
	normal,
	fast,
	tank
	
}uTypes;

typedef struct unit{
    int type;
    int health;
    int maxHealth;
    int speed;
    int x;
    int y;
    int pathIndex;
} unit;

#endif
