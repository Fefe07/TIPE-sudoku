int assess_nb_clues(int** grid){

    int n = 0 ;
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            if(grid[i][j]>0){
                n++ ;
            }
        }
    }
    return n ;
}