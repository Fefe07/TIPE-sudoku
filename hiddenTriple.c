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

/*Fonction globale hidden triple
Entrée : une grille de note
Sortie : booléen (true si un nouveau triplet caché a été trouvé, false sinon)
Effet de bord : les notes pouvant être retirées grâce au triplet ont été retirées
(Fonction globale appelant succéssivement hidden triple sur les lignes,
les colonnes et les zones) */
bool hiddenTriple_line(bool ***notes);
bool hiddenTriple_column(bool ***notes);
bool hiddenTriple_zone(bool ***notes);
void free_zones(bool*** zones){
  for(int i = 0; i<9; i++){
    free(zones[i]);
  }
  free(zones);
}

bool hiddenTriple(grid_t g) {
  //printf("Coucou from hiddenTriple\n");
  bool ok;
  //printf("On lance sur les lignes\n");
  ok = hiddenTriple_line(g->notes);
  if (!ok) {
    //printf("On lance sur les colonnes\n");
    ok = hiddenTriple_column(g->notes);
  }
  if (!ok) {
    //printf("On lance sur les zones\n");
    ok = hiddenTriple_zone(g->notes);
  }
  return ok;
}

/*fonction hiddenTriple (uniquement sur les lignes)
Entrée : une grille munie de notes
Sortie : un booléen (si un nouveau triplet caché a été trouvé ou non) */
bool hiddenTriple_line(bool ***notes) {
  for (int i = 0; i < 9; i++) {
    int compteur[9] = {0, 0, 0, 0, 0,
                       0, 0, 0, 0}; // tableau stockant le nombre d'occurences
                                    // des valeurs dans les notes (initialisé à
                                    // zéro à chaque nouvelle ligne étudiée)
    for (int valeur = 0; valeur < 9; valeur++) {
      for (int j = 0; j < 9; j++) {
        if (notes[i][j][valeur]) {
          compteur[valeur]++;
        }
      }
    }
    // le tableau est rempli, on peut donc faire une étude exhaustive des triplets
    // possibles
    for (int j = 0; j < 9; j++) {
      if (compteur[j] == 2 || compteur[j] == 3) { 
        // Une note n'est présente que dans deux ou trois cases
        // (le cas une case a déjà été traité par le hiddenSingle, 
        // mais une note dasn deux cases peut faire partie d'un hiddenTriple
        // sans faire partie d'un hiddenPair),
        // on examine donc si elle fait partie d'un triplet caché
        for (int k = j + 1; k < 9;
             k++) { // on recherche un triplet parmis les valeurs suivante (la
                    // relation de triplet étant symetrique)
          if (compteur[k] == 2 || compteur[k] == 3) { 
            for (int p = k + 1; p < 9; p++) {
              if (compteur[p] == 2 || compteur[p] == 3) {
                 // La troisième valeur est aussi présente deux fois, on va donc
                 // regarder leurs places. Une valeur ne pouvant être présente
                 // qu'une seule fois dans une case, si le nombre totale de
                 // case occupé par ces notes est de trois alors la paire ets
                 // conforme
                bool place[9] = {
                    false, false, false, false, false,
                    false, false, false, false}; // on utilise ce tableau pour
                                                 // enregistrer les positions
                                                 // des triplets potentiels
                int count = 0;
                for (int l = 0; l < 9; l++) {
                  if (notes[i][l][k] || notes[i][l][j] || notes[i][l][p]) {
                    place[l] = true;
                    count++;
                  }
                }
                if (count ==
                    3) { // le triple est conforme (trois valeurs différente et
                         // 3 cases), on peut donc élaguer
                  // un Hidden Triple déjà élaguée est identifié comme une
                  // hidden pair, on rajoute donc un booléen qui signale lorsque
                  // l'on élague afin de renvoyer true
                  bool verif = false;
                  for (int n = 0; n < 9; n++) {
                    if (place[n]) {
                      for (int m = 0; m < 9; m++) {
                        if (m != k && m != j && m != p && notes[i][n][m]) {
                          verif = true; // on a trouvé une note différente du
                                        // triplet dans une des trois cases, on la
                                        // met alors à false
                          notes[i][n][m] = false;
                        }
                      }
                    }
                  }
                  // si verif est faux c'est que le triplet est déjà élagué, on en
                  // cherche alors un autre dans le tableau;
                  if (verif) {
                    //printf("Technique : hiddenTriple ligne\n");
                    //printf("%d, %d et %d forme un triplet en ligne %d \n", j + 1, k + 1, p + 1, i + 1);
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
  // tout les lignes on été parcourues
  //printf("Grille parcourue en entier\n");
  return false;
}

// flemme de recopier les commentaires
bool hiddenTriple_column(bool ***notes) {
  for (int j = 0; j < 9; j++) {
    int compteur[9] = {0, 0, 0, 0, 0,
                       0, 0, 0, 0}; // tableau stockant le nombre d'occurence
                                    // des valeurs dans les notes (initialisé à
                                    // zéro à chaque nouvelle colonne étudiée)
    for (int valeur = 0; valeur < 9; valeur++) {
      for (int i = 0; i < 9; i++) {
        if (notes[i][j][valeur]) {
          compteur[valeur]++;
        }
      }
    }
    // le tableau est rempli, on peut donc faire une étude exhaustive des
    // triplets possible
    for (int i = 0; i < 9; i++) {
      if (compteur[i] == 3 || compteur[i] == 2) {
        for (int k = i + 1; k < 9; k++) { 
          // on recherche une paire parmis les valeurs suivante (la
          // relation de paire étant symetrique)
          if (compteur[k] == 3 || compteur[k] == 2) { 
            // la seconde valeur est aussi présente trois
            // fois, on va donc
            // regarder leurs places une valeur ne pouvant être présente
            // qu'une seule fois dans une case, si le nombre totale de
            // case occupé par ces notes est de deux alors la paire ets
            // conforme
            for (int p = k + 1; p < 9; p++) {
              if (compteur[p] == 3 || compteur[p] == 2) {
                bool place[9] = {
                    false, false, false, false, false,
                    false, false, false, false}; 
                // on utilise ce tableau pour enregistrer les positions
                // des triplets potentiels
                int count = 0;
                for (int l = 0; l < 9; l++) {
                  if (notes[l][j][i] || notes[l][j][k] || notes[l][j][p]) {
                    place[l] = true;
                    count++;
                  }
                }
                if (count == 3) { 
                  // le triple est conforme (trois valeurs différente et
                  // 3 cases), on peut donc élaguer
                  // un Hidden Triple déjà élaguée est identifié comme une
                  // hidden pair, on rajoute donc un booléen qui signale lorsque
                  // l'on élague afin de renvoyer true
                  bool verif = false;
                  for (int n = 0; n < 9; n++) {
                    if (place[n]) {
                      for (int m = 0; m < 9; m++) {
                        if (m != k && m != i && m != p && notes[n][j][m]) {
                          verif = true; // on a trouvé une note différente de la
                                        // paire dans une des deux cases, on la
                                        // met alors à false
                          notes[n][j][m] = false;
                        }
                      }
                    }
                  }
                  // si verif est faux c'est que la paire est déjà élagué, on en
                  // cherche alors une autre dans le tableau;
                  if (verif) {
                    //printf("Technique : hiddenTriple colonne\n");
                    //printf("%d, %d et %d forme un triplet en colonne %d \n", i + 1, k + 1, p + 1, j + 1);
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
  // tout les lignes on été parcouru
  //printf("Grille parcourue en entier\n");
  return false;
}

bool hiddenTriple_zone(bool ***notes) {
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
    // le tableau est rempli, on peut donc faire une étude exhaustive des pairs
    // possible
    for (int j = 0; j < 9; j++) {
      if (compteur[j] == 3) {
        for (int k = j + 1; k < 9;
             k++) { // on recherche une paire parmis les valeurs suivante (la
                    // relation de paire étant symetrique)
          if (compteur[k] ==
              3) { // la seconde valeur est aussi présente deux fois, on va donc
                   // regarder leurs places une valeur ne pouvant être présente
                   // qu'une seule fois dans une case, si le nombre totale de
                   // case occupé par ces notes est de deux alors la paire ets
                   // conforme
            for (int p = k + 1; p < 9; p++) {
              if (compteur[p] == 3) {
                bool place[9] = {
                    false, false, false, false, false,
                    false, false, false, false}; // on utilise ce tableau pour
                                                 // enregistrer les positions
                                                 // des paires potentielles
                int count = 0;
                for (int l = 0; l < 9; l++) {
                  if (zones[i][l][k] || zones[i][l][j] || zones[i][l][p]) {
                    place[l] = true;
                    count++;
                  }
                }
                if (count ==
                    3) { // le triple est conforme (trois valeurs différente et
                         // 3 cases), on peut donc élaguer
                  // un Hidden Triple déjà élaguée est identifié comme une
                  // hidden pair, on rajoute donc un booléen qui signale lorsque
                  // l'on élague afin de renvoyer true
                  bool verif = false;
                  for (int n = 0; n < 9; n++) {
                    if (place[n]) {
                      for (int m = 0; m < 9; m++) {
                        if (m != k && m != j && m != p && zones[i][n][m]) {
                          verif = true; // on a trouvé une note différente de la
                                        // paire dans une des deux cases, on la
                                        // met alors à false
                          zones[i][n][m] = false;
                          notes[3 * (i / 3) + n / 3][3 * (i % 3) + n % 3][m] =
                              false;
                        }
                      }
                    }
                  }
                  // si verif est faux c'est que la paire est déjà élagué, on en
                  // cherche alors une autre dans le tableau;
                  if (verif) {
                    //printf("Technique : hiddenTriple zone\n");
                    //printf("%d, %d et %d forme un triplet en zone %d \n", j + 1, k + 1, p + 1, i + 1);
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
  // tout les lignes on été parcouru
  //printf("Grille parcourue en entier\n");
  free_zones(zones);
  return false;
}