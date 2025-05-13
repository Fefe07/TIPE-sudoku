#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

struct k_cnf_s {
    int m ; //nb_clauses
    int k ; 
    clause* clauses ;
};
typedef struct k_cnf_s* k_cnf; 

void free_clause(clause c);
void print_var(var v);
void print_k_cnf(k_cnf f);


bool egal_vars(var v1, var v2){
    return (v1.i == v2.i)&&(v1.j == v2.j) && (v1.k == v2.k);
}

var heuristique_0(k_cnf f){
    var v = {.i=0, .j=0, .k=0} ;
    return v ;
}

void substitue(var v, bool b, k_cnf f){
    /* Met la variable v à la valeur b dans f */
    /* Si c est une clause de f et v la i-ème variable de c, */
    /* Alors c est supprimée si c.positif[i] == b */
    /* Et v est retirée sinon */

    for(int c = 0; c<f->m; c++){
        for(int i = 0; i<f->clauses[c].nb_lit; i++){
            if(egal_vars(v,f->clauses[c].vars[i])){
                if(f->clauses[c].positif[i]==b){
                    free_clause(f->clauses[c]);
                    if(c<f->m-1){
                        f->clauses[c] = f->clauses[f->m-1];
                    }
                    f->m -- ;
                    c-- ;
                    break ;
                }
                else{
                    if(i<f->clauses[c].nb_lit-1){
                        f->clauses[c].vars[i] = f->clauses[c].vars[f->clauses[c].nb_lit-1];
                        f->clauses[c].positif[i] = f->clauses[c].positif[f->clauses[c].nb_lit-1];
                    }
                    f->clauses[c].nb_lit -- ;
                    i-- ;

                }
            }
        }
    }
}

bool quine(k_cnf f){
    /* Effectue Quine sur f */
    /* Renvoie true ET modifie f si une clause à un élément est trouvée */
    bool found = false ;
    for(int c = 0; c<f->m; c++){
        if(f->clauses[c].nb_lit == 1){
            substitue(f->clauses[c].vars[0], f->clauses[c].positif[0],f);
            found = true ;
            break ;
        }
        else if(f->clauses[c].nb_lit == 0){
            printf("Formule insatisfiable\n");
            assert(42==69);
        }
    }
    return found ;
}

bool*** copy_notes(bool*** notes){
    bool*** t = malloc(9*sizeof(bool**));
    assert(t!=NULL);
    for(int i = 0; i<9; i++){
        t[i] = malloc(9*sizeof(bool*));
        assert(t[i]!=NULL);
        for(int j = 0; j<9; j++){
            t[i][j] = malloc(9*sizeof(bool));
            assert(t[i][j]!=NULL);
            for(int k = 0; k<9; k++){
                t[i][j][k] = notes[i][j][k];
            }
        }
    }
    return t;
}

k_cnf k_cnf_copy(k_cnf f){
    k_cnf g = malloc(sizeof(struct k_cnf_s));
    assert(g!=NULL);
    g->m = f->m ;
    g->k = f->k ;
    for(int c = 0; c<f->m; c++){
        clause c2 ;
        c2.nb_lit = f->clauses[c].nb_lit ;
        c2.vars = malloc(c2.nb_lit*sizeof(var));
        assert(c2.vars!=NULL);
        c2.positif = malloc(c2.nb_lit*sizeof(bool));
        assert(c2.positif!=NULL);
        for(int i = 0; i<c2.nb_lit;i++){
            c2.vars[i] = f->clauses[c].vars[i];
            c2.positif[i] = f->clauses[c].positif[i];
        }
        g->clauses[c] = c2 ;
    }
    return g;
}

void solve_cnf(k_cnf f, int** grid, var(*h)(k_cnf)){
    /* Résout la formule de logique propositionelle f associée à la grille grid */
    /* Avec l'algortihme de Quine */
    /* L'heuristique utilisée est passée en argument*/

    while(true){
        if(f->m == 0){
            break ;
        }
        bool found = quine(f);
        if(!found){
            /* Heuristique passée en argument, trouve la variable pour la disjonction */
            var v = h(f);

            k_cnf f_true = k_cnf_copy(f);
            k_cnf f_false = k_cnf_copy(f);

            /* Et là, on déroule les deux en même temps et on cherche les similitudes */
            /* En dérouler un seul reproduirait un vrai backtracking (même humain), */
            /* alors que dérouler les deux d'un coup jusqu'à trouver une similitude */
            /* ou une contradiction imite les raisonnements humains */



        }
    }
}