#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

void solve_simple_notes_backtrack(int** grid, float* nb_tech);

float assess_techniques(int** grid, float* coeffs, float* coeffs_first_use){
    float *nb_tech = malloc(13 * sizeof(float));
    assert(nb_tech!=NULL);
    for (int i = 0; i < 13; i++) {
        nb_tech[i] = 0.;
    }
    //printGrid(g.grid);
    solve_simple_notes_backtrack(grid, nb_tech);
    float score = 0. ;
    for(int i = 0; i<13; i++){
        score += nb_tech[i]*coeffs[i];
        if(nb_tech[i]>0.0001){
            score+=coeffs_first_use[i];
        }
    }
    return score ;
}