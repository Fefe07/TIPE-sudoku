#include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <stdbool.h>
#include <time.h>


void printGrid(int** grid);

void consequences_new_number(int **grid, bool ***notes, int i, int j, float* nb_techniques);
bool est_ok(int** grid);

bool lastFreeCell(int** grid, bool ***notes, float* nb_techniques){ // OK !
    // Entrée : une grille ( tableau de 9*9 entiers)
    // Sortie : la grille modifiée sur une unique case si c'est possible avec cette technique et true , false sinon
    // Technique du LastFreeCell : si une zone possède déjà 8 indices, remplit le 9ème
    if(!est_ok(grid)){
        return false;
    }
    
    int sum ; // pour ne pas avoir besoin de rechercher la valeur manquante
    int counter ; // je compte les cases pleines
    for(int row = 0; row<9 ; row ++ ){ // test des lignes
        sum = 45 ;
        counter = 0; // compte les indices présents
        for(int col = 0; col<9; col ++){
            if (grid[row][col] != 0){
                counter ++ ;
                sum -= grid[row][col];
            }
        }
        if (counter==8){ // si 8 cases sont pleines :
            for (int col = 0; col<9; col ++ ){ // recherche l'emplacement libre 
                if(grid[row][col] == 0){ 
                    assert(sum > 0);
                    assert(sum<=9);
                    grid[row][col] = sum ; // sum vaut alors la valeur manquante
                    //printf("Technique : lastFreeCell\n");
                    //printf("row = %d, col = %d, val = %d\n", row, col, grid[row][col]);
                    consequences_new_number(grid, notes, row, col, nb_techniques);
                    return true;
                }
            }
        }
    }
    
    for(int col = 0; col<9 ; col ++ ){ //idem sur les colonnes
        sum = 45 ;
        counter = 0;
        for(int row = 0; row<9; row ++){
            if (grid[row][col] != 0){
                counter ++ ;
                sum -= grid[row][col];
            }
        }
        if (counter==8){
            for (int row = 0; row<9; row ++ ){
                if(grid[row][col] == 0){
                    assert(sum > 0);
                    assert(sum<=9);
                    grid[row][col] = sum ;
                    //printf("Technique : lastFreeCell\n");
                    //printf("row = %d, col = %d, val = %d\n", row, col, grid[row][col]);
                    consequences_new_number(grid, notes, row, col,  nb_techniques);
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
                if (grid[3*rowGroup + row] [3*colGroup + col] != 0){
                    counter ++ ;
                    sum -= grid[3*rowGroup + row] [3*colGroup + col];
                }
            }
        }
        if (counter==8){
            for(int row = 0; row <3; row ++){
                for(int col = 0; col <3; col ++){
                    if (grid[3*rowGroup + row] [3*colGroup + col] == 0){
                        assert(sum > 0);
                        assert(sum<=9);
                        grid[3*rowGroup + row] [3*colGroup + col] = sum ;
                        //printf("Technique : lastFreeCell\n");
                        //printf("row = %d, col = %d, val = %d\n", (3*rowGroup + row), (3*colGroup + col), grid[3*rowGroup + row] [3*colGroup + col]);
                        consequences_new_number(grid, notes, 3*rowGroup + row, 3*colGroup + col,  nb_techniques);
                        return true ;
                    }
                }
            }
        }

    }
    return false ;
}

bool lastFreeCell_one_cell(int** grid, bool*** notes, int i, int j, float* nb_techniques){
    //printf("LastFreeCell_one_cell\n");
    //printf("i = %d, j = %d\n", i, j);
    if(!est_ok(grid)){
        return false;
    }
    
    
    int sum ; // pour ne pas avoir besoin de rechercher la valeur manquante
    int counter ; // je compte les cases pleines
    sum = 45 ;
    counter = 0; // compte les indices présents
    for(int col = 0; col<9; col ++){
        if (grid[i][col] != 0){
            counter ++ ;
            sum -= grid[i][col];
        }
    }
    if (counter==8){ // si 8 cases sont pleines :
        for (int col = 0; col<9; col ++ ){ // recherche l'emplacement libre 
            if(grid[i][col] == 0){ 
                assert(sum > 0);
                assert(sum<=9);
                grid[i][col] = sum ; // sum vaut alors la valeur manquante
                //printf("Technique : lastFreeCell_one_cell\n");
                //printf("row = %d, col = %d, val = %d\n", i, col, grid[i][col]);
                consequences_new_number(grid, notes, i, col,  nb_techniques);
                return true;
            }
        }
    }

    sum = 45 ;
    counter = 0;
    for(int row = 0; row<9; row ++){
        if (grid[row][j] != 0){
            counter ++ ;
            sum -= grid[row][j];
        }
    }
    if (counter==8){
        for (int row = 0; row<9; row ++ ){
            if(grid[row][j] == 0){
                assert(sum > 0);
                assert(sum<=9);
                grid[row][j] = sum ;
                //printf("Technique : lastFreeCell_one_cell\n");
                //printf("row = %d, col = %d, val = %d\n", row, j, grid[row][j]);
                consequences_new_number(grid, notes, row, j, nb_techniques);
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
            if (grid[3*rowGroup + row] [3*colGroup + col] != 0){
                counter ++ ;
                sum -= grid[3*rowGroup + row] [3*colGroup + col];
            }
        }
    }
    if (counter==8){
        for(int row = 0; row <3; row ++){
            for(int col = 0; col <3; col ++){
                if (grid[3*rowGroup + row] [3*colGroup + col] == 0){
                    assert(sum > 0);
                    assert(sum<=9);
                    grid[3*rowGroup + row] [3*colGroup + col] = sum ;
                    //printf("Technique : lastFreeCell_one_cell\n");
                    //printf("row = %d, col = %d, val = %d\n", (3*rowGroup + row), (3*colGroup + col), grid[3*rowGroup + row] [3*colGroup + col]);
                    consequences_new_number(grid, notes, 3*rowGroup + row, 3*colGroup + col, nb_techniques);
                    return true ;
                }
            }
        }
    }
    return false ;
}