#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "robot.h"
#include "field.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	char tecla;
	int d;
	Field testField={21,7,"*:)",
		{"********************",
		 "*                  *",
		 "*                  *",
		 "*         :)       *",
		 "*                  *",
		 "*                # *",
		 "********************"}
	};
	
	Playable p;
	p.posX=1;
	p.posY=1;
	
	testField.representation[p.posY][p.posX]='O';
	
	printField(&testField);
	do {
		testField.representation[p.posY][p.posX]=' ';
		
		//docs for windows says that for arrow keys getch() && getche() must be called twice.
		tecla=getch();
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
		
		move(&p,&testField,d);
		//system("pause");
		if(testField.representation[p.posY][p.posX]=='#'){ //victory tokken.
	    	testField.representation[p.posY][p.posX]='O';
	    	system("cls");
	    	printField(&testField);
			break;
		} 
		testField.representation[p.posY][p.posX]='O';
		system("cls");
		printField(&testField);
	} while(true);
	puts("U won!");
}
