//TODO: optimize this
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //sleep lib
#include <string.h>
#include "utils.h"
#include "field.h"
#include "robot.h"

#define PLAYER 207
#define SNAKE 219
#define BLACK_WHITE 07
#define WHITE_BLACK 240
#define SCREEN_WIDTH 150
#define SCREEN_HEIGHT 40

int list(char * options[],int numberOfOptions,int sizeOfOptions);
int selectableList(char * options[],int numberOfOptions,int sizeOfOptions);
void mainMenu();

char obst[12]={201,202,203,204,185,206,186,200,205,187,188,0}; //walls and corners

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void printField(Field * field){
	int x;
	int centerVertical=(SCREEN_HEIGHT/2)-(field->height/2);
	int centerHorizontal=(SCREEN_WIDTH/2)-(field->width/2);

	for(x=0;x<field->height;x++){
		mgotoxy(centerHorizontal,centerVertical+x);
		printf("%s",field->representation[x]);
	}
}

void playGame(){
	char tecla;
	int d;
	system("cls");
	system("color 07"); // prevent background b0000ggggs

	Field testField;
	readGameField(&testField,"cenario.txt");
	
	int centerY=(SCREEN_HEIGHT/2)-(testField.height/2);
	int centerX=(SCREEN_WIDTH/2)-(testField.width/2);
	
	strcpy(testField.obstacles,obst);
	
	Playable p;
	p.posX = p.posY = 1; 

	printField(&testField);
	hidecursor();
	mgotoxy(p.posX+centerX,p.posY+centerY);
	printf("%c",PLAYER);
	
	do {
		//docs for windows says that for arrow keys getch() && getche() must be called twice.
		tecla=getch();
		if(tecla==-32){
			tecla=getch();
			//Clear last position.
			mgotoxy(p.posX+centerX,p.posY+centerY);
			printf("%c",' ');
			//Move, update coordenates
			move(&p,&testField,tecla);
			//Print new position.
			mgotoxy(p.posX+centerX,p.posY+centerY);
			printf("%c",PLAYER);
			if(p.posX==testField.finalPos[0] && p.posY==testField.finalPos[1]) break;
			usleep(20000);
		}
	} while(true);
	
	system("cls");
	
	int boxCols=30;
	int boxLines=7;
	char ** Textbox=calloc(boxCols*boxLines,sizeof(char));
    drawBox(boxCols,boxLines,Textbox);
    
	//Go to 1/4 of screen
    mgotoxy(boxCols/2,boxLines/2);
    
    //draw the box in screen
	int x;
	char message[]=" You've finished!";
	for(x=0;x<boxLines;x++){
		mgotoxy((SCREEN_WIDTH/2)-(boxCols/2),(SCREEN_HEIGHT/2)-(boxLines/2)+x);
    	printf("%s\n",Textbox[x]);
	}
	mgotoxy((SCREEN_WIDTH/2)-(strlen(message)/2),(SCREEN_HEIGHT/2));
	printf("%s",message);
	sleep(2);	
	mainMenu();


};

void snake(){
	char key;
	int d;
	system("cls");

	Field snakeField;
	readGameField(&snakeField,"cenario.txt");
	
	//character and field declarations
	char sn[15]={201,202,203,204,185,206,186,200,205,187,188,SNAKE};
	strcpy(snakeField.obstacles,sn);	
	Playable snake;
	snake.posX = snake.posY = 1;
	snake.facing=SOUTH; 
	
	//center calculations.
	int centerY=(SCREEN_HEIGHT/2)-(snakeField.height/2);
	int centerX=(SCREEN_WIDTH/2)-(snakeField.width/2);

	printField(&snakeField);
	hidecursor();
	mgotoxy(snake.posX+centerX,snake.posY+centerY);
	snakeField.representation[snake.posX][snake.posY]=SNAKE;
	printf("%c",SNAKE);
	while(true){
		if(kbhit()){
			key=getch();
			if(key==-32){
				key=getch();
				if(key==LEFT){
					singleOrder(&snake,&snakeField,'L');
				} 
				else if(key==RIGHT){
					singleOrder(&snake,&snakeField,'R');
				}	
			}
		}
		//Move, update coordenates
		singleOrder(&snake,&snakeField,'M');
		//Print new position.
		mgotoxy(snake.posX+centerX,snake.posY+centerY);
		printf("%c",SNAKE);
		usleep(500000);
	}
}

