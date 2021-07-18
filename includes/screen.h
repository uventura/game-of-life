#ifndef BASICS_LIB_GOL
#include "basics.h"
#endif

typedef struct
{
	int width, height;
	char symbol;
	char* elements;
} Screen;

Screen* initScr(int width, int height, char symbol);
void freeScr(Screen* scr);
void showScr(Screen* scr);
void clearScr(Screen* scr);

char getElementScr(Screen* scr, int row, int col);
void setElementScr(Screen* scr, int row, int col, char symbol);