// #include <assert.h>
// #include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// typedef struct grid_s {
// 	int** grid ;
// 	bool*** notes ;
// 	float* nb_techniques;
// }grid_s ;

// bool nakedSingle_one_cell(int** grid, bool*** notes, int i, int j, float* nb_tech);

// bool hiddenSingle_one_cell(int** grid, bool*** notes, int i, int j, int k, float* nb_tech);

// bool nakedPair_one_cell_value(int** grid, bool ***notes, int i, int j, int k, float* nb_tech);

// bool pointingPair_one_zone_one_value(bool*** notes, int z, int value);
// bool lastFreeCell_one_cell(int** grid, bool*** notes, int i, int j, float* nb_tech);

// float* consequences_removed_note(grid_t g, int i, int j, int k){

//     float* modifs = malloc(13*sizeof(float));
//     assert(modifs!=NULL);
//     for(int t = 0; t<13; t++){
//         modifs[t] = 0;
//     }

    

    
//     //printf("consequence_removed_note : i = %d , j = %d, value = %d\n", i, j, k+1);
//     // nakedSingle
//     //printf("On teste le nakedSingle\n");
    
//     if(g->nb_techniques[2]>0.01){
//         int nb_pos = hiddenSingle_one_cell(grid, notes, i, j, k, nb_techniques);
//         //nb_tech[1] ++;
//         modifs[2] += nb_pos/9. * 1./81. ;
//     }
//     if(g->nb_techniques[1] > 0.01 && nakedSingle_one_cell(grid, notes, i, j, nb_techniques)){
//         modifs[1] += 1./81. ;
        
//     }
//     //printf("On teste le hiddenSingle\n");
//     if(g->nb_techniques[3] > 0.01 && nakedPair_one_cell_value(grid, notes, i, j, k, nb_techniques)){
//         modifs[3] += 1./81. ;
//     }
    
//     if(g->nb_techniques[5] > 0.01 && pointingPair_one_zone_one_value(notes, 3*(i/3) + j/3, k)){
//          modifs[5] += 1./81. ;
//     } 
//     return modifs ;
// }