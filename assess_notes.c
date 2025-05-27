#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>

struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

bool*** initialize_notes(grid_t g) ;

int assess_nb_notes(int** grid){
    grid_t g = malloc(sizeof(struct grid_s));
    assert(g!=NULL);
    g->grid = grid ;
    initialize_notes(g);

    int count = 0 ;
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            for(int k = 0; k<9; k++){
                if(g->notes[i][j][k]){
                    count++;
                }
            }
        }
    }
    return count ;

}