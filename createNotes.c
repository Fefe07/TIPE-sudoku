#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*fonction create note 
Entrée : aucune
Sortie : un tableau de booléen de dimension 3
A la case i,j on trouve un tableau de neuf booléen, spécifiant si l'indice k peut être posé en i,j*/
bool*** createNotes() {
    //création du tableau dans le tas
    bool*** notes = malloc(9 * sizeof(bool **));
    assert(notes!=NULL);
    for (int i = 0; i < 9; i++) {
        notes[i] = malloc(9 * sizeof(bool *));
        assert(notes[i]!=NULL);
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            notes[i][j] = malloc(9 * sizeof(bool));
            assert(notes[i][j]!=NULL);
        }
    }
    //on initialise toute la grille à true, la grille sera modifiée en fonction des indices ultérieurement  
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                notes[i][j][k] = true;
            }
        }
    }
    return notes;
}