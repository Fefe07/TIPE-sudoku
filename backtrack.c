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

bool ***createNotes();
void updateNotes(grid_t g, int row, int col);

bool solve_notes(grid_t g, bool(**techniques)(grid_t), int n);
bool est_ok(int** grid);

void printGrid(int **grid);
void print_notes(bool ***notes);
void free_grid(int** grid);
void free_notes(bool*** notes);

bool backtrack(grid_t g, bool(**techniques)(grid_t), int n){
	// Entrées : une grille (peut-etre deja une copie due a un precedent appel de cette fonction),
	// 			 ses notes  
	// Sorties : false si la grille n'a pas de solutions (impossible sur l'appel de l'original),
	// 			 true sinon

	
	
	//printf("On passe au Backtracking !\n");
	
	// on trouve la meilleure case
	int best_row ;
	int best_col ;
	int best_nb_notes = 42;
	for(int i =0; i<9; i++){
		for(int j = 0; j<9; j++){
			if (g->grid[i][j] == 0){
				int nb_notes = 0 ;
				for(int k = 0; k<9; k++){
					if (g->notes[i][j][k]){
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
	//printf("meilleure case : %d, %d avec %d possibilités\n", best_row, best_col, best_nb_notes);
	if (best_nb_notes <= 0){
		// on a trouvé une incohérence, on retourne donc faux
		//printf("une incohérence !\n");
		return false ;
	}
	
	//on fait du backtracking
	
	for(int value = 1; value<=9; value++){
		//pour chaque valeur valable
		if(g->notes[best_row][best_col][value-1]){
			//printf("on essaye avec %d\n", value);
			// on duplique la grille
			grid_t newG = malloc(sizeof(struct grid_s));
			assert(newG!=NULL);

			newG->grid = malloc(9*sizeof(int*));
			assert(newG->grid!=NULL);
			for(int i = 0; i<9; i++){
				newG->grid[i] = malloc(9*sizeof(int));
				assert(newG->grid[i]!=NULL);
			}
			for(int i=0; i<9; i++){
				for(int j=0; j<9; j++){
					newG->grid[i][j] = g->grid[i][j];
				}
			}
			
			newG->notes = createNotes();
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					for(int k = 0; k<9; k++){
						newG->notes[i][j][k] = g->notes[i][j][k];
					}
				}
			}
			
			newG->grid[best_row][best_col] = value ;
			updateNotes(newG, best_row, best_col);
			g->nb_techniques[12] ++;

			newG->nb_techniques = g->nb_techniques ;
			/*
			int* new_nb_techniques = malloc(10*sizeof(int));
			assert(new_nb_techniques!=NULL);
			for(int i = 0; i<10; i++){
				new_nb_techniques[i] = nb_techniques[i];
			}*/

			// on essaye de finir la grille
			//printGrid(newG->grid);
			//print_notes(newG->notes);
			bool finished = solve_notes(newG, techniques, n);
			
			if(est_ok(newG->grid)){
			

				// si on peut finir la grille avec le guess
				if(finished){
					//printf("On a trouve une solution !\n");
					//printGrid(newG->grid);
					//fflush(stdout);
					for(int i=0; i<9; i++){
						for(int j=0; j<9; j++){
							g->grid[i][j] = newG->grid[i][j];
						}
					}
					/*for(int i = 0; i<10; i++){
						nb_techniques[i] = new_nb_techniques[i];
					}*/
					free_grid(newG->grid);
					free_notes(newG->notes);
					free(newG);
					return true ;
				}
				else {
					bool correct = backtrack(newG, techniques, n);
					if (correct){
						//printf("On a trouve une solution !\n");
						for(int i=0; i<9; i++){
							for(int j=0; j<9; j++){
								g->grid[i][j] = newG->grid[i][j];
							}
						}
						/*
						for(int i = 0; i<10; i++){
							nb_techniques[i] = new_nb_techniques[i];
						}*/
						free_grid(newG->grid);
						free_notes(newG->notes);
						free(newG);
						return true ;
					}
					else{
						//nb_techniques[9] = new_nb_techniques[9];
						g->notes[best_row][best_col][value-1] = false ;
					}
					// si correct est faux, il faut tester les autres possibilités !
				}
				
			}
			free_grid(newG->grid);
			free_notes(newG->notes);
			free(newG);
		}
	}
	// si on en arrive la, c'est qu'aucune des possibilités ne marchait
	//printf("Aucune des possibilités n'a fonctionné\n");
	return false ;
}
