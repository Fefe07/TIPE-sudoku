#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool ***createNotes();
void updateNotes(int **grid, bool ***notes, int row, int col);

bool*** initialize_notes(int** grid){
	bool ***notes = createNotes();
	// notes[i][j][k] == true si la case ij peut accueillir l'indice k+1

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			updateNotes(grid, notes, i, j);
		}
	}
	return notes ;

}