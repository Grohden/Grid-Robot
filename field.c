#include "field.h"
#include<stdio.h>
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

void printField(Field * field){
	int row;
	for(row=0;row<7;row++){
		char *pointertoarray = field->representation[row];
		printf(pointertoarray);
		printf("\n");
	}
}
