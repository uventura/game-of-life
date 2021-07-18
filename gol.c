#include "includes/screen.h"
#include "includes/cell.h"

#include <time.h>

typedef struct
{
	int amountAliveCells;
	Cell* deadCells;
} CellsArround;

void putCellScr(Screen* scr, Cell* cell)
{
	while(cell != NULL)
	{
		if(cell->row > -1 && cell->row < scr->height && cell->col > -1 && cell->col < scr->width)
			setElementScr(scr, cell->row, cell->col, 'o');

		cell = cell->prevCell;
	}
}

void searchCellsArround(Screen* scr, Cell* cell, CellsArround* result)
{
	// First you need put cell on scr->elements.
	// result has to be defined.

	int row, col;
	for(row = cell->row-1; row <= cell->row+1; ++row)
	{
		for(col = cell->col-1; col <= cell->col+1; ++col)
		{
			if(row < 0 || row >= scr->height || col < 0 || col >= scr->width || (row == cell->row && col == cell->col))
				continue;

			if(getElementScr(scr, row, col) == 'o')
				++result->amountAliveCells;
			else
				result->deadCells = newCell(result->deadCells, row, col, false);
		}
	}
}

Cell* killCellsAddNew(Screen* scr, Cell* cell)
{
	CellsArround infoArround;
	infoArround.amountAliveCells = 0;
	infoArround.deadCells = NULL;

	while(cell != NULL)
	{
		searchCellsArround(scr, cell, &infoArround);

		if(infoArround.amountAliveCells < 2 || infoArround.amountAliveCells > 3)
			cell->alive = false;

		cell = cell->prevCell;
		infoArround.amountAliveCells = 0;
	}

	return infoArround.deadCells;
}

Cell* discoverNewCells(Screen* scr, Cell* cell)
{
	Cell* babies = killCellsAddNew(scr, cell);
	Cell* result = babies;

	CellsArround infoBaby;
	infoBaby.amountAliveCells = 0;
	infoBaby.deadCells = NULL;

	while(result != NULL)
	{
		searchCellsArround(scr, result, &infoBaby);

		if(infoBaby.amountAliveCells == 3)
			result->alive = true;

		result = result->prevCell;

		infoBaby.amountAliveCells = 0;
		infoBaby.deadCells = NULL;
	}

	return babies;
}

Cell* newPopulation(Screen* scr, Cell* cell)
{
	Cell* result = discoverNewCells(scr, cell);

	killRepetedCells(cell);	
	killRepetedCells(result);

	cell = removeDeadCells(cell);
	result = removeDeadCells(result);

	while(cell != NULL)
	{
		result = newCell(result, cell->row, cell->col, true);
		cell = cell->prevCell;
	}

	return result;
}

int main()
{
	// [ SET BELLOW YOUR INITIAL ELEMENTS AND GRID'SIZE ]

	Cell* cells = NULL;
	cells = newCell(cells, 15, 15, true);
	cells = newCell(cells, 15, 16, true);
	cells = newCell(cells, 15, 17, true);
	cells = newCell(cells, 14, 16, true);

	// [ SCREEN SIZE AND THE "BLANK" ELEMENT
	Screen* scr = initScr(30, 30, '.');

	// END OF SETTINGS

	showScr(scr);
	
	putCellScr(scr, cells);
	showScr(scr);
	
	clock_t init = clock();
	double delta_t;

	int i = 0;
	while(1)
	{
		delta_t = (double)(clock() - init)/CLOCKS_PER_SEC;

		if(delta_t > 0.2)
		{
			system("clear"); /*If Windows replace "clear" to "cls". */
			putCellScr(scr, cells);
			cells = newPopulation(scr, cells);
			
			showScr(scr);
			clearScr(scr);

			init = clock();

			++i;
		}

		if(i == 100) break;
	}

	freeCells(cells);
	freeScr(scr);

	return 0;
}
