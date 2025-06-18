#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>


struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;



void solve_simple_notes_backtrack(grid_t g, bool(**techniques)(grid_t g), int n);
void printGrid(int** grid);

float assess_techniques(int** grid, float* coeffs, float* coeffs_first_use, bool(**techniques)(grid_t g), int n){
    grid_t g = malloc(sizeof(struct grid_s));
    assert(g!=NULL);
    g->nb_techniques = malloc(13 * sizeof(float));
    assert(g->nb_techniques!=NULL);
    for (int i = 0; i < 13; i++) {
        g->nb_techniques[i] = 0.;
    }
    g->grid = grid;
    printGrid(g->grid);
    solve_simple_notes_backtrack(g, techniques, n);
    float score = 0. ;
    for(int i = 0; i<13; i++){
        score += g->nb_techniques[i]*coeffs[i];
        if(g->nb_techniques[i]>0.0001){
            score+=coeffs_first_use[i];
        }
    }
    free(g->nb_techniques);
    free(g);
    return score ;
}