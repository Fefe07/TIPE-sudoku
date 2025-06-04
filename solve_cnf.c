#include <assert.h>
#include <bits/types/stack_t.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

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


/* Implémente les ensembles de litéraux */
/* Je pourrais faire des arbres rouge-noir. Je pourrais */
struct lit_set_s {
    var v ;
    bool positif ;
    struct lit_set_s* next ;
};
typedef struct lit_set_s* lit_set ;


// struct maillon_s {
//     k_cnf f ;
//     lit_set* lsptr1 ;
//     lit_set* lsptr2 ;
//     bool val ; //suivant la valeur prise dans la disjonction précédente
//     /* Le suivant dans la file ; vaut NULL pour la queue de file*/
//     struct maillon_s* next ;
//     /* Vaut NULL pour la tête de file */
//     struct maillon_s* prec ;
// } ;
// typedef struct maillon_s* maillon ;

// struct queue_s {
//     maillon head ;
//     maillon tail ;
// };
// typedef struct queue_s* queue ;


void free_clause(clause c);
void print_var(var v);
void print_clause(clause c);
void print_k_cnf(k_cnf f);

void free_k_cnf(k_cnf f){
    for(int a = 0; a<f->m ; a++){
        free_clause(f->clauses[a]);
    }
    free(f->clauses);
    free(f);
}

/* queue queue_create(){
    queue q = malloc(sizeof(struct queue_s));
    assert(q!=NULL);
    q->head = NULL ;
    q->tail = NULL ;
    return q ;
}

void queue_push(queue q, k_cnf f, lit_set* ls_ptr1, lit_set* ls_ptr2, bool b){
    maillon m = malloc(sizeof(struct maillon_s));
    assert(m!=NULL);
    m->f = f ;
    m->lsptr1 = ls_ptr1 ;
    m->lsptr2 = ls_ptr2 ;
    m->val = b ;
    m-> next = NULL ;
    m->prec = q->tail ;
    if(q->tail!=NULL){
        q->tail->next = m ;
    }
    else{
        q->head = m ;
    }
    q->tail = m ;
}

maillon queue_pop(queue q){
    assert(q->head !=NULL);
    maillon m = q->head ;
    q->head = q->head->next ;
    if(q->head!=NULL){
        q->head->prec = NULL ;
    }
    else{
        q->tail = NULL ;
    }
    
    return m ;
}

bool queue_is_empty(queue q){
    if(q->head == NULL){
        assert(q->tail==NULL);
        return true ;
    }
    else{
        return false;
    }
}



void free_empty_queue(queue q){
    assert(queue_is_empty(q));
    free(q);
}
*/

bool egal_vars(var v1, var v2){
    return (v1.i == v2.i)&&(v1.j == v2.j) && (v1.k == v2.k);
}


void ls_print(lit_set ls){
    if(ls!=NULL){
        printf("i = %d, j = %d, k = %d, b = %d\n", ls->v.i, ls->v.j, ls->v.k, ls->positif);
        ls_print(ls->next);
    }
}

bool ls_mem(var v, bool b, lit_set ls){ //ok
    return ((ls!=NULL)&&((egal_vars(v,ls->v) && b == ls->positif)|| ls_mem(v, b,ls->next)));
}

void ls_union(lit_set ls1, lit_set ls2){
    /* Fait l'union de ls1 et ls2 */
    /* *ls1 est modifié pour contenir cette union */
    /* ls2 n'est pas libéré ni altéré */

    /* ATTENTION : NE FONCTIONNE PAS SI ls1==NULL */
    //printf("Union\n");

    assert(ls1!=NULL);

    if(ls2!=NULL){
        if(ls_mem(ls2->v,ls2->positif,ls1)){ 
            ls_union(ls1, ls2->next);
        }
        else{
            //printf("ls1 =  ");
            //ls_print(ls1);
            

            lit_set ls = malloc(sizeof(struct lit_set_s));
            assert(ls!=NULL);
            *ls = *ls1 ;
            ls1->next = ls ;
            ls1->positif = ls2->positif;
            ls1->v = ls2->v ;

            //printf("ls1 =  ");
            //ls_print(ls1);
            ls_union(ls1, ls2->next);
        }
    }
}

