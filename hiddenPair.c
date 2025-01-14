#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Fonction globale hidden pair
Entrée : une grille de notes
Sortie : booléen (si une nouvelle paire cachée a été trouvée ou non)
Effet de bord : les notes pouvant être retirées grâce à la paire ont été retirées
(Fonction globale appelant successivement hidden pair sur les lignes, 
les colonnes et les zones )*/
bool hiddenPair_line(bool ***notes);
bool hiddenPair_column(bool ***notes);
bool hiddenPair_zone(bool ***notes);
void free_zones(bool*** zones);

bool hiddenPair(bool ***notes) {
   //printf("Coucou from hiddenpair\n");
   bool ok ;
   //printf("On lance sur les lignes\n");
   ok = hiddenPair_line(notes);
   if(!ok){
      //printf("On lance sur les colonnes\n");
      ok = hiddenPair_column(notes);
   }
   if(!ok){
      //printf("On lance sur les zones\n");
      ok = hiddenPair_zone(notes);
   }

   return ok;
}

/*fonction hiddenPair (uniquement sur les lignes )
Entrée : une grille munie de notes
Sortie : un booléen (si une nouvelle paire cachée a été trouvée ou non )*/
bool hiddenPair_line(bool ***notes) {
   for (int i = 0; i < 9; i++) {
      int compteur[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // tableau stockant le nombre d'occurences
                                          // des valeurs dans les notes (initialisé à
                                          // zéro à chaque nouvelle ligne étudiée)
      for (int valeur = 0; valeur < 9; valeur++) {
         for (int j = 0; j < 9; j++) {
            if (notes[i][j][valeur]) {
               compteur[valeur]++;
            }
         }
      }
      // le tableau est rempli, on peut donc faire 
      // une étude exhaustive des paires possibles
      for (int j = 0; j < 9; j++) {
         if (compteur[j] == 2) {
            for (int k = j + 1; k < 9;
                   k++) { // on recherche une paire parmis les valeurs suivantes (la
                              // relation de paire étant symetrique)
               if (compteur[k] == 2) { // la seconde valeur est aussi présente deux
                                 // fois, on va donc regarder leurs places
                  // une valeur ne pouvant être présente qu'une seule fois dans une
                  // case, si le nombre total de cases occupées par ces notes est de
                  // deux alors la paire est conforme
                  bool place[9] = {
                        false, false, false, false, false,
                        false, false, false, false}; // on utilise ce tableau pour
                                              // enregistrer les positions des
                                              // paires potentielles
                  int count = 0;
                  for (int l = 0; l < 9; l++) {
                     if (notes[i][l][k] || notes[i][l][j]) {
                        place[l] = true;
                        count++;
                     }
                  }
                  if (count == 2) {
                     // la paire est conforme, on peut donc élaguer
                     // une Hidden pair déjà élaguée est identifiée comme une hidden
                     // pair, on rajoute donc un booléen qui signale lorsque l'on
                     // élague afin de renvoyer true
                     bool verif = false;
                     for (int n = 0; n < 9; n++) {
                        if (place[n]) {
                           for (int m = 0; m < 9; m++) {
                              if (m != k && m != j && notes[i][n][m]) {
                                 verif = true; // on a trouvé une note différente de la
                                 // paire dans une des deux cases, 
                                 // on la met alors à false
                                 notes[i][n][m] = false;
                              }
                           }
                        }
                     }
                     // si verif est faux c'est que la paire est déjà élaguée, on en
                     // cherche alors une autre dans le tableau;
                     if (verif) {
                        printf("Technique : hiddenPair ligne\n");
                        printf("%d et %d forme une paire ligne %d \n", j + 1, k + 1, i + 1);
                        
                        return true;
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

/*fonction hiddenPair sur les colonne (même fonctionnement que la fonction précédente )*/
bool hiddenPair_column(bool ***notes) {
   for (int i = 0; i < 9; i++) {
      int compteur[9] = {0, 0, 0, 0, 0,
                                  0, 0, 0, 0}; // tableau stockant le nombre d'occurences
                                                      // des valeurs dans les notes (initialisé à
                                                      // zéro à chaque nouvelle ligne étudié)
      for (int valeur = 0; valeur < 9; valeur++) {
         for (int j = 0; j < 9; j++) {
            if (notes[j][i][valeur]) {
               compteur[valeur]++;
            }
         }
      }
      // le tableau est rempli, on peut donc faire une étude exhaustive des pairs
      // possible
      for (int j = 0; j < 9; j++) {
         if (compteur[j] == 2) {
            for (int k = j + 1; k < 9;
                   k++) { // on recherche une paire parmis les valeurs suivante (la
                              // relation de paire étant symetrique)
               if (compteur[k] == 2) { // la seconde valeur est aussi présente deux
                                                   // fois, on va donc regarder leurs places
                  // une valeur ne pouvant être présente qu'une seule fois dans une
                  // case, si le nombre totale de case occupé par ces notes est de
                  // deux alors la paire ets conforme
                  bool place[9] = {
                        false, false, false, false, false,
                        false, false, false, false}; // on utilise ce tableau pour
                                                                   // enregistrer les positions des
                                                                   // paires potentielles
                  int count = 0;
                  for (int l = 0; l < 9; l++) {
                     if (notes[l][i][k] || notes[l][i][j]) {
                        place[l] = true;
                        count++;
                     }
                  }
                  if (count == 2) {
                     // la paire est conforme, on peut donc élaguer
                     // une Hidden pair déjà élaguée est identifié comme une hidden
                     // pair, on rajoute donc un booléen qui signale lorsque l'on
                     // élague afin de renvoyer true
                     bool verif = false;
                     for (int n = 0; n < 9; n++) {
                        if (place[n]) {
                           for (int m = 0; m < 9; m++) {
                              if (m != k && m != j && notes[n][i][m]) {
                                 verif = true; // on a trouvé une note différente de la
                                                      // paire dans une des deux cases, on la met
                                                      // alors à false
                                 notes[n][i][m] = false;
                              }
                           }
                        }
                     }
                     // si verif est faux c'est que la paire est déjà élagué, on en
                     // cherche alors une autre dans le tableau;
                     if (verif) {
                        printf("Technique : hiddenPair colonne\n");
                        printf("%d et %d forme une paire colonne %d \n", j + 1, k + 1,
                                  i + 1);
                        return true;
                     }
                  }
               }
            }
         }
      }
   }
   // tout les colonnes on été parcouru
   //printf("Grille parcourue en entier\n");
   return false;
}

/*fonction hiddenPair sur les zones (même principe mais on convertie la grille
 * pour la parcourir selon les zones)*/
bool hiddenPair_zone(bool ***notes) {
   // conversion de la grille en zones
   bool ***zones = malloc(9 * sizeof(bool **));
   // on construit une grille répartis en zones :
   // plus simple pour cette étude
   // même morceau de fonction que last_remaining_cell_zone
   assert(zones != NULL);
   for (int i = 0; i < 9; i++) {
      zones[i] = malloc(9 * sizeof(bool **));
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
         if (compteur[j] == 2) {
            for (int k = j + 1; k < 9;
                   k++) { // on recherche une paire parmis les valeurs suivantes (la
                              // relation de paire étant symetrique)
               if (compteur[k] == 2) { // la seconde valeur est aussi présente deux
                                                   // fois, on va donc regarder leurs places
                  // une valeur ne pouvant être présente qu'une seule fois dans une
                  // case, si le nombre totale de case occupé par ces notes est de
                  // deux alors la paire ets conforme
                  bool place[9] = {
                        false, false, false, false, false,
                        false, false, false, false}; // on utilise ce tableau pour
                                                                   // enregistrer les positions des
                                                                   // paires potentielles
                  int count = 0;
                  for (int l = 0; l < 9; l++) {
                     if (zones[i][l][k] || zones[i][l][j]) {
                        place[l] = true;
                        count++;
                     }
                  }
                  if (count == 2) {
                     // la paire est conforme, on peut donc élaguer
                     // une Hidden pair déjà élaguée est identifié comme une hidden
                     // pair, on rajoute donc un booléen qui signale lorsque l'on
                     // élague afin de renvoyer true
                     bool verif = false;
                     for (int n = 0; n < 9; n++) {
                        if (place[n]) {
                           for (int m = 0; m < 9; m++) {
                              if (m != k && m != j && zones[i][n][m]) {
                                 verif = true; // on a trouvé une note différente de la
                                                      // paire dans une des deux cases, on la met
                                                      // alors à false
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
                        printf("Technique : hiddenPair zone\n");
                        printf("%d et %d forme une paire zone %d \n", j + 1, k + 1, i + 1);
                        free_zones(zones);
                        return true;
                     }
                  }
               }
            }
         }
      }
   }
   // tout les zones on été parcouru
   //printf("Grille parcourue en entier\n");
   free_zones(zones);
   return false;
}