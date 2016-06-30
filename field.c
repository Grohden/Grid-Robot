#include "field.h"
#include<stdio.h>
#include<malloc.h>
#include<strings.h>


bool hasObstacle(Field * field,int row,int col){
	int cont;
	for(cont=0;cont<=strlen(field->obstacles)+1;cont++) {
		if(field->obstacles[cont]==field->representation[row][col]){
			if(_FIELD_DEBUG){
				printf("%c\n",field->representation[row][col]);
			};
			
			return true;
		};
	};
	return false;	
};

char * drawTop(int width){
	int x;
	char * str=(char *) calloc(width+1,sizeof(char));
	str[0]=201; //left upper corner
	
	for(x=1;x<width;x++){
 		str[x]=205; //top wall
	};
	
	str[width]=187; //right upper corner
	str[width+1]=0;
	return str;
};

char * drawMiddle(int width){
	int x;
	char * str=(char *) calloc(width+1,sizeof(char));
	str[0]=186;
	
	for(x=1;x<width;x++){
 		str[x]=32; //space
	};
	
	str[width]=186;
	str[width+1]=0;
	return str;
};	

char * drawBottom(int width){
	int x;
	char * str=(char *) calloc(width+1,sizeof(char));
	str[0]=200; //left bottom corner
	
	for(x=1;x<width;x++){
 		str[x]=205; //top wall
	};
	
	str[width]=188; //right bottom corner
	str[width+1]=0;
	return str;
};

void drawBox(int width,int height, char ** destination){
    int x;
    
    //Topper
    destination[0]=(char *) drawTop(width);
    
    //Middle
    for(x=1;x<height-1;x++){
        destination[x]=(char *) drawMiddle(width);
    }
    //Bottom
    destination[height-1]=(char *) drawBottom(width);
}

void readGameField(Field * field, char * fileName){
	int qtdLine,qtdCol;
	int x=0;
	int i=0;
	char text[150];
	
	FILE * arq = fopen(fileName, "r");
	
	fscanf(arq,"%i",&qtdLine);
	qtdLine-=2;
	field->height=qtdLine;
	fscanf(arq,"%i",&qtdCol);
	field->width=qtdCol-1;
	//To break string in a bi-dimensional array
	char ** final = calloc(qtdLine*qtdCol,sizeof(char));
	
	fgets(text,150,arq);
	
	//characters convertions to ansii extended.
	for (i=0; i<qtdLine; i++) {
		fgets(text,150,arq);
		text[qtdCol+1]=0;
		for(x=0;x<qtdCol;x++){
			switch(text[x]){
				/*
				case '1':text[x]=201;break;
				case '2':text[x]=187;break;
				case '3':text[x]=200;break;
				case '4':text[x]=188;break;
				case '5':text[x]=202;break;
				case '6':text[x]=203;break;
				case '7':text[x]=204;break;
				case '8':text[x]=185;break;
				case '9':text[x]=206;break;
				case '-':text[x]=205;break;
				case '|':text[x]=186;break;
				*/
				case '*':text[x]=' ';break;
				case '#':
					text[x]=176;
					field->finalPos[0]=x;
					field->finalPos[1]=i;
					break;
				case '@':
					text[x]=' ';
					field->startPos[0]=x;
					field->startPos[1]=i;
					break;
				default: 
					text[x]=177;
					break;
			}
		}
		final[i]=(char *) calloc(qtdCol,sizeof(char));
		strcpy(final[i],text);
	}
	fclose(arq);
	field->representation=final;
}

