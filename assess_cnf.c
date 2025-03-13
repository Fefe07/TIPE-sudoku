#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<stdio.h>

typedef struct var_s{
    /* Une variable est de la forme p_i,j,k, elle indique si la case i,j contient k */
    /* 0 <= i,j < 9 */
    /* 1 <= k <= 9 */
    int i;
    int j;
    int k;
}var;

typedef struct {
    /* On représente un litéral par une variable (un entier) 
    et une positivite (1 si litéral positif, 0 si litéral négatif)
    On représente donc une clause par un tableau de litéraux */
    int nb_lit ;
    var* vars ;
    bool* positif ;
}clause;


typedef struct {
    /* Ce type est beaucoup moins général ; le filtre est spécifique à cet usage */
    int nb_var ;
    var* vars ;
    bool* filtre ;
}clause_1in9;


struct k_cnf_s {
    int m ; //nb_clauses
    int k ; 
    clause* clauses ;
};
typedef struct k_cnf_s* k_cnf; 

void free_clause(clause c);
k_cnf sudoku_to_cnf(int** grid);
void printGrid(int** grid);
void print_k_cnf(k_cnf f);

float assess_cnf(int** grid){
    //printGrid(grid);
    k_cnf f = sudoku_to_cnf(grid);
    // on compte les variables
    int n = 0;
    int m = f->m ;
    //print_k_cnf(f);
    bool*** existing_variables = malloc(9*sizeof(bool**));
    assert(existing_variables!=NULL);
    for(int i = 0; i<9; i++){
        existing_variables[i] = malloc(9*sizeof(bool*));
        assert(existing_variables[i]!=NULL);
        for(int j = 0; j<9; j++){
            existing_variables[i][j] = malloc(9*sizeof(bool));
            assert(existing_variables[i][j]!=NULL);
            for(int k = 0; k<9; k++){
                existing_variables[i][j][k] = false;
            }
        }
    }
    for(int a = 0; a<f->m; a++){
        for(int b = 0; b<f->clauses[a].nb_lit; b++){
            if(!existing_variables[f->clauses[a].vars[b].i][f->clauses[a].vars[b].j][f->clauses[a].vars[b].k]){
                existing_variables[f->clauses[a].vars[b].i][f->clauses[a].vars[b].j][f->clauses[a].vars[b].k] = true ;
                n++ ;
            }
        }
    }
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            free(existing_variables[i][j]);
        }
        free(existing_variables[i]);
    }
    free(existing_variables);
    for(int i = 0; i<m; i++){
        free_clause(f->clauses[i]);
    }
    free(f->clauses);
    free(f);
    assert(n>0);
    return (1.*m)/n;
}