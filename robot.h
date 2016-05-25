#ifndef ROBOT__
#define ROBOT__

#include "field.h"
#ifndef _ROBOT_DEBUG
#define _ROBOT_DEBUG false //Debug Logs.
#endif
/*Variables and Structs */

typedef enum {NORTH,SOUTH,WEST,EAST}  cardinalPoint; 

typedef enum {UP=72,DOWN=80,LEFT=75,RIGHT=77} direction; //Same numbers for keyboard arrow keys.

typedef struct Playable {
	int posX;
	int posY;
	cardinalPoint facing;
} Playable;

/* Changes cardinalPoint based on actual facing value. */
void turnLeft(Playable * playable);

void turnRight(Playable * playable);

/* X axys*/
bool canMoveRight(Playable * playable,Field * field);

bool canMoveLeft(Playable * playable,Field * field);

/* Y axys*/
bool canMoveUp(Playable * playable,Field * field);

bool canMoveDown(Playable * playable,Field * field);

/* This move the playble based on the actual direction (cardinalPoint facing),
 * and return if the character has been moved. */
bool cardinalMove(Playable * playable,Field * field);

//This recives a single char: M(move, calls cardinalMove()), L and R (Left, Right, uses the turn functions)
void singleOrder(Playable * playable,Field * field,char singleChar);

/* This moves ignoring cardinal points, 
 * and return if the character has been moved. */ 
bool move(Playable * playable,Field * field, direction d);

#endif
