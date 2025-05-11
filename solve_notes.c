#include <assert.h>
#include <stdbool.h>


bool lastFreeCell(int** grid, bool ***notes, float* nb_techniques);
bool hiddenSingle(int **grid, bool ***notes, float* nb_techniques);
bool nakedSingle(int **grid, bool ***notes, float* nb_techniques);

bool nakedPair(bool ***notes);
bool nakedTriple(bool ***notes);
bool hiddenPair(bool ***notes);
bool hiddenTriple(bool ***notes);
bool pointingPair(bool ***notes);
bool boxLineReduction(bool ***notes);
bool x_wing(bool ***notes);
bool y_wing(bool ***notes);
bool swordfish(bool ***notes);

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


bool solve_notes(int **grid, bool ***notes, float* nb_techniques) {

  bool ok = true;
  
  // teste successivement les techniques, dans l'ordre croissant des difficultés
  while (ok) {
    if(!est_ok(grid)){
      return false;
    }
    // easy
    //printf("SolveNotes\n");
    ok = lastFreeCell(grid, notes, nb_techniques);
    //ok = false ;
    if(!ok){
      int nb_pos = hiddenSingle(grid, notes, nb_techniques);
      ok = (nb_pos >= 1);
      if (!ok) {
        ok = nakedSingle(grid, notes, nb_techniques);
        if (!ok) {
          // medium
           
          ok = nakedPair(notes);
          if (!ok) {
            // printf("coucou4\n");
            // fflush(stdout);
            ok = nakedTriple(notes);
            
            if (!ok) {
              // printf("coucou5\n");
              // fflush(stdout);
              
              ok = pointingPair(notes);
              
              if (!ok) {
                // printf("coucou6\n");
                // fflush(stdout);
                
                ok = boxLineReduction(notes);
                
                if (!ok) {
                  // printf("coucou7\n");
                  // fflush(stdout);
                  ok = hiddenPair(notes);
                  if (!ok) {
                    // printf("coucou8\n");
                    // fflush(stdout);
                    ok = hiddenTriple(notes);
                    if (!ok) {
                      // printf("coucou9\n");
                      // fflush(stdout);
                      ok = x_wing(notes);
                      // printf("coucou10\n");
                      // fflush(stdout);
                      if(!ok){
                        ok = y_wing(notes);
                        if(!ok){
                          ok = swordfish(notes);
                          if(ok){
                            nb_techniques[11] ++ ;
                          }
                        }
                        else{
                          nb_techniques[10] ++ ;
                        }
                      }
                      else{
                        nb_techniques[9]++ ;
                      }
                    }
                    else {
                      nb_techniques[8]++;
                    }
                  } else {
                    nb_techniques[7]++;
                  }
                } else {
                  nb_techniques[6]++;
                }
              } else {
                nb_techniques[5]++;
              }
            } else {
              nb_techniques[4]++;
            }
          } else {
            nb_techniques[3]++;
          }
        } else {
          nb_techniques[1]++;
        }
      } else {
        /* Le décalage d'indices vient d'une revue de l'aordre de difficulté des techniques */
        nb_techniques[2]+= nb_pos/9.;
      }
    }
    else{
      nb_techniques[0]++;
      
      
    }
  }
  // print_tab(nb_techniques,10);
  //  renvoie true si la grille est finie, false sinon
  // printf("coucou42\n");
  // fflush(stdout);

  bool finished  = true ;
  for(int i = 0; i<9; i++){
    for(int j = 0; j<9; j++){
      if(grid[i][j] == 0){
        finished = false;
        
      }
    }
  }
  if(!finished){
    //printf("SolveNotes pas fini\n");
    //printGrid(grid);
  }
  
  return finished ;
  
}
