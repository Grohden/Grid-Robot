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
void messageBox(char * str, int strSize);

char obst[13]={177,201,202,203,204,185,206,186,200,205,187,188,0}; //walls and corners

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*Creates a message box with one option (i know, it is useless since we have list(), may i change this to a pop-up with timer*/
void messageBox(char * str, int strSize){
	system("cls");
	
	int boxCols=36;
	int boxLines=7;
	char ** Textbox=calloc(boxCols*boxLines,sizeof(char));
    drawBox(boxCols,boxLines,Textbox);
    
	//Go to 1/4 of screen
    mgotoxy(boxCols/2,boxLines/2);
    
    int x=0;
    //draw the box in screen
	for(x=0;x<boxLines;x++){
		mgotoxy((SCREEN_WIDTH/2)-(boxCols/2),(SCREEN_HEIGHT/2)-(boxLines/2)+x);
    	printf("%s\n",Textbox[x]);
	}
	mgotoxy((SCREEN_WIDTH/2)-(strSize/2),(SCREEN_HEIGHT/2));
	printf("%s",str);
}

/*Intended to print the representation of Field struct in center of screen */
void printField(Field * field){
	int x;
	int centerVertical=(SCREEN_HEIGHT/2)-(field->height/2);
	int centerHorizontal=(SCREEN_WIDTH/2)-(field->width/2);

	for(x=0;x<field->height;x++){
		mgotoxy(centerHorizontal,centerVertical+x);
		printf("%s",field->representation[x]);
	}
}

/*This thing should be avoided, just done in hurry.*/
int levelCounter=1;
/*Labirinthy game, ending with snake game in last level.*/
void playGame(){
	char tecla;
	int score=0;
	int d;
	system("cls");
	system("color 07"); // prevent background b0000ggggs
	
	//Intro message
	char format[]="Level %d";
	char msg[1];
	sprintf(msg,format,levelCounter);
	messageBox(msg,sizeof(format)-3);
	sleep(2);
	system("cls");

	Field testField;
	char cenario[]="cenario_%d.txt";
	char level[1];
  	sprintf(level,cenario,levelCounter);
	readGameField(&testField,level);
	
	int centerY=(SCREEN_HEIGHT/2)-(testField.height/2);
	int centerX=(SCREEN_WIDTH/2)-(testField.width/2);
	int top=(SCREEN_HEIGHT/2)-(testField.height/2)-1;
	int start=(SCREEN_WIDTH/2)-(testField.width/2);
	
	
	strcpy(testField.obstacles,obst);
	
	Playable p;
	p.posX = p.posY = 1; 

	printField(&testField);
	hidecursor();
	mgotoxy(p.posX+centerX,p.posY+centerY);
	printf("%c",PLAYER);
	
	do {
		//docs for windows says that for arrow keys getch() && getche() must be called twice.
		mgotoxy(start,top);
		printf("Score: %d  ",score);
		tecla=getch();
		if(tecla==-32){
			tecla=getch();
			//Clear last position.
			mgotoxy(p.posX+centerX,p.posY+centerY);
			printf("%c",' ');
			//Move, update coordenates
			if(move(&p,&testField,tecla)){score++;}
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
    if(levelCounter<3){
    	levelCounter+=1;
		playGame();
	} else {
		char finalmsg[]="U finished the main game!";
		char welcomeToHell[]="Now play this if you can!";
		messageBox(finalmsg,sizeof(finalmsg));
		sleep(2);
		messageBox(welcomeToHell,sizeof(welcomeToHell));
		sleep(2);
		levelCounter=1;
		snake("cenario_3.txt");
	}


};

/*Snake game, imcomplete, some limitations with array.*/
void snake(char * campo){
	char key;
	int d;
	system("cls");

	Field snakeField;
	readGameField(&snakeField,campo);
	
	//character and field declarations
	char sn[14]={177,201,202,203,204,185,206,186,200,205,187,188,SNAKE};
	strcpy(snakeField.obstacles,sn);	
	Playable snake;
	snake.posX = snake.posY = 1;
	snake.facing=SOUTH; 
	
	//center calculations.
	int centerY=(SCREEN_HEIGHT/2)-(snakeField.height/2);
	int centerX=(SCREEN_WIDTH/2)-(snakeField.width/2);

	printField(&snakeField);
	hidecursor();
	
	int snakeSize=3;
	int x;
	for(x=1;x<=snakeSize;x++){
		mgotoxy(1+centerX,x+centerY);
		printf("%c",SNAKE);
	}
	
	snake.posX = 1;
	snake.posY = snakeSize;
	
	int tail[8][2]={{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7},{1,8}};
	int count=0;
	bool end=false;
	
	while(true){
		mgotoxy(tail[count][0]+centerX,tail[count][1]+centerY);
		printf("%c",' ');
		
		if(kbhit()){
			key=getch();
			if(key==-32){
				key=getch();
				if(key==LEFT){
					turnLeft(&snake);
				} 
				else if(key==RIGHT){
					turnRight(&snake);
				}	
			}
		}
		//Move, update coordenates
		if(!cardinalMove(&snake,&snakeField)){break;}
		
		//Print new position.
		mgotoxy(snake.posX+centerX,snake.posY+centerY);
		printf("%c",SNAKE);
		
		snakeField.representation[tail[count][1]][tail[count][0]]=' ';
		snakeField.representation[snake.posY][snake.posX]=177;
		
		//Tail control
		if(count<snakeSize){
			tail[count][0]=snake.posX;
			tail[count][1]=snake.posY;
			count+=1;
		}
		if(count == snakeSize){count=0;}
		usleep(800000);
		}
	char msg[]="U faild this game!";
	messageBox(msg,sizeof(msg));
	sleep(1);	
	mainMenu();
}

/*Create the menu options and some submenus*/
void mainMenu(){
	char *options[10]={"Labirinto","Snake","Records","Creditos","Sair"};
	char *creators[20]={"Gabriel de Oliveira Rohden","Leonardo Tadeu Diniz Leal","","Code Found at:","https://github.com/Grohden/Grid-Robot/tree/C"};
	char msg[]="Buy the DLC to use this feature.";
	
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
			snake("snake.txt");
			break;
		case 2:
			messageBox(msg,sizeof(msg));
			sleep(2);
			mainMenu();
			break;
		case 3:
			list(creators,5,35);
			system("pause");
			mainMenu();			
			break;
		case 4:break;
	};
	mgotoxy(1,35);
}

/* This function draw a box and put in the middle of screen, and put the options on center*/
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
	mgotoxy(1,35);
}

/* This function uses the list function and implement arrow keys listening to navigate the options.
 * it returns the number of chosed option.
 */
int selectableList(char * options[],int numberOfOptions,int sizeOfOptions){
	if(kbhit()){
		getch(); //prevent acidental enters
	}
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
	
	char key;
	hidecursor();	
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
