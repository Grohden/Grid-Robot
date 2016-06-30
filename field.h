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
	char startPos[2]; //character that must sinalize where the player go
	char finalPos[2]; //character that must sinalize where is the final position to end the level.
	char ** representation; //intended do be used with malloc/alloc
} Field;

/* This function check for a char specified in the field.obstacles[] and if it find it it return true. */
bool hasObstacle(Field * field,int row,int col);

/* This function properly create a box(doesnt print it)
 * Note: destionation must be alocated in memory before drawBox() recive it.
 * Note: destionation is intended to be used with X Y coordenates, this is why it is an array of arrays.
 */
void drawBox(int width,int height, char ** destination);


/* Functions mean to create(they doesnt print) a box, they could be used to something else.
 * created the functions because dev-c doesnt support extra characters from ASCII table.
 */
char * drawBottom(int width);

char * drawMiddle(int width);

char * drawTop(int width);

/*This function read a file, and fill the Field struct with the needed data.
 *It also convert the characters in the file to a better grafical visualization.
 */
void readGameField(Field * field, char * fileName);
#endif
