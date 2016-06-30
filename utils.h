/*
 *Author: Gabriel de Oliveira Rohden.
 */
#ifndef UTILS__
#define UTILS__


/*This function change the text color and its background,color values are 1 byte size(0 to 255).
 * Colors doesnt changes until the function is called with another color.
 */
void setTextColor(int k);

//This function changes the number of character per lines and the lines of cmd, this resize the screen.
void setScreenSize(int cols,int lines);

//This function hides the cursor ( _ ) that waits the input from user.
void hidecursor();

//this must be improved, it doesnt really work.
void freeArray(char** myPointer);

//this function puts the cursor on specified coordenate. if the coordenate doesnt exist it dont work.
void mgotoxy(int x,int y);

#endif

