# include <assert.h>
# include <stdbool.h>
#include <stdio.h>

struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

void printGrid(int** grid);

//void consequences_new_number(int **grid, bool ***notes, int i, int j, float* nb_techniques);
bool est_ok(int** grid);

bool lastFreeCell(grid_t g){ // OK !
    // Entrée : une grille ( tableau de 9*9 entiers)
    // Sortie : la grille modifiée sur une unique case si c'est possible avec cette technique et true , false sinon
    // Technique du LastFreeCell : si une zone possède déjà 8 indices, remplit le 9ème
    if(!est_ok(g->grid)){
        return false;
    }
    
    int sum ; // pour ne pas avoir besoin de rechercher la valeur manquante
    int counter ; // je compte les cases pleines
    for(int row = 0; row<9 ; row ++ ){ // test des lignes
        sum = 45 ;
        counter = 0; // compte les indices présents
        for(int col = 0; col<9; col ++){
            if (g->grid[row][col] != 0){
                counter ++ ;
                sum -= g->grid[row][col];
            }
        }
        if (counter==8){ // si 8 cases sont pleines :
            for (int col = 0; col<9; col ++ ){ // recherche l'emplacement libre 
                if(g->grid[row][col] == 0){ 
                    assert(sum > 0);
                    assert(sum<=9);
                    g->grid[row][col] = sum ; // sum vaut alors la valeur manquante
                    //printf("Technique : lastFreeCell\n");
                    //printf("row = %d, col = %d, val = %d\n", row, col, g->grid[row][col]);
                    //consequences_new_number(grid, notes, row, col, nb_techniques);
                    return true;
                }
            }
        }
    }
    
    for(int col = 0; col<9 ; col ++ ){ //idem sur les colonnes
        sum = 45 ;
        counter = 0;
        for(int row = 0; row<9; row ++){
            if (g->grid[row][col] != 0){
                counter ++ ;
                sum -= g->grid[row][col];
            }
        }
        if (counter==8){
            for (int row = 0; row<9; row ++ ){
                if(g->grid[row][col] == 0){
                    assert(sum > 0);
                    assert(sum<=9);
                    g->grid[row][col] = sum ;
                    //printf("Technique : lastFreeCell\n");
                    //printf("row = %d, col = %d, val = %d\n", row, col, g->grid[row][col]);
                    //consequences_new_number(g->grid, g->notes, row, col,  g->nb_techniques);
                    return true;
                }
            }
        }
    }

    int colGroup ;
    int rowGroup ;
    for (int group = 0; group<9; group ++){//idem sur les blocs : petite complication sur les indices, mais sinon c'est identique
        sum = 45 ;
        counter = 0;
        colGroup = group % 3 ;
        rowGroup = group / 3 ;
        for(int row = 0; row <3; row++){
            for(int col = 0; col < 3; col++){
                if (g->grid[3*rowGroup + row] [3*colGroup + col] != 0){
                    counter ++ ;
                    sum -= g->grid[3*rowGroup + row] [3*colGroup + col];
                }
            }
        }
        if (counter==8){
            for(int row = 0; row <3; row ++){
                for(int col = 0; col <3; col ++){
                    if (g->grid[3*rowGroup + row] [3*colGroup + col] == 0){
                        assert(sum > 0);
                        assert(sum<=9);
                        g->grid[3*rowGroup + row] [3*colGroup + col] = sum ;
                        //printf("Technique : lastFreeCell\n");
                        //printf("row = %d, col = %d, val = %d\n", (3*rowGroup + row), (3*colGroup + col), g->grid[3*rowGroup + row] [3*colGroup + col]);
                        //consequences_new_number(g->grid, g->notes, 3*rowGroup + row, 3*colGroup + col,  g->nb_techniques);
                        return true ;
                    }
                }
            }
        }

    }
    return false ;
}

bool lastFreeCell_one_cell(grid_t g, int i, int j){
    //printf("LastFreeCell_one_cell\n");
    //printf("i = %d, j = %d\n", i, j);
    if(!est_ok(g->grid)){
        return false;
    }
    
    
    int sum ; // pour ne pas avoir besoin de rechercher la valeur manquante
    int counter ; // je compte les cases pleines
    sum = 45 ;
    counter = 0; // compte les indices présents
    for(int col = 0; col<9; col ++){
        if (g->grid[i][col] != 0){
            counter ++ ;
            sum -= g->grid[i][col];
        }
    }
    if (counter==8){ // si 8 cases sont pleines :
        for (int col = 0; col<9; col ++ ){ // recherche l'emplacement libre 
            if(g->grid[i][col] == 0){ 
                assert(sum > 0);
                assert(sum<=9);
                g->grid[i][col] = sum ; // sum vaut alors la valeur manquante
                //printf("Technique : lastFreeCell_one_cell\n");
                //printf("row = %d, col = %d, val = %d\n", i, col, g->grid[i][col]);
                //consequences_new_number(grid, notes, i, col,  nb_techniques);
                return true;
            }
        }
    }

    sum = 45 ;
    counter = 0;
    for(int row = 0; row<9; row ++){
        if (g->grid[row][j] != 0){
            counter ++ ;
            sum -= g->grid[row][j];
        }
    }
    if (counter==8){
        for (int row = 0; row<9; row ++ ){
            if(g->grid[row][j] == 0){
                assert(sum > 0);
                assert(sum<=9);
                g->grid[row][j] = sum ;
                //printf("Technique : lastFreeCell_one_cell\n");
                //printf("row = %d, col = %d, val = %d\n", row, j, g->grid[row][j]);
                //consequences_new_number(grid, notes, row, j, nb_techniques);
                return true;
            }
        }
    }


    sum = 45 ;
    counter = 0;
    int colGroup = i / 3 ;
    int rowGroup = j /3 ;
    for(int row = 0; row <3; row++){
        for(int col = 0; col < 3; col++){
            if (g->grid[3*rowGroup + row] [3*colGroup + col] != 0){
                counter ++ ;
                sum -= g->grid[3*rowGroup + row] [3*colGroup + col];
            }
        }
    }
    if (counter==8){
        for(int row = 0; row <3; row ++){
            for(int col = 0; col <3; col ++){
                if (g->grid[3*rowGroup + row] [3*colGroup + col] == 0){
                    assert(sum > 0);
                    assert(sum<=9);
                    g->grid[3*rowGroup + row] [3*colGroup + col] = sum ;
                    //printf("Technique : lastFreeCell_one_cell\n");
                    //printf("row = %d, col = %d, val = %d\n", (3*rowGroup + row), (3*colGroup + col), g->grid[3*rowGroup + row] [3*colGroup + col]);
                    //consequences_new_number(grid, notes, 3*rowGroup + row, 3*colGroup + col, nb_techniques);
                    return true ;
                }
            }
        }
    }
    return false ;
}