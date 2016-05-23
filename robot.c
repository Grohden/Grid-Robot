#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>

#define DEBUG true //Debug Logs.

/*Variables and Structs */
typedef enum {NORTH,SOUTH,WEST,EAST}  cardinalPoint; 

typedef enum {UP,DOWN,LEFT,RIGHT} direction;

char points[4][6]={"NORTH","SOUTH","EAST","WEST"};

typedef struct {
	int posX;
	int posY;
	cardinalPoint facing;
} Playable;

/* Fields will count to fieldX+1 since 0 counts. */
int mFieldWidth=5;
int mFieldHeight=5; 
bool cardinalMovement=false;

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
	if(DEBUG){
		printf("Now facing: %s \n",points[playable->facing]);
	}
}

bool canMove(Playable * playable, direction d, char * obstacles){
	if(d==RIGHT && playable->posX>=mFieldWidth && ) {return false};

}
bool canMoveRight(Playable * playable,int fieldWidth,int fieldHeight) {
	if(playable->posX>fieldHeight-1)return false;
	else return true;
}

bool canMoveLeft(Playable * playable) {
	if(playable->posX<1)return false;
	else return true;
}

bool canMoveUp(Playable * playable) {
	if(playable->posY>mFieldHeight-1) return false;
	else return true;
}

bool canMoveDown(Playable * playable) {
	if(playable->posY<1)return false;
	else return true;
}

void cardinalMove(Playable * playable){
	//Y cardinal points
	if(playable->facing==SOUTH && canMoveDown(playable)){playable->posY-=1;}
	if(playable->facing==NORTH && canMoveUp(playable)){playable->posY+=1;}
			
	//X cardinal points
	if(playable->facing==WEST && canMoveLeft(playable)){playable->posX-=1;}
	if(playable->facing==EAST && canMoveRight(playable)){playable->posX+=1;}
	if(DEBUG){
		printf(" x: %i",playable->posX);
		printf(" y: %i",playable->posY);
		printf("(%s)\n",points[playable->facing]);
	}
}

void move(Playable * playable, direction d){
	
	//Y cardinal points
	if(d==DOWN && canMoveDown(playable)){playable->posY-=1;}
	if(d==UP && canMoveUp(playable)){playable->posY+=1;}
			
	//X cardinal points
	if(d==LEFT && canMoveLeft(playable)){playable->posX-=1;}
	if(d==RIGHT && canMoveRight(playable)){playable->posX+=1;}
	if(DEBUG){
		printf(" x: %i",playable->posX);
		printf(" y: %i \n",playable->posY);
	}
}

void singleOrder(Playable * playable,char singleChar){
	switch (singleChar){
		case 'M':
			cardinalMove(playable);
			break;
		case 'L':
			turnLeft(playable);
			break;
		case 'R':
			turnRight(playable);
			break;
		default:
			printf(" R U TRYIN TO MAKE ME EXPLODE??\n");
			break;
			
	}
}

int main(int argc, char **argv){
	if(argc<2){printf("ROBOT NEED COMMANDS!");return -1;}
	//With structs implementation we can use more instances, maybe for mobs.
	Playable player={0,0,NORTH};
	int x;
	//if we wish to use cardinal directions to orientate the mob.
	 for(x = 0; x<strlen(argv[1]); x++){
		if(cardinalMovement) {
			singleOrder(&player,argv[1][x]);
		} else {
			move(&player,NORTH);
			}
		}
	return 0;
	}
