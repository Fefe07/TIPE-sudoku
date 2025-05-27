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

// bool nakedSingle_one_cell(int **grid, bool ***notes, int i, int j);
// float* consequences_removed_note(int **grid, bool ***notes, int i, int j, int k, float* nb_techniques);
// void updateNotes(grid_t g, int row, int col);
// void printGrid(int** grid);
// void free_notes(bool*** notes);


// bool lastFreeCell_one_cell(grid_t g, int i, int j);

// void add_float_tabs(float* tab1, float* tab2, int size){
//     for(int i = 0; i<size; i++){
//         tab1[i] += tab2[i];
//     }
// }

// void consequences_new_number(grid_t g, int i, int j) {

//     float* modifs = malloc(13 * sizeof(float));
//     assert(modifs!=NULL);
//     for(int t = 0; t<13; t++){
//         modifs[t] = 0.;
//     }
    
//     //printf("Consequences new number : i = %d, j = %d, value = %d\n", i, j, grid[i][j]);
//     printGrid(grid);

//     if(lastFreeCell_one_cell(g, i, j)){
//         g->nb_techniques[0] += 2./9. ;
//     }
//     //printf("Coucou\n");
//     int nb_notes_modified = 0;
//     bool*** newNotes = malloc(9*sizeof(bool**));
//     assert(newNotes!=NULL);
//     for(int i = 0; i<9; i++){
//         newNotes[i] = malloc(9*sizeof(bool*));
//         assert(newNotes[i]!=NULL);
//         for(int j = 0; j<9; j++){
//             newNotes[i][j] = malloc(9*sizeof(bool));
//             assert(newNotes[i][j] != NULL);
//             for(int k = 0; k<9; k++){
//                 newNotes[i][j][k] = g->notes[i][j][k] ;
//             }
//         }
//     }
//     updateNotes(g, i, j);
//     // on duplique la grille afin de garder en mémoire les modifications de notes

//     // ce nouveau tableau de techniques comptabilise les "nouveaux" gains
//     // voir a la fin de la focntion pour l'utilite
    
//     // nakedSingle
//     for (int i1 = 0; i1 < 9; i1++) {
//         // Alternative :
//         if(g->notes[i1][j][g->grid[i][j]-1] != newNotes[i1][j][grid[i][j]-1] && i1!=i){
//             float* to_add = consequences_removed_note(grid, newNotes, i1, j, grid[i][j]-1, nb_techniques);
//             add_float_tabs(modifs, to_add, 13) ;
//             nb_notes_modified ++;
//             free(to_add);
//         }
//     }
//     for (int j1 = 0; j1 < 9; j1++) {
//         if(notes[i][j1][grid[i][j]-1] != newNotes[i][j1][grid[i][j]-1]&& j1 != j){
//             float* to_add = consequences_removed_note(grid, newNotes, i, j1, grid[i][j]-1, nb_techniques);
//             add_float_tabs(modifs, to_add, 13) ;
//             nb_notes_modified ++;
//             free(to_add);
//         }
//     }
//     for (int i1 = 0; i1 < 3; i1++) {
//         for (int j1 = 0; j1 < 3; j1++) {
//             if(notes[i1][j1][grid[i][j]-1] != newNotes[i1][j1][grid[i][j]-1] && (i1 != i || j1 != j)){
//                 float* to_add = consequences_removed_note(grid, newNotes, i1, j1, grid[i][j]-1, nb_techniques);
//                 add_float_tabs(modifs, to_add, 13) ;
//                 nb_notes_modified ++;
//                 free(to_add);
//             }
//         }
//     }

//     for(int k = 0; k<9; k++){
//         if(notes[i][j][k] != newNotes[i][j][k] && k+1 != grid[i][j]){
//             float* to_add = consequences_removed_note(grid, newNotes, i, j, k, nb_techniques);
//             add_float_tabs(modifs, to_add, 13) ;
//             free(to_add);
//             nb_notes_modified ++;
//         }
//     }

//     for(int i1 = 0; i1<9; i1++){
//         for(int j1 = 0; j1<9; j1++){
//             for(int k1 = 0; k1<9; k1++){
//                 notes[i1][j1][k1] = newNotes[i1][j1][k1];
//             }
//         }
//     }
//     free_notes(newNotes);
    
//     for(int t = 0; t<13; t++){
//         nb_techniques[t] += modifs[t] * nb_notes_modified ;
//     }
//     free(modifs);
//     // On a du faire nb_notes_modified essais pour trouver les techniques ! 
//     // On multiplie donc la difficulté pas nb_notes_modified
// }