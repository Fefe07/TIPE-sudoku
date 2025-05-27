#include <assert.h>
#include <stdbool.h>



struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

// l'appel de cette fonction pour toute les cases permet un premier remplissage de la grille
void updateNotes(grid_t g, int row, int col){
	// Entrées : une grille, deux indices row et col
	// Sorties : aucune ; les cellules du tableau de notes sont modifées sur la ligne, la colonne et la zone de row-col pour retirer grid[row][col] des notes
	int value = g->grid[row][col] ;
	if(value!=0){
		for(int i = 0; i<9; i++){
			g->notes[row][col][i] = false ;
		}



		int iPos = value - 1 ; // indice dans notes
		for(int i = 0; i < 9; i ++){
			g->notes[i][col][iPos] = false;
		}
		for(int j = 0; j < 9; j ++){
			g->notes[row][j][iPos] = false;
		}
		for(int i = 0; i < 3; i ++){
			for(int j =0; j<3; j++){
				g->notes[3*(row/3) + i][3*(col/3) + j][iPos] = false;
			}
		}
	}
}