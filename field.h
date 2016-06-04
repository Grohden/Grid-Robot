#ifndef FIELD__
#define FIELD__
#include<stdbool.h>

#ifndef _FIELD_DEBUG
#define _FIELD_DEBUG false //Debug Logs.
#endif

/* Obstacles must end with \0, and must contain all characters that represent obstacles */
typedef struct Field {
	int width;
	int height;
	char obstacles[20];
	char ** representation; //intended do be used with malloc/alloc
} Field;

bool hasObstacle(Field * field,int row,int col);

void readGameField(Field * field, char * fileName);
#endif
