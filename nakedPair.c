#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

/*Fonction globale naked pair
Entrée : une grille de notes
Sortie : booléen (true si une nouvelle paire nue a été trouvée, false sinon )
Effet de bord : les notes pouvant être retirées grâce à la paire ont été retirées
(Fonction globale appelant successivement naked pair sur les lignes, 
les colonnes et les zones )*/
// Ces fonctions sont inspiré du Hidden Pair même si le raisonnement est inverse
bool nakedPair_line(bool ***notes);
bool nakedPair_column(bool ***notes);
bool nakedPair_zone(bool ***notes);
//float* consequences_removed_note(int** grid, bool*** notes, int i, int j, int k, float* nb_techniques);
void printGrid(int** grid);
void free_zones(bool*** zones);

bool nakedPair(grid_t g) {
    bool ok  ;
    ok = nakedPair_line(g->notes);
    if (!ok) {
        ok = nakedPair_column(g->notes);
    }
    if (!ok) {
        ok = nakedPair_zone(g->notes);
    }

    return ok;
}

bool nakedPair_zone(bool ***notes) {
    // conversion de la grille en zones
    bool ***zones = malloc(9 * sizeof(bool **));
    // on construit une grille répartis en zones :
    // plus simple pour cette étude
    // même morceau de fonction que last_remaining_cell_zone
    assert(zones != NULL);
    for (int i = 0; i < 9; i++) {
        zones[i] = malloc(9 * sizeof(bool *));
        assert(zones[i] != NULL);
        for (int j = 0; j < 9; j++) {
            zones[i][j] = notes[3*(i/3) + j/3][3*(i%3) + j%3] ;
        }
    }
    
    for (int i = 0; i < 9; i++) {
        int compteur[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; 
        // tableau contenant le nombre de notes d'une case
        for (int cell = 0; cell < 9; cell++) {
            for (int j = 0; j < 9; j++) { // parcours du tableau de booléen en i, cell
                if (zones[i][cell][j]) {    // note présente
                    compteur[cell]++; 
                    // on incrémente le nombre de notes présentes dans cette case
                }
            }
        }
        for (int j = 0; j < 9; j++) {
            if (compteur[j] == 2) { 
            // une case ne contient que deux notes, on examine donc si c'est une paire nue
                for (int k = j + 1; k < 9; k++) {
                    if (compteur[k] == 2) { 
                    // on a trouvé une seconde case avec seulement deux notes, on compare alors ces notes
                        bool valeur[9] = {false, false, false, false, false, false, false, false, false}; 
                        // on utilise ce tableau pour enregistrer les positions des paires potentielles
                        int count = 0;
                        for (int l = 0; l < 9; l++) {
                            if (zones[i][j][l] || zones[i][k][l]) {
                                valeur[l] = true;
                                count++;
                            }
                        }
                        // il n'y a que deux valeurs différentes dans les deux cases, c'est
                        // donc une paire
                        if (count == 2) { 
                            // une paire nue est présente, on elague si ça n'est pas déjà fait
                            bool verif = false;
                            for (int n = 0; n < 9; n++) {
                                if (valeur[n]) {
                                    for (int m = 0; m < 9; m++) { 
                                        if (m != j && m != k && zones[i][m][n]) {
                                            verif = true;
                                            zones[i][m][n] = false;
                                            notes[3 * (i / 3) + m / 3][3 * (i % 3) + m % 3][n] = false;
                                        }
                                    }
                                }
                            }
                            if (verif) {
                                //printf("Technique : nakedPair zone\n");
                                //printf("les cases %d et %d forme une paire nue zone %d\n", j + 1, k + 1, i + 1);
                                free_zones(zones);
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    //printf("Grille parcourue\n");
    free_zones(zones);
    return false;
}

bool nakedPair_column(bool ***notes) {
    for (int i = 0; i < 9; i++) {
        int compteur[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; 
        // tableau contenant le nombre de note d'une case
        for (int cell = 0; cell < 9; cell++) {
            for (int j = 0; j < 9; j++) { // parcours du tableau de booléen en i, cell
                if (notes[cell][i][j]) {    // note présente
                    compteur[cell]++; // on incrémente le nombre de notes présentent dans
                                                        // cette case
                }
            }
        }
        for (int j = 0; j < 9; j++) {
            if (compteur[j] == 2) { // une case ne contient que deux notes, on examine
                                                            // donc si c'est une paire nue
                for (int k = j + 1; k < 9; k++) {
                    if (compteur[k] == 2) { // on a trouvé une seconde case avec seulement
                                                                    // deux notes, on compare alors ces notes
                        bool valeur[9] = {
                                false, false, false, false, false,
                                false, false, false, false}; // on utilise ce tableau pour
                                                                                         // enregistrer les positions des
                                                                                         // paires potentielles
                        int count = 0;
                        for (int l = 0; l < 9; l++) {
                            if (notes[j][i][l] || notes[k][i][l]) {
                                valeur[l] = true;
                                count++;
                            }
                        }
                        // il n'y a que deux valeurs différentes dans les deux cases, c'est
                        // donc une paire
                        if (count == 2) { // une paire nue est présente, on elague si ça
                                                            // n'est pas déjà fait
                            bool verif = false;
                            for (int n = 0; n < 9; n++) {
                                if (valeur[n]) {
                                    for (int m = 0; m < 9; m++) {
                                        if (m != j && m != k && notes[m][i][n]) {
                                            verif = true;
                                            notes[m][i][n] = false;
                                        }
                                    }
                                }
                            }
                            if (verif) {
                                //printf("Technique : nakedPair colonne\n");
                                //printf("les cases %d et %d forme une paire nue colonne %d\n", j + 1, k + 1, i + 1);
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    //printf("Grille parcourue\n");
    return false;
}

bool nakedPair_line(bool ***notes) {
    for (int i = 0; i < 9; i++) {
        int compteur[9] = {
                0, 0, 0, 0, 0,
                0, 0, 0, 0}; // tableau contenant le nombre de note d'une case
        for (int cell = 0; cell < 9; cell++) {
            for (int j = 0; j < 9; j++) { // parcours du tableau de booléen en i, cell
                if (notes[i][cell][j]) {    // note présente
                    compteur[cell]++; // on incrémente le nombre de notes présentent dans
                                                        // cette case
                }
            }
        }
        for (int j = 0; j < 9; j++) {
            if (compteur[j] == 2) { // une case ne contient que deux notes, on examine
                                                            // donc si c'est une paire nue
                for (int k = j + 1; k < 9; k++) {
                    if (compteur[k] == 2) { // on a trouvé une seconde case avec seulement
                                                                    // deux notes, on compare alors ces notes
                        bool valeur[9] = {
                                false, false, false, false, false,
                                false, false, false, false}; // on utilise ce tableau pour
                                                                                         // enregistrer les positions des
                                                                                         // paires potentielles
                        int count = 0;
                        for (int l = 0; l < 9; l++) {
                            if (notes[i][j][l] || notes[i][k][l]) {
                                valeur[l] = true;
                                count++;
                            }
                        }
                        // il n'y a que deux valeurs différentes dans les deux cases, c'est
                        // donc une paire
                        if (count == 2) { // une paire nue est présente, on elague si ça
                                                            // n'est pas déjà fait
                            bool verif = false;
                            for (int n = 0; n < 9; n++) {
                                if (valeur[n]) {
                                    for (int m = 0; m < 9; m++) {
                                        if (m != j && m != k && notes[i][m][n]) {
                                            verif = true;
                                            notes[i][m][n] = false;
                                        }
                                    }
                                }
                            }
                            if (verif) {
                                //printf("Technique : nakedPair ligne\n");
                                //printf("les cases %d et %d forme une paire nue ligne %d\n", j + 1, k + 1, i + 1);
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    //printf("Grille parcourue\n");
    return false;
}

bool nakedPair_one_zone_one_value(int** grid, bool ***notes, int z, int k, float* nb_techniques);
bool nakedPair_one_column_one_value(int** grid, bool ***notes, int i, int k, float* nb_techniques);
bool nakedPair_one_line_one_value(int** grid, bool ***notes, int i, int k, float* nb_techniques);

bool nakedPair_one_cell_value(grid_t g, int i, int j, int k){
    bool ok ;
    ok = nakedPair_one_zone_one_value(g->grid, g->notes, 3*(i/3) + j/3, k, g->nb_techniques);
    if (!ok){
        ok = nakedPair_one_line_one_value(g->grid, g->notes, i, k, g->nb_techniques);
    }
    if(!ok){
        ok = nakedPair_one_column_one_value(g->grid, g->notes, j, k, g->nb_techniques);
    }
    return ok ;
}


bool nakedPair_one_zone_one_value(int** grid, bool ***notes, int z, int k, float* nb_techniques) {
    // conversion de la grille en zones
    bool ***zones = malloc(9 * sizeof(bool **));
    // on construit une grille répartis en zones :
    // plus simple pour cette étude
    // même morceau de fonction que last_remaining_cell_zone
    assert(zones != NULL);
    for (int i = 0; i < 9; i++) {
        zones[i] = malloc(9 * sizeof(bool *));
        assert(zones[i] != NULL);
        for (int j = 0; j < 9; j++) {
            zones[i][j] = notes[3*(i/3) + j/3][3*(i%3) + j%3] ;
        }
    }

    int compteur[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; 
    // tableau contenant le nombre de notes d'une case
    for (int cell = 0; cell < 9; cell++) {
        for (int j = 0; j < 9; j++) { // parcours du tableau de booléen en i, cell
            if (zones[z][cell][j]) {    // note présente
                compteur[cell]++; 
                // on incrémente le nombre de notes présentes dans cette case
            }
        }
    }
    for (int j = 0; j < 9; j++) {
        if (compteur[j] == 2) { 
        // une case ne contient que deux notes, on examine donc si c'est une paire nue
            if (j!= k && compteur[k] == 2) { 
            // on a trouvé une seconde case avec seulement deux notes, on compare alors ces notes
                bool valeur[9] = {false, false, false, false, false, false, false, false, false}; 
                // on utilise ce tableau pour enregistrer les positions des paires potentielles
                int count = 0;
                for (int l = 0; l < 9; l++) {
                    if (zones[z][j][l] || zones[z][k][l]) {
                        valeur[l] = true;
                        count++;
                    }
                }
                // il n'y a que deux valeurs différentes dans les deux cases, c'est
                // donc une paire
                if (count == 2) { 
                    // une paire nue est présente, on elague si ça n'est pas déjà fait
                    bool verif = false;
                    bool** todo = malloc(9*sizeof(bool*));
                    assert(todo!=NULL);
                    int count = 0;
                    for(int n = 0; n <9; n++){
                        todo[n] = malloc(9*sizeof(bool));
                        for(int m = 0; m<9; m++){
                            todo[n][m] = false;
                        }
                    }
                    for (int n = 0; n < 9; n++) {
                        if (valeur[n]) {
                            for (int m = 0; m < 9; m++) { 
                                if (m != j && m != k && zones[z][m][n]) {
                                    verif = true;
                                    zones[z][m][n] = false;
                                    todo[n][m] = true ;
                                    count ++;
                                    notes[3 * (z / 3) + m / 3][3 * (z % 3) + m % 3][n] = false;
                                }
                            }
                        }
                    }
                    if (verif) {
                        //printf("Technique : nakedPair zone_one_cell\n");
                        //printf("les cases %d et %d forme une paire nue zone %d\n", j + 1, k + 1, z + 1);
                        // for(int n = 0; n<9; n++){
                        //     for(int m = 0; m<9; m++){
                        //         if(todo[n][m]){
                        //             float * to_add = consequences_removed_note(grid, notes, z, m, n, nb_techniques);
                        //             for(int i = 0; i<13; i++){
                        //                 nb_techniques[i] += to_add[i] * count ;
                        //             }
                        //             free(to_add);
                        //         }
                        //     }
                        // }
                        for(int i = 0; i<9; i++){
                            free(todo[i]);
                        }
                        free(todo);
                        free_zones(zones);
                        return true;
                    }
                    for(int i = 0; i<9; i++){
                        free(todo[i]);
                    }
                    free(todo);
                }
            }
            
        }
    }
    free_zones(zones);
    //printf("Grille parcourue\n");
    return false;
}

bool nakedPair_one_column_one_value(int** grid, bool ***notes, int i, int k, float* nb_techniques) {

    int compteur[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; 
    // tableau contenant le nombre de note d'une case
    for (int cell = 0; cell < 9; cell++) {
        for (int j = 0; j < 9; j++) { // parcours du tableau de booléen en i, cell
            if (notes[cell][i][j]) {    // note présente
                compteur[cell]++; 
                // on incrémente le nombre de notes présentes dans cette case
            }
        }
    }
    for (int j = 0; j < 9; j++) {
        if (compteur[j] == 2) { // une case ne contient que deux notes, on examine
                                                        // donc si c'est une paire nue
            
            if (j!= k && compteur[k] == 2) { // on a trouvé une seconde case avec seulement
                                                            // deux notes, on compare alors ces notes
                bool valeur[9] = {
                        false, false, false, false, false,
                        false, false, false, false}; // on utilise ce tableau pour
                                                                                 // enregistrer les positions des
                                                                                 // paires potentielles
                int count = 0;
                for (int l = 0; l < 9; l++) {
                    if (notes[j][i][l] || notes[k][i][l]) {
                        valeur[l] = true;
                        count++;
                    }
                }
                // il n'y a que deux valeurs différentes dans les deux cases, c'est
                // donc une paire
                if (count == 2) { // une paire nue est présente, on elague si ça
                                                    // n'est pas déjà fait
                    bool verif = false;
                    for (int n = 0; n < 9; n++) {
                        if (valeur[n]) {
                            for (int m = 0; m < 9; m++) {
                                if (m != j && m != k && notes[m][i][n]) {
                                    verif = true;
                                    notes[m][i][n] = false;
                                }
                            }
                        }
                    }
                    if (verif) {
                        //printf("Technique : nakedPair colonne one cell\n");
                        //printf("les cases %d et %d forme une paire nue colonne %d\n", j + 1, k + 1, i + 1);
                        return true;
                    }
                }
            }
            
        }
    }
    
    //printf("Grille parcourue\n");
    return false;
}

bool nakedPair_one_line_one_value(int** grid, bool ***notes, int i, int k, float* nb_techniques) {

    int compteur[9] = {
            0, 0, 0, 0, 0,
            0, 0, 0, 0}; // tableau contenant le nombre de note d'une case
    for (int cell = 0; cell < 9; cell++) {
        for (int j = 0; j < 9; j++) { // parcours du tableau de booléen en i, cell
            if (notes[i][cell][j]) {    // note présente
                compteur[cell]++; // on incrémente le nombre de notes présentent dans
                                                    // cette case
            }
        }
    }
    for (int j = 0; j < 9; j++) {
        if (compteur[j] == 2) { 
            // une case ne contient que deux notes, on examine
            // donc si c'est une paire nue
            if (j != k && compteur[k] == 2) { 
            // on a trouvé une seconde case avec seulement
            // deux notes, on compare alors ces notes
                bool valeur[9] = {
                        false, false, false, false, false,
                        false, false, false, false}; 
                // on utilise ce tableau pour enregistrer les positions des
                // paires potentielles
                int count = 0;
                for (int l = 0; l < 9; l++) {
                    if (notes[i][j][l] || notes[i][k][l]) {
                        valeur[l] = true;
                        count++;
                    }
                }
                // il n'y a que deux valeurs différentes dans les deux cases, 
                // c'est donc une paire
                if (count == 2) { 
                    // une paire nue est présente, on elague si ça
                    // n'est pas déjà fait
                    bool verif = false;
                    for (int n = 0; n < 9; n++) {
                        if (valeur[n]) {
                            for (int m = 0; m < 9; m++) {
                                if (m != j && m != k && notes[i][m][n]) {
                                    verif = true;
                                    notes[i][m][n] = false;
                                }
                            }
                        }
                    }
                    if (verif) {
                        //printf("Technique : nakedPair ligne one cell\n");
                        //printf("les cases %d et %d forme une paire nue ligne %d\n", j + 1, k + 1, i + 1);
                        return true;
                    }
                }
            }
            
        }
    }
    
    //printf("Grille parcourue\n");
    return false;
}
