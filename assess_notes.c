#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>

struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

bool*** initialize_notes(grid_t g) ;
int assess_nb_clues(int ** grid);
void free_notes(bool*** notes);

float assess_nb_notes(int** grid){
    grid_t g = malloc(sizeof(struct grid_s));
    assert(g!=NULL);
    g->grid = grid ;
    initialize_notes(g);

    float count = 0 ;
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            int n = 0 ;
            for(int k = 0; k<9; k++){
                if(g->notes[i][j][k]){
                    n++;
                }
            }
            if (n>0){
                count += log(n);
            }
        }
    }
    int nb_clues = assess_nb_clues(g->grid);
    free_notes(g->notes);
    free(g);
    
    return (count/*/(81-nb_clues)*/) ;

}