lit_set ls_singleton(var v, bool positif){
    lit_set ls = malloc(sizeof(struct lit_set_s));
    assert(ls!=NULL);
    ls->v = v;
    ls->positif = positif ;
    ls->next = NULL ;
    return ls ;
}



void ls_free(lit_set ls){
    if(ls!=NULL){
        ls_free(ls->next);
        free(ls);
    }
}


bool ls_is_empty(lit_set ls){
    return ls == NULL ;
}

lit_set ls_inter(lit_set ls1, lit_set ls2){
    /* Fait l'intersection de ls1 et ls2 */
    //printf("Inter\n");
    if(ls2!=NULL){
        if(ls_mem(ls2->v,ls2->positif,ls1)){ 
            lit_set sing = ls_singleton(ls2->v, ls2->positif);
            lit_set inter = ls_inter(ls1,ls2->next);
            if(inter!=NULL){
                ls_union(inter,sing);
                ls_free(sing);
                return inter ;
            }
            else{
                return sing;
            }
        }
        else{
            return ls_inter(ls1,ls2->next);
        }
    }
    else{
        return NULL ;
    }
}


var heuristique_0(k_cnf f){

    /* Choisit une variable uniformément dans la cnf */
    /* Les variables plus présentes ont plus de chances d'être choisies */

    assert(f->m>0);
    int nb_vars_vues = 0;
    var v_choisie ;
    for(int c = 0; c<f->m; c++){
        /* On cherche les clauses à valeurs positives !*/
        for(int i = 0; i<f->clauses[c].nb_lit; i++){
            nb_vars_vues ++ ;
            if (rand()%nb_vars_vues==0){
                v_choisie = f->clauses[c].vars[i];
            }
        }
    }

    return v_choisie;

}


// var heuristique_1(k_cnf f){

//     /* Donne la première variable de la plus petite clause à valeurs positives */

//     assert(f->m>0);
//     int nb_lit_min = 42; 
//     clause c_min ;
//     for(int c = 0; c<f->m; c++){
//         /* On cherche les clauses à valeurs positives !*/
//         if(f->clauses[c].nb_lit<nb_lit_min && f->clauses[c].positif[0]){
//             nb_lit_min = f->clauses[c].nb_lit ;
//             c_min = f->clauses[c] ;
//         }
//     }
//     assert(nb_lit_min>1); // sinon on n'appelerait pas h
//     return c_min.vars[0];
// }

/* On cherche ici la variable qui aurait le plus d'impact */
    /* La variable est présente en positif sur exactement quatre clauses (ligne, colonne, bloc, case) 
    (en effet, si on a résolu une de ces clauses, alors on sait ou placer le chiffre dans cette zone) */
    /* La présence de la variable négative dépend de la taille de ces zones */
    /* Du fait de l'exploration parallèle des deux cas, l'approche visant à maximiser le nombre d'occurences
    du litéral négatif est contre-intuitive, il s'agit plutôt de maximiser son impact à l'aide d'une petite clause */
    /* On va donc simplement affiner l'heuristique précédente */
var heuristique_1(k_cnf f){
    u_int8_t* count = malloc(2*9*9*9*sizeof(u_int8_t));
    assert(count!=NULL);
    for(int i = 0; i<1458; i++){
        count[i]=0;
    }
    for(int c = 0; c<f->m; c++){
        clause cl = f->clauses[c] ;
        for(int i = 0; i<cl.nb_lit; i++){
            int indice = cl.vars[i].i + 9*cl.vars[i].j + 81*cl.vars[i].k ;
            if(cl.positif[i]){
                indice+=729 ;
            }
            count[indice]++;
        }
    }
    for(int i = 730; i<1458; i++){
        assert(count[i]==0 || count[i]==4);
    }

    assert(f->m>0);
    int nb_lit_min = 42; 
    var best_var ;
    for(int c = 0; c<f->m; c++){
        /* On cherche les clauses à valeurs positives !*/
        for(int i = 0; i<f->clauses[c].nb_lit; i++){
            if(f->clauses[c].positif[i]&&(f->clauses[c].nb_lit<nb_lit_min || (f->clauses[c].nb_lit==nb_lit_min && count[f->clauses[c].vars[i].i + 9*f->clauses[c].vars[i].j + 81* f->clauses[c].vars[i].k] < count[best_var.i + 9*best_var.j + 81*best_var.k]))){
                nb_lit_min = f->clauses[c].nb_lit ;
                best_var = f->clauses[c].vars[i] ;
            }
        }
    }
    assert(nb_lit_min>1); // sinon on n'appelerait pas h
    free(count);
    return best_var;
}


