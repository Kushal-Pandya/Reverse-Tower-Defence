#ifndef TOWER_HEADER
#define TOWER_HEADER


#define NORMAL_DAMAGE 3
#define NORMAL_FIRE_RATE 1
#define NORMAL_COUNTER 1
#define NORMAL_RANGE 5

#define MISSILE_DAMAGE 7
#define MISSILE_FIRE_RATE 3
#define MISSILE_COUNTER 3
#define MISSILE_RANGE 4

#define ARCHER_DAMAGE 3
#define ARCHER_FIRE_RATE 2
#define ARCHER_COUNTER 2
#define ARCHER_RANGE 10

#define SLOW_DAMAGE 0
#define SLOW_FIRE_RATE 0
#define SLOW_COUNTER 0
#define SLOW_RANGE 2




typedef enum tTypes
{
	NORMAL,
	MISSILE,
	ARCHER,
	SLOW
}tTypes;

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
