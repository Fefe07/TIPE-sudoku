# include <assert.h>
# include <stdbool.h>
#include<stdio.h>

struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

bool same_zone(int row, int col, int i, int j);

bool lastPossibleNumber(grid_t g){
    // Entrée : une grille ( tableau de 9*9 entiers)
    // Sortie : la grille modifiée sur une unique case si c'est possible avec cette technique et true , false sinon
    int nPossibilities = 9 ; // compteur
    int sum = 45 ; // pour faire le décompte, ça m'évite de devoir chercher l'indice restant à nouveau
    for(int row = 0; row<9; row++){ 
        for(int col = 0; col<9; col++){// je parcours la grille
            if (g->grid[row][col]==0){ // si la case est vide :
                bool possibilities[9] = {true,true,true,true,true,true,true,true,true}; // tableau des valeurs possibles
                nPossibilities = 9 ;
                sum = 45 ;
                for(int i = 0; i<9; i++){  //parcours sur les lignes
                    for(int j = 0; j<9; j++){ //parcours sur les colonnes 
                        if (g->grid[i][j] != 0 && (i!=row || col != j) && same_zone(row, col, i, j)){ 
                            if (possibilities[g->grid[i][j]-1]){ // Rien à faire si la valeur est déjà impossible !
                                possibilities[g->grid[i][j]-1] = false ;
                                nPossibilities--;
                                sum -= g->grid[i][j];
                            }
                        }
                    }
                }
                if (nPossibilities == 1 ){ // si il ne me reste qu'une seule possibilité
                    g->grid[row][col]=sum; // sum vaut alors la seule valeur restante
                    //printf("Technique : last Possible Number\n");
                    //printf("row = %d, col = %d, val = %d\n", row, col, sum); //tests
                    return true ;
                }
            }
        }
    }
    return false ; // pas trouvé !
}