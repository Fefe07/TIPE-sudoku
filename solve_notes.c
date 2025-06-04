#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

bool lastFreeCell(grid_t g);
int hiddenSingle(grid_t g);
bool nakedSingle(grid_t g);

bool nakedPair(grid_t g);
bool nakedTriple(grid_t g);
bool hiddenPair(grid_t g);
bool hiddenTriple(grid_t g);
bool pointingPair(grid_t g);
bool boxLineReduction(grid_t g);
bool x_wing(grid_t g);
bool y_wing(grid_t g);
bool swordfish(grid_t g);

void printGrid(int **grid);
void print_tab_float(float *tab, int size);

/* Entrées : une grille, ses notes
Sortie : true si la grille a été résolue, false sinon
Effet de bord : la grille contient autant d'indices que possible,
les notes sont le plus vide possible
Remarque : la séparation de la résolution d'une grille avec le main permet à la
fois de simplifier la lecture du code, et d'utiliser le backtracking pour finir
la grille */
bool est_ok(int** grid){
  for(int i = 0; i<9; i++){
    int num[9] = {0,0,0,0,0,0,0,0,0};
    for(int j = 0; j<9; j++){
      if(grid[i][j] != 0){
        num[grid[i][j]-1] ++ ;
      }
    }
    for(int j = 0; j<9; j++){
      if(num[j]>1){
        return false ;
      }
    }
  }
  for(int j = 0; j<9; j++){
    int num[9] = {0,0,0,0,0,0,0,0,0};
    for(int i = 0; i<9; i++){
      if(grid[i][j] != 0){
        num[grid[i][j]-1] ++ ;
      }
    }
    for(int i = 0; i<9; i++){
      if(num[i]>1){
        return false ;
      }
    }
  }
  for(int z = 0; z<9; z++){
    int num[9] = {0,0,0,0,0,0,0,0,0};
    for(int c = 0; c<9; c++){
      if(grid[3*(z/3) + c/3][3*(z%3) + c%3] != 0){
        num[grid[3*(z/3) + c/3][3*(z%3) + c%3]-1] ++ ;
      }
    }
    for(int j = 0; j<9; j++){
      if(num[j]>1){
        return false ;
      }
    }
  }
  return true;
}


bool solve_notes(grid_t g, bool(**techniques)(grid_t g), int n) {

  
  
  /* techniques est un tableau de pointeurs de fonctions, qui sont les techniques de résolution (hors backtracking) */
  /* n est le nombre d'éléments de techniques */


  int i = 0 ;
  while(i<n){
    if((*(techniques[i]))(g)){
      g->nb_techniques[i] ++ ;
      i = 0;
    }
    else{
      i++;
    }
    if(!est_ok(g->grid)){
      return false;
    }
  }

  // teste successivement les techniques, dans l'ordre croissant des difficultés
  // bool ok = true ;
  // while (ok) {
  //   if(!est_ok(g->grid)){
  //     return false;
  //   }
  //   // easy
  //   //printf("SolveNotes\n");
  //   ok = lastFreeCell(g);
  //   //ok = false ;
  //   if(!ok){
  //     int nb_pos = hiddenSingle(g);
  //     ok = (nb_pos >= 1);
  //     if (!ok) {
  //       ok = nakedSingle(g);
  //       if (!ok) {
  //         // medium
           
  //         ok = nakedPair(g);
  //         if (!ok) {
  //           //printf("coucou4\n");
  //           // fflush(stdout);
  //           ok = nakedTriple(g);
            
  //           if (!ok) {
  //             //printf("coucou5\n");
  //             // fflush(stdout);
              
  //             ok = pointingPair(g);
              
  //             if (!ok) {
  //               //printf("coucou6\n");
  //               // fflush(stdout);
                
  //               ok = boxLineReduction(g);
                
  //               if (!ok) {
  //                 //printf("coucou7\n");
  //                 // fflush(stdout);
  //                 ok = hiddenPair(g);
  //                 if (!ok) {
  //                   //printf("coucou8\n");
  //                   // fflush(stdout);
  //                   ok = hiddenTriple(g);
  //                   if (!ok) {
  //                     //printf("coucou9\n");
  //                     // fflush(stdout);
  //                     ok = x_wing(g);
  //                     // //printf("coucou10\n");
  //                     // fflush(stdout);
  //                     if(!ok){
  //                       ok = y_wing(g);
  //                       if(!ok){
  //                         ok = swordfish(g);
  //                         if(ok){
  //                           g->nb_techniques[11] ++ ;
  //                         }
  //                       }
  //                       else{
  //                         g->nb_techniques[10] ++ ;
  //                       }
  //                     }
  //                     else{
  //                       g->nb_techniques[9]++ ;
  //                     }
  //                   }
  //                   else {
  //                     g->nb_techniques[8]++;
  //                   }
  //                 } else {
  //                   g->nb_techniques[7]++;
  //                 }
  //               } else {
  //                 g->nb_techniques[6]++;
  //               }
  //             } else {
  //               g->nb_techniques[5]++;
  //             }
  //           } else {
  //             g->nb_techniques[4]++;
  //           }
  //         } else {
  //           g->nb_techniques[3]++;
  //         }
  //       } else {
  //         g->nb_techniques[1]++;
  //       }
  //     } else {
  //       /* Le décalage d'indices vient d'une revue de l'aordre de difficulté des techniques */
  //       g->nb_techniques[2]+= nb_pos/9.;
  //     }
  //   }
  //   else{
  //     g->nb_techniques[0]++;
      
      
  //   }
  // }
  // print_tab(nb_techniques,10);
  //  renvoie true si la grille est finie, false sinon
  // //printf("coucou42\n");
  // fflush(stdout);

  bool finished  = true ;
  for(int c = 0; c<81; c++){
    if(g->grid[c/9][c%9] == 0){
      finished = false;
      break ;
    }
  }

  if(!finished){
    //printf("SolveNotes pas fini\n");
    //printGrid(g->grid);
  }
  
  return finished ;
  
}
