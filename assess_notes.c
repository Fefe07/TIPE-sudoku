#include<stdbool.h>


bool*** initialize_notes(int** grid) ;

int assess_nb_notes(int** grid){
    bool*** notes = initialize_notes(grid);

    int count = 0 ;
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            for(int k = 0; k<9; k++){
                if(notes[i][j][k]){
                    count++;
                }
            }
        }
    }
    return count ;

}