void mainMenu(){
	char *options[10]={"Labirinto","Snake","Records","Creditos","Sair"};
	char *creators[20]={"Gabriel de Oliveira Rohden","Leonardo Leal","","Code Found at:","github.com//grohden//grid-robot#c"};
	
	int numberOfOptions=5;
	int sizeOfOptions=sizeof(*options);
	
	int choice=selectableList(options,numberOfOptions,sizeOfOptions);
	setTextColor(BLACK_WHITE);
	mgotoxy(1,35);
	switch(choice){
		case 0:
			playGame();
			break;
		case 1:
			snake();
			break;
		case 2:break;
		case 3:
			list(creators,5,35);
			break;
		case 4:break;
	};
	mgotoxy(1,35);
}

int list(char * options[],int numberOfOptions,int sizeOfOptions){
    int cols=SCREEN_WIDTH;
    int lines=SCREEN_HEIGHT;
    int boxCols=cols/2;
    int boxLines=lines/2;
    system("cls");
    
    char ** box=calloc(boxCols*boxLines,sizeof(char));
    drawBox(boxCols,boxLines,box);
    
	//Go to 1/4 of screen
    mgotoxy(boxCols/2,boxLines/2);
    
    //draw the box in screen
	int x;
	for(x=0;x<boxLines;x++){
		mgotoxy(boxCols/2,(boxLines/2)+x);
    	printf("%s\n",box[x]);
	}
	
	char halfOpts=(numberOfOptions)/2;
	char itemsSize=(sizeOfOptions);

	//Go to box center and write options
	for(x=-halfOpts;x<=halfOpts;x++){
		mgotoxy(boxCols-(itemsSize/2),boxLines+x);
		printf(options[x+halfOpts]);
	}
}

int selectableList(char * options[],int numberOfOptions,int sizeOfOptions){
	list(options,numberOfOptions,sizeOfOptions);
	int boxCols=SCREEN_WIDTH/2;
    int boxLines=SCREEN_HEIGHT/2;
	char halfOpts=(numberOfOptions)/2;
	char itemsSize=(sizeOfOptions);
	int selectedOption=-halfOpts;
	//Select first item
	setTextColor(WHITE_BLACK);
	mgotoxy(boxCols-(itemsSize/2),boxLines+selectedOption);
	printf(options[selectedOption+halfOpts]);
	
	hidecursor();
	char key;
	do{
		key=getch();
		if(key==-32){ //if its a arrow key
			key=getch();
			setTextColor(BLACK_WHITE);
			mgotoxy(boxCols-(itemsSize/2),boxLines+selectedOption);
			printf(options[selectedOption+halfOpts]);
			
			switch(key){
			case UP:
				selectedOption= selectedOption<=-halfOpts ? halfOpts : selectedOption-1; //Infinite scroll
				break;
			case DOWN:
				selectedOption= selectedOption>=halfOpts ? -halfOpts : selectedOption+1; //Infinite scroll
				break;
			}
			setTextColor(WHITE_BLACK);
			mgotoxy(boxCols-(itemsSize/2),boxLines+selectedOption);
			printf("%s",options[selectedOption+halfOpts]);
		}
	} while(key!=13); //Enter key.
	return selectedOption+halfOpts;
}

int main(int argc, char *argv[]) {
	setScreenSize(SCREEN_WIDTH,SCREEN_HEIGHT);
	mainMenu();
	exit(0);
	return 0;
}
