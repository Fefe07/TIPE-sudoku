#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printGrid(int **grid); // ok

bool ***createNotes();
void updateNotes(int **grid, bool ***notes, int row, int col);

void print_tab_float(float *tab, int size);

bool solve(int **grid);
bool solve_notes(int** grid, bool*** notes, float* nb_techniques);
bool backtrack(int **grid, bool ***notes, float* nb_techniques);

bool*** initialize_notes(int** grid);

void affiche_notes(bool ***notes);
void free_notes(bool*** notes);

float consequences_new_number(int** grid, bool*** notes,int i, int j, float* nb_techniques);

void solve_simple_notes_backtrack(int** grid, float* nb_techniques){
	
	bool finished = false ;
	

	//finished = solve(grid);
	//printGrid(grid);
	if(!finished){
		//printf(" on utilise les notes\n");
		bool ***notes = initialize_notes(grid);
		//printf("Coucou1\n");
		//printGrid(grid);
		//affiche_notes(notes);
		finished = solve_notes(grid, notes, nb_techniques);
		
		//print_tab_float(nb_techniques, 13);
		// si les techniques ne suffisent pas,
		// on passe au backtracking
		if (!finished){
			printGrid(grid);
			finished = backtrack(grid, notes, nb_techniques);
			if (!finished){
				printGrid(grid);
				print_tab_float(nb_techniques,13);
			}
			assert(finished);
		}
		free_notes(notes);
	}
}