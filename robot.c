#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>

int mFieldWidth=5;
int mFieldHeight=5;
int mPosX=0;
int mPosY=0;
char mCardinalPoint[]="NORTH";
bool cardinalMovement=true; //TODO:this i will implement later


void setDirectionLeft(){
	
	switch(mCardinalPoint[0]){
		case 'N':strcpy(mCardinalPoint,"EAST");break;
		case 'S':strcpy(mCardinalPoint,"WEST");break;
		case 'W':strcpy(mCardinalPoint,"NORTH");break;
		case 'E':strcpy(mCardinalPoint,"SOUTH");break;
	}
}

void setDirectionRight(){
	
	switch(mCardinalPoint[0]){			
		case 'N':strcpy(mCardinalPoint,"WEST");break;
		case 'S':strcpy(mCardinalPoint,"EAST");break;
		case 'W':strcpy(mCardinalPoint,"SOUTH");break;
		case 'E':strcpy(mCardinalPoint,"NORTH");break;
	}
	return;
	
}

bool canMoveRight() {
	if(mPosX>mFieldWidth-1)return false;
	else return true;
}

bool canMoveLeft() {
	if(mPosX<1)return false;
	else return true;
}

bool canMoveUp() {
	if(mPosY>mFieldHeight-1)return false;
	else return true;
}

bool canMoveDown() {
	if(mPosY<1)return false;
	else return true;
}

void cardinalMove(){
	//Y cardinal points
	if(mCardinalPoint[0]=='S' && canMoveDown()){mPosY-=1;}
	if(mCardinalPoint[0]=='N' && canMoveUp()){mPosY+=1;}
			
	//X cardinal points
	if(mCardinalPoint[0]=='W' && canMoveLeft()){mPosX-=1;}
	if(mCardinalPoint[0]=='E' && canMoveRight()){mPosX+=1;}
	printf(" x: %i y: %i (%s)\n",mPosX,mPosY,mCardinalPoint);
	return;
}


void processCardinalCommand(char singleChar){
	switch (singleChar){
		case 'M':
			cardinalMove();
			break;
		case 'L':
			setDirectionLeft();
			break;
		case 'R':
			setDirectionRight();
			break;
		default:
			printf(" R U TRYIN TO MAKE ME EXPLODE??\n");
			break;
			
	}
}



int main(int argc, char **argv){
	if(cardinalMovement) {
		if(argc<2){printf("ROBOT NEED COMMANDS!");return -1;}
			int x=0;
			while(x<strlen(argv[1])){
				processCardinalCommand(argv[1][x]);
				x++;
				}
			}
		
		return 0;
	}