var heuristique_2(k_cnf f){
    u_int8_t* count = malloc(2*9*9*9*sizeof(u_int8_t));
    assert(count!=NULL);
    for(int i = 0; i<1458; i++){
        count[i]=0;
    }
    for(int c = 0; c<f->m; c++){
        clause cl = f->clauses[c] ;
        for(int i = 0; i<cl.nb_lit; i++){
            int indice = cl.vars[i].i + 9*cl.vars[i].j + 81*cl.vars[i].k ;
            if(cl.positif[i]){
                indice+=729 ;
            }
            count[indice]++;
        }
    }
    for(int i = 730; i<1458; i++){
        assert(count[i]==0 || count[i]==4);
    }

    assert(f->m>0);
    int nb_lit_max = 42; 
    var best_var ;
    for(int c = 0; c<f->m; c++){
        /* On cherche les clauses à valeurs positives !*/
        for(int i = 0; i<f->clauses[c].nb_lit; i++){
            if(f->clauses[c].positif[i]&&(f->clauses[c].nb_lit<nb_lit_max || (f->clauses[c].nb_lit==nb_lit_max && count[f->clauses[c].vars[i].i + 9*f->clauses[c].vars[i].j + 81* f->clauses[c].vars[i].k] > count[best_var.i + 9*best_var.j + 81*best_var.k]))){
                nb_lit_max = f->clauses[c].nb_lit ;
                best_var = f->clauses[c].vars[i] ;
            }
        }
    }
    assert(nb_lit_max<=9); // sinon on n'appelerait pas h
    free(count);
    return best_var;
}

