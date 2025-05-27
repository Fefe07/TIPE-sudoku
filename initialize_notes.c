#include <assert.h>
#include <stdbool.h>
#include<stdlib.h>

struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

bool ***createNotes();
void updateNotes(grid_t g, int row, int col);

void initialize_notes(grid_t g){
	g->notes = createNotes();
	assert(g->notes!=NULL);
	// notes[i][j][k] == true si la case ij peut accueillir l'indice k+1

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			updateNotes(g, i, j);
		}
	}
	assert(g->notes!=NULL);

}