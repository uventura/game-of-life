#include "cell.h"

void* cellInit(){return NULL;}

void freeCells(Cell* mainCell)
{
	Cell* prev = mainCell;
	while(prev != NULL)
	{
		prev = mainCell->prevCell;
		free(mainCell);
		mainCell = prev;
	}

	printf("Memória liberada!\n");
}

void showCells(Cell* mainCell)
{
	int i = 1;

	printf("\n--------------------------------\n");

	while(mainCell != NULL)
	{
		printf("%d -> Row: %d, Col: %d, State: ", i, mainCell->row, mainCell->col);

		if(mainCell->alive == true)
			printf("[Alive]\n");
		else
			printf("[Dead]\n");

		mainCell = mainCell->prevCell;
		++i;
	}

	printf("--------------------------------\n");
}


Cell* newCell(Cell* mainCell, int row, int col, bool alive)
{
	Cell* new = (Cell*)malloc(sizeof(Cell));
	new->row = row;
	new->col = col;
	new->alive = alive;
	new->prevCell = mainCell;

	if(mainCell == NULL) new->indice = 0;
	else new->indice++;

	return new;
}

void killRepetedCells(Cell* cell)
{	
	Cell* aux;
	if(cell != NULL)
		aux = cell->prevCell;	

	while(cell != NULL)
	{
		while(aux != NULL)
		{
			if(aux->alive == false)
			{
				aux = aux->prevCell;
				continue;
			}

			if(aux->row == cell->row && aux->col == cell->col)
				aux->alive = false;

			aux = aux->prevCell;
		}

		cell = cell->prevCell;
		if(cell != NULL) aux = cell->prevCell;
	}
}

Cell* removeDeadCells(Cell* mainCell)
{
	Cell* active = mainCell;
	Cell* prev = NULL;

	while(active != NULL)
	{
		if(active->alive == false)
		{
			if(active == mainCell)
			{
				mainCell = active->prevCell;

				free(active);
				active = mainCell;

				prev = NULL;
				continue;
			}

			prev->prevCell = active->prevCell;
			free(active);

			active = prev->prevCell;
			continue;
		}

		prev = active;
		active = active->prevCell;
	}

	return mainCell;
}