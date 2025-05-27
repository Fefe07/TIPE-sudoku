#include <stdbool.h>
#include <stdio.h>

bool lastRemainingCell(int **grid);
bool lastFreeCell(int **grid);
bool lastPossibleNumber(int **grid);

void printGrid(int** grid);

bool solve(int** grid){
	//printf("Coucou_de_solve\n");
	bool ok = true;
	while (ok) { // tant qu'on trouve un nouvel indice
		ok = lastFreeCell(grid);
		if (!ok) { // si la première méthode échoue, passe à la deuxième
			ok = lastRemainingCell(grid);
			// //printf("coucou1\n");
			if (!ok) { // si la deuxième méthode échoue, passe à la troisième
				// //printf("coucou2\n");
				ok = lastPossibleNumber(grid);

			}
		}
		printGrid(grid);
	}
	
	// renvoie true si la grille est finie, false sinon
	for(int i = 0; i<9; i++){
		for(int j = 0; j<9; j++){
			//printf("coucou1");
			if(grid[i][j] == 0){
				//printf("\ncoucou2\n");
				return false;
			}
		}
	}
	return true;
}