#include "screen.h"

Screen* initScr(int width, int height, char symbol)
{
	Screen* scr = (Screen*)malloc(sizeof(Screen));
	scr->width = width;
	scr->height = height;
	scr->symbol = symbol;
	scr->elements = (char*)malloc(width*height*sizeof(char));

	int i;
	for(i = 0; i < width * height; ++i)
		scr->elements[i] = symbol;

	return scr;
}

void freeScr(Screen* scr)
{
	free(scr->elements);
	free(scr);
}

void clearScr(Screen* scr)
{
	int i = 0;
	for(i; i < scr->width * scr->height; ++i)
		scr->elements[i] = scr->symbol;
}

char getElementScr(Screen* scr, int row, int col)
{
	return scr->elements[scr->width * row + col];
}

void setElementScr(Screen* scr, int row, int col, char symbol)
{
	scr->elements[scr->width * row + col] = symbol;
}

void showScr(Screen* scr)
{
	int i, j;
	for(i = 0; i < scr->width; ++i)
	{
		for(j = 0; j < scr->height; ++j)
			printf("%c ", getElementScr(scr, i, j));
		printf("\n");
	}
}