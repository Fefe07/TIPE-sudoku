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


void free_clause(clause c){
    free(c.vars);
    free(c.positif);
}

void free_clause_1in9(clause_1in9 c){
    free(c.vars);
    free(c.filtre);
}

void print_var(var v){
    printf("i = %d, j = %d, k = %d\n", v.i, v.j, v.k);
}

void print_clause(clause c){
    for(int b = 0; b<c.nb_lit;b++){
            if(c.positif[b]){
                printf("x_%d,%d,%d ", c.vars[b].i, c.vars[b].j, c.vars[b].k);
            }
            else{
                printf("not x_%d,%d,%d ", c.vars[b].i, c.vars[b].j, c.vars[b].k);
            }
            if(b<c.nb_lit-1){
                printf("or ");
            }
        }
    printf("\n");
}

void print_k_cnf(k_cnf f){
    printf("m = %d\n",f->m);
    printf("k = %d\n", f->k);
    for(int a = 0; a<f->m; a++){
        print_clause(f->clauses[a]);
    }
}


k_cnf sudoku_to_cnf(int** grid){
    /* génère une cnf à partir d'une grille de sudoku */
    /* La tactique qui consiste à encoder les règles puis les indices ne fonctionne pas
    car un sudoku plus compliqué aurait donc moins de contraintes pour le même nombre d'indices... 
    et de toute façon cela riviendrait juste à compter les indices initiaux */

    clause_1in9* clauses_1in9 = malloc(324*sizeof(clause_1in9));
    assert(clauses_1in9!=NULL);

    /* La transformation se fera donc en trois étapes : 
    1 - écriture des clauses 1-dans-9 imposées par les règles (324 au total = 81 pour les lignes, colonnes, zones et cases)
    2 - élagage de ces clauses : chaque indice donné nous permet 
        - de supprimer 4 clauses (celles ou la variable mise à vrai apparait)
        - de supprimer toutes les autres variables de la ligne, colonne, zone et tour de l'indice
        il y a au plus 28 variables à retirer des clauses restantes
    on ne considère pas que les clauses réduites à une variable forment de nouveaux indices,
    car cela correspondrait à dérouler les naked single et hidden single */
    /* Remarque : la fusion de ces deux étapes permettrait de gagner en efficacité, mais perdrait en clarté */

    /* Étape 1 :*/
    /* Cases */
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            var* vars = malloc(9*sizeof(var));
            assert(vars!=NULL);
            bool* filtre = malloc(9*sizeof(bool));
            assert(filtre!=NULL);
            for(int k = 0; k<9; k++){
                filtre[k] = true;
                var v = {.i = i, .j=j, .k=k};
                vars[k] = v;
                //print_var(vars[k]);
            }
            clause_1in9 c = {.nb_var = 9, .vars = vars, .filtre = filtre};
            clauses_1in9[9*i+j] = c;
        }
    }

    /* Lignes */
    for(int i = 0; i<9; i++){
        for(int k = 0; k<9; k++){
            var* vars = malloc(9*sizeof(var));
            assert(vars!=NULL);
            bool* filtre = malloc(9*sizeof(bool));
            assert(filtre!=NULL);
            for(int j = 0; j<9; j++){
                filtre[j] = true;
                var v = {.i = i, .j=j, .k=k};
                vars[j] = v;
                //print_var(vars[j]);
            }
            clause_1in9 c = {.nb_var = 9, .vars = vars, .filtre = filtre};
            clauses_1in9[81 + 9*i+k] = c;
        }
    }

    /* Colonnes */
    for(int j = 0; j<9; j++){
        for(int k = 0; k<9; k++){
            var* vars = malloc(9*sizeof(var));
            assert(vars!=NULL);
            bool* filtre = malloc(9*sizeof(bool));
            assert(filtre!=NULL);
            for(int i = 0; i<9; i++){
                filtre[i] = true;
                var v = {.i = i, .j=j, .k=k};
                vars[i] = v;
                //print_var(vars[i]);
            }
            clause_1in9 c = {.nb_var = 9, .vars = vars, .filtre = filtre};
            clauses_1in9[162 + 9*j+k] = c;
        }
    }

    /* Zones */
    for(int z = 0; z<9; z++){
        for(int k = 0; k<9; k++){
            var* vars = malloc(9*sizeof(var));
            assert(vars!=NULL);
            bool* filtre = malloc(9*sizeof(bool));
            assert(filtre!=NULL);
            for(int c = 0; c<9; c++){
                filtre[c] = true;
                var v = {.i = 3*(z/3)+c/3, .j=3*(z%3)+c%3, .k=k};
                vars[c] = v;
                //print_var(vars[c]);
            }
            clause_1in9 cl = {.nb_var = 9, .vars = vars, .filtre = filtre};
            clauses_1in9[243 + 9*z+k] = cl;
        }
    }


    
    /* Étape 2 : */
    bool* filtre = malloc(324*sizeof(bool));
    assert(filtre!=NULL);
    for(int i = 0; i<324; i++){
        filtre[i] = true ;
    }
    /* On ne peut pas retirer les éléments du tableau à proprement parler, donc on filtre */

    
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            if(grid[i][j]>0){
                int k = grid[i][j] -1 ;
                int z = 3*(i/3) + j/3 ;
                int c = 3*(i%3) + j%3 ;
                filtre[9*i+j] = false ;
                filtre[81 + 9*i+k] = false ;
                filtre[162 + 9*j+k] = false ;
                filtre[243 + 9*z+k] = false ;

                // on retire ces variables
                for(int k2 = 0; k2<9; k2++){
                    clauses_1in9[81 + 9*i+k2].filtre[j] = false ;
                    clauses_1in9[162 + 9*j+k2].filtre[i] = false ;
                    clauses_1in9[243 + 9*z+k2].filtre[c] = false ;
                    
                }
                for(int i2 = 0; i2<9; i2++){
                    clauses_1in9[9*i2+j].filtre[k] = false ;
                    clauses_1in9[81 + 9*i2+k].filtre[j] = false ;
                    int z2 = 3*(i2/3)+j/3 ;
                    int c2 = 3*(i2%3)+(j%3) ;
                    assert(z2<9);
                    assert(c2<9) ;
                    clauses_1in9[243 + 9*z2+k].filtre[c2] = false ;
                }
                for(int j2 = 0; j2<9; j2++){
                    clauses_1in9[9*i+j2].filtre[k] = false ;
                    clauses_1in9[162 + 9*j2+k].filtre[i] = false ;
                    clauses_1in9[243 + 9*(3*(i/3)+j2/3)+k].filtre[3*(i%3)+j2%3] = false ;
                }
                for(int c2 = 0; c2<9; c2++){
                    int i2 = 3*(z/3)+c2/3 ;
                    int j2 = 3*(z%3)+c2%3 ;
                    clauses_1in9[9*i2+j2].filtre[k] = false ;
                    clauses_1in9[81 + 9*i2+k].filtre[j2] = false ;
                    clauses_1in9[162 + 9*j2+k].filtre[i2] = false ;
                    
                }
            }
        }
    }
    
    
    /* On crée la k_cnf */

    int m = 0; //nb_clauses
    
    // tableau pouvant stocker le nombre maximal de clauses(sudoku vide)
    // il sera redimensionné
    clause* clauses = malloc(324*37*sizeof(clause));
    assert(clauses!=NULL);

    

    for(int a = 0; a<324; a++){
        if(filtre[a]){
            int nb_lit = 0;
            for(int b = 0; b<9; b++){
                if(clauses_1in9[a].filtre[b]){
                    nb_lit++ ;
                }
            }
            // si il y a au moins une variable
            if(nb_lit >0){
                var* vars = malloc(nb_lit*sizeof(var));
                assert(vars!=NULL);
                bool* positif = malloc(nb_lit*sizeof(bool));
                assert(positif!=NULL);
                int i = 0;
                for(int b = 0; b<9; b++){
                    if(clauses_1in9[a].filtre[b]){
                        vars[i] = clauses_1in9[a].vars[b] ;
                        //print_var(vars[i]);
                        positif[i] = true ;
                        i++ ;
                    }
                }
                clause c = {.vars = vars, .nb_lit = nb_lit, .positif = positif} ;
                clauses[m] = c;
                m++;
                
                for(int i = 0; i<nb_lit; i++){
                    for(int j = 0; j<nb_lit; j++){
                        if(i<j){
                            var* vars_2 = malloc(2*sizeof(var));
                            assert(vars_2!=NULL);
                            bool* pos_2 = malloc(2*sizeof(bool));
                            assert(pos_2!=NULL);
                            vars_2[0] = vars[i];
                            vars_2[1] = vars[j];
                            pos_2[0] = false ;
                            pos_2[1] = false ;
                            clause c_2 = {.nb_lit=2, .positif=pos_2, .vars=vars_2} ;
                            clauses[m] = c_2;
                            m++ ;
                        }
                    }
                }
            }
        }
    }
    //printf("m = %d\n",m);

    clause* clauses_redimensionne = malloc(m*sizeof(clause));
    assert(clauses_redimensionne!=NULL);
    for(int i = 0; i<m; i++){
        clauses_redimensionne[i]=clauses[i];
    }

    /* Mettre des free ! */
    // for(int i = 0; i<m; i++){
    //     free_clause(clauses[i]);
    // }
    // free(clauses);
    for(int i =0; i<324; i++){
        free_clause_1in9(clauses_1in9[i]);
    }
    free(clauses_1in9);

    k_cnf f = malloc(sizeof(struct k_cnf_s));
    assert(f!=NULL);
    f->m = m;
    f->k = 9;
    f->clauses = clauses_redimensionne ;

    //print_k_cnf(f);
    return f; 
}