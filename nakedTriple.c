#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Fonction globale naked Triple
Entrée : une grille de notes
Sortie : booléen (true si un nouveau triplet nu a été trouvé, false sinon)
Effet de bord : les notes pouvant être retirées grâce au triplet ont été retirées
(Fonction globale appelant successivement naked triple sur les lignes,
les colonnes et les zones) */
// Ces fonctions sont inspiré du Hidden triple même si le raisonnement est inverse
bool nakedTriple_line(bool ***notes);
bool nakedTriple_column(bool ***notes);
bool nakedTriple_zone(bool ***notes);
void free_zones(bool*** zones);

bool nakedTriple(bool ***notes) {
  //printf("coucou from nakedTriple\n");
  bool ok;
  //printf("on lance sur les lignes\n");
  ok = nakedTriple_line(notes);
  if (!ok) {
    //printf("on lance sur les colonnes\n");
    ok = nakedTriple_column(notes);
  }
  if (!ok) {
    //printf("on lance sur les zones\n");
    ok = nakedTriple_zone(notes);
  }
  return ok;
}

bool nakedTriple_line(bool ***notes) {
  for (int i = 0; i < 9; i++) {
    int compteur[9] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0}; // tableau contenant le nombre de notes d'une case
    for (int cell = 0; cell < 9; cell++) {
      for (int j = 0; j < 9; j++) { // parcours du tableau de booléen en i, cell
        if (notes[i][cell][j]) {    // note présente
          compteur[cell]++; // on incrémente le nombre de notes présentent dans
                            // cette case
        }
      }
    }
    for (int j = 0; j < 9; j++) {
      if (compteur[j] == 2 || compteur[j] ==3) { 
        // une case ne contient que deux ou trois notes, 
        //(le cas 1 note a déjà été traité par le nakedSingle, 
        //mais une case avec deux notes peut faire partie d'un nakedTriple
        // sans faire partie d'un nakedPair)
        // on examine donc si elle fait partie d'un triplet nu
        for (int k = j + 1; k < 9; k++) { //on a déjà testé les cases précédentes
          if (compteur[k] == 2 || compteur[k] ==3) { // on a trouvé une seconde case avec seulement
                                  // deux ou trois notes
            for (int p = k + 1; p < 9; p++) {
              if (compteur[p] == 2 || compteur[p] ==3) {// on a trouvé une troisième case avec seulement
                                    // deux ou trois notes, on teste si les trois cases 
                                    // font un triplet nu 
                bool valeur[9] = {
                    false, false, false, false, false,
                    false, false, false, false}; // on utilise ce tableau pour
                                                 // enregistrer les positions
                                                 // des triplets potentiels
                int count = 0;
                for (int l = 0; l < 9; l++) {
                  if (notes[i][j][l] || notes[i][k][l] || notes[i][p][l]) {
                    valeur[l] = true;
                    count++;
                  }
                }
                // il n'y a que trois valeurs différentes dans les trois cases,
                // c'est donc un triplet
                if (count == 3) { // un triplet nu est présent, on élague si ça
                                  // n'est pas déjà fait
                  bool verif = false;
                  for (int n = 0; n < 9; n++) {
                    if (valeur[n]) {
                      for (int m = 0; m < 9; m++) {
                        if (m != j && m != k && m != p && notes[i][m][n]) {
                          verif = true;
                          notes[i][m][n] = false;
                        }
                      }
                    }
                  }
                  if (verif) {
                    //printf("Technique : nakedTriple ligne\n");
                    //printf("les cases %d, %d et %d forme un triplet nu ligne %d\n",
                    //       j + 1, k + 1, p + 1, i + 1);
                    return true;
                  }
                }
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
// flemme de modifier les commentaires, voir la première fonction
bool nakedTriple_column(bool ***notes) {
  for (int i = 0; i < 9; i++) {
    int compteur[9] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0}; // tableau contenant le nombre de note d'une case
    for (int cell = 0; cell < 9; cell++) {
      for (int j = 0; j < 9; j++) { // parcours du tableau de booléen en i, cell
        if (notes[cell][i][j]) {    // note présente
          compteur[cell]++; // on incrémente le nombre de notes présentent dans
                            // cette case
        }
      }
    }
    for (int j = 0; j < 9; j++) {
      if (compteur[j] == 3 || compteur[j] == 2) { // une case ne contient que deux notes, on examine
                              // donc si c'est une paire nue
        for (int k = j + 1; k < 9; k++) {
          if (compteur[k] == 3 || compteur[k] == 2) { // on a trouvé une seconde case avec seulement
                                  // deux notes, on compare alors ces notes
            for (int p = k + 1; p < 9; p++) {
              if (compteur[p] == 3 || compteur[p] == 2) {
                bool valeur[9] = {
                    false, false, false, false, false,
                    false, false, false, false}; // on utilise ce tableau pour
                                                 // enregistrer les positions
                                                 // des paires potentielles
                int count = 0;
                for (int l = 0; l < 9; l++) {
                  if (notes[j][i][l] || notes[k][i][l] || notes[p][i][l]) {
                    valeur[l] = true;
                    count++;
                  }
                }
                // il n'y a que deux valeurs différentes dans les deux cases,
                // c'est donc une paire
                if (count == 3) { // une paire nue est présente, on elague si ça
                                  // n'est pas déjà fait
                  bool verif = false;
                  for (int n = 0; n < 9; n++) {
                    if (valeur[n]) {
                      for (int m = 0; m < 9; m++) {
                        if (m != j && m != k && m != p && notes[m][i][n]) {
                          verif = true;
                          notes[m][i][n] = false;
                        }
                      }
                    }
                  }
                  if (verif) {
                    //printf("Technique : nakedTriple colonne\n");
                    //printf("les cases %d, %d et %d forme un triplet nu colonne %d\n", j + 1, k + 1, p + 1, i + 1);
                    return true;
                  }
                }
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

// flemme de modifier les commentaires, voir la première fonction

bool nakedTriple_zone(bool ***notes) {
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
    int compteur[9] = {0, 0, 0, 0, 0,
                       0, 0, 0, 0}; // tableau stockant le nombre d'occurence
                                    // des valeurs dans les notes (initialisé à
                                    // zéro à chaque nouvelle ligne étudié)
    for (int valeur = 0; valeur < 9; valeur++) {
      for (int j = 0; j < 9; j++) {
        if (zones[i][j][valeur]) {
          compteur[valeur]++;
        }
      }
    }
  }
  for (int i = 0; i < 9; i++) {
    int compteur[9] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0}; // tableau contenant le nombre de note d'une case
    for (int cell = 0; cell < 9; cell++) {
      for (int j = 0; j < 9; j++) { // parcours du tableau de booléen en i, cell
        if (zones[i][cell][j]) {    // note présente
          compteur[cell]++; // on incrémente le nombre de notes présentent dans
                            // cette case
        }
      }
    }
    for (int j = 0; j < 9; j++) {
      if (compteur[j] == 3 || compteur[j] == 2) { // une case ne contient que deux notes, on examine
                              // donc si c'est une paire nue
        for (int k = j + 1; k < 9; k++) {
          if (compteur[k] == 3 || compteur[k]==2) { // on a trouvé une seconde case avec seulement
                                  // deux notes, on compare alors ces notes
            for (int p = k + 1; p < 9; p++) {
              if (compteur[p] == 3 || compteur[p] == 2) {
                bool valeur[9] = {
                    false, false, false, false, false,
                    false, false, false, false}; // on utilise ce tableau pour
                                                 // enregistrer les positions
                                                 // des paires potentielles
                int count = 0;
                for (int l = 0; l < 9; l++) {
                  if (zones[i][j][l] || zones[i][k][l] || zones[i][p][l]) {
                    valeur[l] = true;
                    count++;
                  }
                }
                // il n'y a que deux valeurs différentes dans les deux cases,
                // c'est donc une paire
                if (count == 3) { // une paire nue est présente, on elague si ça
                                  // n'est pas déjà fait
                  bool verif = false;
                  for (int n = 0; n < 9; n++) {
                    if (valeur[n]) {
                      for (int m = 0; m < 9; m++) {
                        if (m != j && m != k && m != p && zones[i][m][n]) {
                          verif = true;
                          zones[i][m][n] = false;
                          notes[3 * (i / 3) + m / 3][3 * (i % 3) + m % 3][n] =
                              false;
                        }
                      }
                    }
                  }
                  if (verif) {
                    //printf("Technique : nakedTriple zone\n");
                    //printf(
                    //    "les cases %d, %d et %d forme un triplet nu zone %d\n",
                    //    j + 1, k + 1, p + 1, i + 1);
                    free_zones(zones);
                    return true;
                  }
                }
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