void substitue(var v, bool b, k_cnf f){
    /* Met la variable v à la valeur b dans f */
    /* Si c est une clause de f et v la i-ème variable de c, */
    /* Alors c est supprimée si c.positif[i] == b */
    /* Et v est retirée sinon */


    //printf("Subitute :");
    print_var(v) ;
    //printf(", b= %d\n",b);


    for(int c = 0; c<f->m; c++){
        for(int i = 0; i<f->clauses[c].nb_lit; i++){
            if(egal_vars(v,f->clauses[c].vars[i])){
                if(f->clauses[c].positif[i]==b){
                    // for(int i = 0; i<f->clauses[c].nb_lit; i++){
                    //     ls_union(ls, ls_singleton(f->clauses[c].vars[i]));
                    //     /* Merde il faut la positivité aussi */
                    // }
                    //printf("On supprime une clause\n");
                    free_clause(f->clauses[c]);
                    if(c<f->m-1){
                        f->clauses[c] = f->clauses[f->m-1];
                    }
                    f->m -- ;
                    c-- ;
                    break ;
                }
                else{
                    //printf("On supprime une occurence d'une variable\n");
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

lit_set* quine(k_cnf f){ //ok
    /* Effectue une itération de Quine sur f */
    /* Modifie f au passage */
    /* Renvoie un singleton contenant la variable si une variable est trouvée */
    /* Renvoie un pointeur sur l'ensemble vide si aucune variable est trouvée */
    /* Renvoie NULL si la formule est insatisfiable car une clause est vide */
    
    //printf("########### Quine : ############\n");
    for(int c = 0; c<f->m; c++){
        //printf("%d   ", f->clauses[c].nb_lit);
        print_clause(f->clauses[c]);
        if(f->clauses[c].nb_lit == 1){
            lit_set* found = malloc(sizeof(lit_set));
            assert(found!=NULL);
            //printf("Clause à un littéral trouvée : i = %d, j = %d, k = %d, b = %d\n", f->clauses[c].vars[0].i,f->clauses[c].vars[0].j, f->clauses[c].vars[0].k, f->clauses[c].positif[0]);
            *found = ls_singleton(f->clauses[c].vars[0], f->clauses[c].positif[0]);
            substitue(f->clauses[c].vars[0], f->clauses[c].positif[0],f);
            return found ;
        }
        else if(f->clauses[c].nb_lit == 0){
            //printf("Formule insatisfiable\n");
            
            return NULL ;
        }
    }
    lit_set* found = malloc(sizeof(lit_set));
    assert(found!=NULL);
    *found = NULL ;
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
    //printf("Begin k_cnf_copy\n");
    k_cnf g = malloc(sizeof(struct k_cnf_s));
    assert(g!=NULL);
    g->m = f->m ;
    g->k = f->k ;
    g->clauses = malloc(g->m * sizeof(clause));
    assert(g->clauses!=NULL);
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



// void solve_cnf_aux(k_cnf f, lit_set* ls_ptr1, lit_set* ls_ptr2, queue q, var(*h)(k_cnf), int* nb_disjonctions, int* nb_quines, int profondeur){
//     /* Effectue l'opération élémentaire associée à la formule f  */
//     /* Les variables trouvées sont mises dans modified_t */
//     /* Si modified_t inter modified_f est non vide, on s 'arrête */
//     /* Le booléen finished_quine sert à gérer les déséquilibres dans le nombre de quines possibles */


//     //printf("Solve_cnf_aux\n");

//     /* On ne continue pas si on a trouvé quelque chose */
    

// }


lit_set disjonction(k_cnf f, var(*h)(k_cnf), int* nb_disjonctions, int* nb_quines, int profondeur){
    /* Résout la formule de logique propositionelle f associée à la grille grid */
    /* Avec l'algortihme de Quine */
    /* L'heuristique utilisée est passée en argument*/
    /* Renvoie l'ensemble des litéraux communes (qui sont donc nécéssairement vrais)*/

    //printf("Disjonction !\n");
    if(profondeur<3){
        printf("profondeur = %d,  m = %d\n",profondeur, f->m);
    }
    nb_disjonctions[profondeur]++;



    //printf("File créée\n");
    /* Heuristique passée en argument, trouve la variable pour la disjonction */
    var v = h(f);
    //printf("Variable trouvée\n");

    k_cnf f_true = k_cnf_copy(f);
    k_cnf f_false = k_cnf_copy(f);

    lit_set modified_t = ls_singleton(v, true);
    substitue(v, true, f_true);

    lit_set modified_f =  ls_singleton(v,false);
    substitue(v, false, f_false);


    
    bool finished_quine_t = false ;

    bool finished_quine_f = false ;
    //printf("Coucou\n");

    lit_set inter = ls_inter(modified_t, modified_f);
    while( ls_is_empty(inter)){

        if(!finished_quine_t){
            if(f_true->m == 0){
                for(lit_set c = modified_t; c !=NULL; c = c->next){
                    substitue(c->v, c->positif, f);
                }
                ls_free(modified_f);
                free_k_cnf(f_false);
                free_k_cnf(f_true);
                return modified_t ;
            }

            lit_set* found = quine(f_true);
            nb_quines[profondeur+1]++;
            

            /* Si la clause est satisfiable, on continue*/
            if(found!=NULL){
                if(*found == NULL){
                    free(found) ;
                    finished_quine_t = true ;
                }
                else{
                    //printf("Coucou\n");
                    // Par construction, modified_t!=NULL
                    ls_union(modified_t, *found);
                    //printf("Coucou\n");
                    ls_free(*found);
                    free(found);
                }
                
            }
            else{
                /* Attention, ce qu'on va faire n'a aucun sens, mais permet de "valider" l'autre clause (puisque celle-là est fausse)*/
                /* N.B. On ne dit pas que l'autre clause est forcément satisfiable, juste que si la clause mère est satisfiable, alors l'autre l'est aussi*/
                //printf("La formule est insatisfiable d'après Quine\n");
                assert(modified_f!=NULL);
                //printf("modified_t = \n");
                //ls_print(modified_t);
                //printf("modified_f = \n");
                //ls_print(modified_f);
                assert(modified_t!=NULL);
                ls_union(modified_t, modified_f);
                //printf("modified_t = \n");
                //ls_print(modified_t);
                //printf("modified_f = \n");
                //ls_print(modified_f);
                lit_set inter = ls_inter(modified_f,modified_t);
                assert(inter!=NULL);
                ls_free(inter);
            }
        }
        else if(!finished_quine_f){
            if(f_false->m == 0){
                for(lit_set c = modified_f; c !=NULL; c = c->next){
                    substitue(c->v, c->positif, f);
                }
                ls_free(modified_t);
                free_k_cnf(f_false);
                free_k_cnf(f_true);
                return modified_f ;
            }

            lit_set* found = quine(f_false);
            nb_quines[profondeur+1]++;
            

            /* Si la clause est satisfiable, on continue*/
            if(found!=NULL){
                if(*found == NULL){
                    free(found) ;
                    finished_quine_f = true ;
                }
                else{
                    //printf("Coucou3\n");
                    ls_union(modified_f, *found);
                    
                    ls_free(*found);
                    free(found);
                }
                
            }
            else{
                /* Attention, ce qu'on va faire n'a aucun sens, mais permet de "valider" l'autre clause (puisque celle-là est fausse)*/
                /* N.B. On ne dit pas que l'autre clause est forcément satisfiable, juste que si la clause mère est satisfiable, alors l'autre l'est aussi*/
                //printf("La formule est insatisfiable d'après Quine\n");
                //printf("Coucou4\n");
                ls_union(modified_f, modified_t);
                
            }
                
            
        }

        else{

            if(rand()%2 == 0){

                lit_set ls = disjonction(f_true,h, nb_disjonctions, nb_quines, profondeur+1);
                //ls_print(ls);
                if(!ls_is_empty(ls)){
                    //printf("ls est non vide\n");
                    //printf("Coucou5\n");
                    ls_union(modified_t, ls);
                    ls_free(ls);
                    
                }
                else{
                    /* Alors f est nécéssairement insatisfiable*/
                    for(lit_set c = modified_f; c !=NULL; c = c->next){
                        substitue(c->v, c->positif, f);
                    }
                    ls_free(ls);
                    ls_free(modified_t);
                    free_k_cnf(f_false);
                    free_k_cnf(f_true);
                    return modified_f ;
                }

                finished_quine_t = false;
            }
            else{
                lit_set ls = disjonction(f_false,h, nb_disjonctions, nb_quines, profondeur+1);
                //ls_print(ls);
                if(!ls_is_empty(ls)){
                    //printf("ls est non vide\n");
                    //printf("Coucou6\n");
                    ls_union(modified_f, ls);
                    ls_free(ls);
                    
                }
                else{
                    /* Alors f est nécéssairement insatisfiable*/
                    for(lit_set c = modified_t; c !=NULL; c = c->next){
                        substitue(c->v, c->positif, f);
                    }
                    ls_free(ls);
                    ls_free(modified_f);
                    free_k_cnf(f_false);
                    free_k_cnf(f_true);
                    return modified_t ;
                }

                finished_quine_f = false;
            }
        }

        lit_set temp = inter ;
        inter = ls_inter(modified_t, modified_f);
        ls_free(temp);
    }


    //printf("ls = \n");
    //ls_print(ls);
    assert(inter != NULL);
    for(lit_set c = inter; c !=NULL; c = c->next){
        substitue(c->v, c->positif, f);
    }

    
    ls_free(modified_f);
    ls_free(modified_t);
    free_k_cnf(f_false);
    free_k_cnf(f_true);

    return inter ;

}



void solve_cnf(k_cnf f, var(*h)(k_cnf), int* nb_disjonctions, int* nb_quines){
    /* Fonctionne sans disjonction ! */

    /* nb_disjonctions contient le nombre de disjonction à chaque profondeur */
    /* nb_quines contient le nombre de quines à chaque profondeur*/

    

    while(f->m>0){
        //printf(" m = %d\n", f->m);

        lit_set* found = quine(f) ;

        nb_quines[0]++ ;
        print_k_cnf(f);
        if(found==NULL){
            
            //printf("La formule initiale est insatisfiable !\n");
            fflush(stdout);
            assert(42==69);
        }
        else{
            if(ls_is_empty(*found)){

                lit_set ls = disjonction(f, h, nb_disjonctions, nb_quines, 0);

                //printf (" ls = \n");
                //ls_print(ls);
                ls_free(ls);
                print_k_cnf(f);
            }
            else{
                ls_free(*found);
            }
            free(found);
            
        }
    }

}


/* Questions : */
// - Faut-il compter/différencier les quines vrais et faux ? 
// (les quines faux sont des applications de règles)