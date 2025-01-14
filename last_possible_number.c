#include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <stdbool.h>
#include <time.h>

bool same_zone(int row, int col, int i, int j);

bool lastPossibleNumber(int** grid){
    // Entrée : une grille ( tableau de 9*9 entiers)
    // Sortie : la grille modifiée sur une unique case si c'est possible avec cette technique et true , false sinon
    int nPossibilities = 9 ; // compteur
    int sum = 45 ; // pour faire le décompte, ça m'évite de devoir chercher l'indice restant à nouveau
    for(int row = 0; row<9; row++){ 
        for(int col = 0; col<9; col++){// je parcours la grille
            if (grid[row][col]==0){ // si la case est vide :
                bool possibilities[9] = {true,true,true,true,true,true,true,true,true}; // tableau des valeurs possibles
                nPossibilities = 9 ;
                sum = 45 ;
                for(int i = 0; i<9; i++){  //parcours sur les lignes
                    for(int j = 0; j<9; j++){ //parcours sur les colonnes 
                        if (grid[i][j] != 0 && (i!=row || col != j) && same_zone(row, col, i, j)){ 
                            if (possibilities[grid[i][j]-1]){ // Rien à faire si la valeur est déjà impossible !
                                possibilities[grid[i][j]-1] = false ;
                                nPossibilities--;
                                sum -= grid[i][j];
                            }
                        }
                    }
                }
                if (nPossibilities == 1 ){ // si il ne me reste qu'une seule possibilité
                    grid[row][col]=sum; // sum vaut alors la seule valeur restante
                    //printf("Technique : last Possible Number\n");
                    //printf("row = %d, col = %d, val = %d\n", row, col, sum); //tests
                    // assert(check(grid, row, col)); // au cas où la grille serait mauvaise (je ne sais pas si c'est nécéssaire)
                    // retiré pour gagner du temps !
                    return true ;
                }
            }
        }
    }
    return false ; // pas trouvé !
}