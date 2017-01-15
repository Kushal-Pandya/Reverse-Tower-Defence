#ifndef UNIT_HEADER
#define UNIT_HEADER


#define NORMAL_MAX_HEALTH 90
#define NORMAL_SPEED 2
#define NORMAL_COST 100
#define NORMAL_DMG 2

#define TANK_MAX_HEALTH 175
#define TANK_SPEED 1
#define TANK_COST 125
#define TANK_DMG 1

#define FAST_MAX_HEALTH 75
#define FAST_SPEED 3
#define FAST_COST 75
#define FAST_DMG 3


typedef enum uTypes
{
	tank,
	normal,
	fast
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
