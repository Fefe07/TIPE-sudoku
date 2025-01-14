#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



bool ***createNotes();
void updateNotes(int **grid, bool ***notes, int row, int col);

bool solve_notes(int** grid, bool*** notes, float* nb_techniques);
bool est_ok(int** grid);

void printGrid(int **grid);
void affiche_notes(bool ***notes);
void free_grid(int** grid);
void free_notes(bool*** notes);

bool backtrack(int** grid, bool*** notes, float* nb_techniques){
	// Entrées : une grille (peut-etre deja une copie due a un precedent appel de cette fonction),
	// 			 ses notes  
	// Sorties : false si la grille n'a pas de solutions (impossible sur l'appel de l'original),
	// 			 true sinon

	
	
	printf("On passe au Backtracking !\n");
	
	// on trouve la meilleure case
	int best_row ;
	int best_col ;
	int best_nb_notes = 42;
	for(int i =0; i<9; i++){
		for(int j = 0; j<9; j++){
			if (grid[i][j] == 0){
				int nb_notes = 0 ;
				for(int k = 0; k<9; k++){
					if (notes[i][j][k]){
						nb_notes ++ ;
					}
				}
				if (nb_notes < best_nb_notes){
					best_nb_notes = nb_notes ;
					best_row = i ;
					best_col = j ;
				}
			}
		}
	}
	printf("meilleure case : %d, %d avec %d possibilités\n", best_row, best_col, best_nb_notes);
	if (best_nb_notes <= 0){
		// on a trouvé une incohérence, on retourne donc faux
		printf("une incohérence !\n");
		return false ;
	}
	
	//on fait du backtracking
	
	for(int value = 1; value<=9; value++){
		//pour chaque valeur valable
		if(notes[best_row][best_col][value-1]){
			printf("on essaye avec %d\n", value);
			// on duplique la grille
			int** newGrid = malloc(9*sizeof(int*));
			assert(newGrid!=NULL);
			for(int i = 0; i<9; i++){
				newGrid[i] = malloc(9*sizeof(int));
				assert(newGrid[i]!=NULL);
			}
			for(int i=0; i<9; i++){
				for(int j=0; j<9; j++){
					newGrid[i][j] = grid[i][j];
				}
			}
			
			bool ***newNotes = createNotes();
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					for(int k = 0; k<9; k++){
						newNotes[i][j][k] = notes[i][j][k];
					}
				}
			}
			
			newGrid[best_row][best_col] = value ;
			updateNotes(newGrid, newNotes, best_row, best_col);
			nb_techniques[12] ++;
			/*
			int* new_nb_techniques = malloc(10*sizeof(int));
			assert(new_nb_techniques!=NULL);
			for(int i = 0; i<10; i++){
				new_nb_techniques[i] = nb_techniques[i];
			}*/

			// on essaye de finir la grille
			printf("Coucou1\n");
			//printGrid(newGrid);
			//affiche_notes(newNotes);
			bool finished = solve_notes(newGrid, newNotes, /*new_*/nb_techniques);
			
			if(est_ok(newGrid)){
			

				// si on peut finir la grille avec le guess
				if(finished){
					printf("On a trouve une solution !\n");
					printGrid(newGrid);
					fflush(stdout);
					for(int i=0; i<9; i++){
						for(int j=0; j<9; j++){
							grid[i][j] = newGrid[i][j];
						}
					}
					/*for(int i = 0; i<10; i++){
						nb_techniques[i] = new_nb_techniques[i];
					}*/
					free_grid(newGrid);
					free_notes(newNotes);
					return true ;
				}
				else {
					bool correct = backtrack(newGrid, newNotes, /*new_*/nb_techniques);
					if (correct){
						//printf("On a trouve une solution !\n");
						for(int i=0; i<9; i++){
							for(int j=0; j<9; j++){
								grid[i][j] = newGrid[i][j];
							}
						}
						/*
						for(int i = 0; i<10; i++){
							nb_techniques[i] = new_nb_techniques[i];
						}*/
						free_grid(newGrid);
						free_notes(newNotes);
						return true ;
					}
					else{
						//nb_techniques[9] = new_nb_techniques[9];
						notes[best_row][best_col][value-1] = false ;
					}
					// si correct est faux, il faut tester les autres possibilités !
				}
				
			}
			free_grid(newGrid);
			free_notes(newNotes);
		}
	}
	// si on en arrive la, c'est qu'aucune des possibilités ne marchait
	return false ;
}
