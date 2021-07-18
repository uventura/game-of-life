#ifndef BASICS_LIB_GOL
#include "basics.h"
#endif

typedef struct cell
{
	int indice;
	int row, col;
	bool alive;
	struct cell* prevCell;
}Cell;

void* cellInit();
void freeCells(Cell* mainCell);
void showCells(Cell* mainCell);

Cell* newCell(Cell* mainCell, int row, int col, bool alive);

void killRepetedCells(Cell* cell);
Cell* removeDeadCells(Cell* mainCell);