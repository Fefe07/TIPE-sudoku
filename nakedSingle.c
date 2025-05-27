#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

void updateNotes(int** grid, bool*** notes, int row, int col);
float consequences_new_number(int** grid, bool*** notes,int i, int j, float* nb_tech);

bool nakedSingle(grid_t g){
	// renvoie true si on parvient à placer un chiffre avec la technique du naked single et place ledit chiffre
	// renvoie false sinon
	for(int i = 0; i<9; i ++){ // on parcourt la grille
		for(int j = 0; j<9; j++){
			if(g->grid[i][j]== 0){ // si la case est vide
				int count = 0 ;
				int chiffre = 0 ;
				for(int k = 0; k<9; k++){ 
					if(g->notes[i][j][k]){
						count ++;
						chiffre = k+1 ;
					}
				}
				if (count == 1){ // si un seul chiffre est possible
					assert(chiffre != 0);
					g->grid[i][j] = chiffre ;
					//printf("Technique : nakedSingle\n");
					//printf("row = %d, col = %d, val = %d\n", i, j, chiffre);
					
					//consequences_new_number(grid, notes, i, j, nb_tech);
					return true;
				}
			}
		}
	}
	return false ;

}

bool nakedSingle_one_cell(int** grid, bool*** notes, int i, int j, float* nb_tech){
	if(grid[i][j]== 0){ // si la case est vide
		int count = 0 ;
		int chiffre = 0 ;
		for(int k = 0; k<9; k++){ 
			if(notes[i][j][k]){
				count ++;
				chiffre = k+1 ;
			}
		}
		if (count == 1){ // si un seul chiffre est possible
			assert(chiffre != 0);
			grid[i][j] = chiffre ;
			//printf("Technique : nakedSingle_one_cell\n");
			//printf("row = %d, col = %d, val = %d\n", i, j, chiffre);
			//consequences_new_number(grid, notes, i, j, nb_tech);
			return true;
		}
	}
	return false ;
}


