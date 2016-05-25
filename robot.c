#include<stdio.h>
#include<string.h>
#include "robot.h"

static const char points[][6]={"NORTH","SOUTH","EAST","WEST"};

/* Methods */
void turnLeft(Playable * playable){
	
	switch(playable->facing){
		case NORTH:
			playable->facing=WEST;
			break;
		case SOUTH:
			playable->facing=EAST;
			break;
		case EAST:
			playable->facing=NORTH;
			break;
		case WEST:
			playable->facing=SOUTH;
			break;
	};
}

void turnRight(Playable * playable){
	
	switch(playable->facing){
		case NORTH:
			playable->facing=EAST;
			break;
		case SOUTH:
			playable->facing=WEST;
			break;
		case EAST:
			playable->facing=SOUTH;
			break;
		case WEST:
			playable->facing=NORTH;
			break;
	};
	if(_ROBOT_DEBUG){
		printf("Now facing: %s \n",points[playable->facing]);
	}
}

bool canMoveRight(Playable * playable,Field * field) {
	int posX=playable->posX;
	if(posX>=field->width){
		return false;
	} 
	if(hasObstacle(field,playable->posY,posX+1)){
		return false;	
	}
	return true;
}

bool canMoveLeft(Playable * playable,Field * field) {
	int posX=playable->posX;
	if(posX<=0){
		return false;
	} 
	if(hasObstacle(field,playable->posY,posX-1)){
		return false;	
	}
	return true;
}

/*Some problem, since the string begin in 0, 0 will be the top, not the bottom, so the logic is switched with canMoveDown()*/
bool canMoveUp(Playable * playable,Field * field) {
	int posY=playable->posY;
	if(posY<=0){
		return false;
	} 
	if(hasObstacle(field,posY-1,playable->posX)){
		return false;	
	}
	return true;
}

bool canMoveDown(Playable * playable,Field * field) {
	int posY=playable->posY;
	if(posY>=field->height){
		return false;
	} 
	if(hasObstacle(field,posY+1,playable->posX)){
		return false;	
	}
	return true;
}

bool cardinalMove(Playable * playable,Field * field){
	
	switch(playable->facing){
		case SOUTH:
			if(canMoveDown(playable,field)){
				playable->posY+=1;
				return true;
			}
			break;
		case NORTH:
			if(canMoveUp(playable,field)){
				playable->posY-=1;
				return true;
			}
			break;
		case WEST:
			if(canMoveLeft(playable,field)){
				playable->posX-=1;
				return true;
			}
			break;
		case EAST:
			if(canMoveRight(playable,field)){
				playable->posX+=1;
				return true;
			}
			break;
	};
	if(_ROBOT_DEBUG){
		printf(" x: %i",playable->posX);
		printf(" y: %i",playable->posY);
		printf("(%s)\n",points[playable->facing]);
	}
}

bool move(Playable * playable,Field * field, direction d){
	bool r=false;
	switch(d){
		case DOWN:
			if(canMoveDown(playable,field)){
				playable->posY+=1;
				r=true;
			}
			break;
		case UP:
			if(canMoveUp(playable,field)){
				playable->posY-=1;
				r=true;
			}
			break;
		case LEFT:
			if(canMoveLeft(playable,field)){
				playable->posX-=1;
				r=true;
			}
			break;
		case RIGHT:
			if(canMoveRight(playable,field)){
				playable->posX+=1;
				r=true;
			}
			break;
	};
	
	//if(DEBUG){
		printf(" x: %i",playable->posX);
		printf(" y: %i \n",playable->posY);
	//};
	return r;	
}

void singleOrder(Playable * playable,Field * field,char singleChar){
	switch (singleChar){
		case 'M':
			cardinalMove(playable,field);
			break;
		case 'L':
			turnLeft(playable);
			break;
		case 'R':
			turnRight(playable);
			break;
		default:
			//printf(" R U TRYIN TO MAKE ME EXPLODE??\n");
			break;
			
	}
}
