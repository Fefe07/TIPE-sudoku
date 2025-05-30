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

void printGrid(int **grid); // ok

bool ***createNotes();
void updateNotes(grid_t g, int row, int col);

void print_tab_float(float *tab, int size);

bool solve(int **grid);
bool solve_notes(grid_t g, bool(**techniques)(grid_t g), int n);
bool backtrack(grid_t g, bool(**techniques)(grid_t g), int n);

void initialize_notes(grid_t g);

void print_notes(bool ***notes);
void free_notes(bool*** notes);

float consequences_new_number(int** grid, bool*** notes,int i, int j, float* nb_techniques);

void solve_simple_notes_backtrack(grid_t g, bool(**techniques)(grid_t g), int n){
	
	bool finished = false ;

	//finished = solve(grid);
	if(!finished){
		//printf(" on utilise les notes\n");
		initialize_notes(g);
		//printGrid(g->grid);
		assert(g->notes!=NULL);	
		//print_notes(g->notes);
		finished = solve_notes(g, techniques, n);
		
		//print_tab_float(g->nb_techniques, 13);
		// si les techniques ne suffisent pas,
		// on passe au backtracking
		if (!finished){
			//printGrid(g->grid);
			finished = backtrack(g, techniques, n);
			if (!finished){
				//printGrid(g->grid);
				print_tab_float(g->nb_techniques,13);
			}
			assert(finished);
		}
		free_notes(g->notes);
	}
}