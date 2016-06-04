#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<windows.h>
#include<conio.h>
#include "field.h"
#include "robot.h"

#define PLAYER 254

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void mgotoxy(int x,int y){	COORD p={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),p);
};

void hidecursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int main(int argc, char *argv[]) {
	char tecla;
	int d;
	Field testField;
	readGameField(&testField,"test.txt");
	char obst[12]={201,202,203,204,185,206,186,200,205,187,188,0};
	
	strcpy(testField.obstacles,obst);
	
	Playable p;
	p.posX=1;
	p.posY=1;

	printField(&testField);
	hidecursor();
	mgotoxy(p.posX,p.posY);
	printf("%c",PLAYER);
	
	do {
	
		//docs for windows says that for arrow keys getch() && getche() must be called twice.
		tecla=getch();
		if(tecla==-32){
		tecla=getch();
		switch(tecla){
			case UP:
				d=UP;
				break;
			case DOWN:
				d=DOWN;
				break;
			case RIGHT:
				d=RIGHT;
				break;
			case LEFT:
				d=LEFT;
				break;
		};
		//Clear last position.
		mgotoxy(p.posX,p.posY);
		printf("%c",' ');
		//Move, update coordenates
		move(&p,&testField,d);
		//Print new position.
		mgotoxy(p.posX,p.posY);
		printf("%c",PLAYER);
		if(p.posX==77 && p.posY==5) break;
		usleep(20000);
		
		mgotoxy(20,20);
		printf("x:%d, y:%d   ",p.posX,p.posY);
		}
	} while(true);
	char ** tst;
	system("cls");
	drawBox(20,10);
	mgotoxy((20/2)-3,10/2);
	puts("U won!");
	
	mgotoxy(1,21);
}
