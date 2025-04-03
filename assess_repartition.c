






int assess_repartition(int** grid){

    int r = 0 ;
    for (int i = 0; i<9; i++){
        // mesure la répartition sur les lignes
        int s = 0;
        for(int j = 0; j<9; j++){
            if(grid[i][j]!=0){
                s++;
            }
        }
        /* A modifier !!!!!!!!!!!! */
        r+= s*s;
    }

    for (int j = 0; j<9; j++){
        // mesure la répartition sur les lignes
        int s = 0;
        for(int i = 0; i<9; i++){
            if(grid[i][j]!=0){
                s++;
            }
        }
        /* A modifier !!!!!!!!!!!! */
        r+= s*s;
    }
    for (int z = 0; z<9; z++){
        // mesure la répartition sur les lignes
        int s = 0;
        for(int c = 0; c<9; c++){
            int i = 3*(z/3) + c/3 ;
            int j = 3*(z%3) + c%3 ;
            if(grid[i][j]!=0){
                s++;
            }
        }
        /* A modifier !!!!!!!!!!!! */
        r+= s*s;
    }

    return r ;
}