#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// l'appel de cette fonction pour toute les cases permet un premier remplissage de la grille
void updateNotes(int** grid, bool*** notes, int row, int col){
	// Entrées : une grille, deux indices row et col
	// Sorties : aucune ; les cellules du tableau de notes sont modifées sur la ligne, la colonne et la zone de row-col pour retirer grid[row][col] des notes
	int value = grid[row][col] ;
	if(value!=0){
		for(int i = 0; i<9; i++){
			notes[row][col][i] = false ;
		}



		int iPos = value - 1 ; // indice dans notes
		for(int i = 0; i < 9; i ++){
			notes[i][col][iPos] = false;
		}
		for(int j = 0; j < 9; j ++){
			notes[row][j][iPos] = false;
		}
		for(int i = 0; i < 3; i ++){
			for(int j =0; j<3; j++){
				notes[3*(row/3) + i][3*(col/3) + j][iPos] = false;
			}
		}
	}
}