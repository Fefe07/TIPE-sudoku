#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/*fonction print grid
Entrée : une grille
Sortie : aucune, on imprime la grille*/
void printGrid(int **grid) {
	printf("Grille actuelle : \n");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if(grid[i][j]==0){
				printf("   ");
			}
			else{
				printf("%d  ", grid[i][j]);
			}
			if (j == 2 || j == 5) {
				printf("| ");
			}
		}
		printf("\n");
		if (i == 2 || i == 5) {
			printf("-----------------------------\n");
		}
	}
}