/*fonction y-wing*/
#include <assert.h>
#include <stdbool.h>
#include<stdio.h>

struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

bool same_zone(int i1, int j1, int i2, int j2) ;
// même ligne ou même colonne ou même sous-groupe

int compteur(bool *tab) {
  int compt = 0;
  for (int i = 0; i < 9; i++) {
    if (tab[i]) {
      compt++;
    }
  }
  return compt;
}

bool y_wing(grid_t g) {
  bool verif = false;
  for (int i = 0; i < 9; i++) {   // boucle itérant sur les lignes
    for (int j = 0; j < 9; j++) { // boucle itérant sur les colonnes
      // on parcours chaque case de la grille
      if (compteur(g->notes[i][j]) == 2) { 
        // on compte le nombre d'indice par case, si il y en a deux on la
        // considère comme pivot
        int pivot[2] = {-1, -1};
        int pincer_1[2] = {-1, -1};
        int pincer_2[2] = {-1, -1};
        int position_pince[4] = {
            -1, -1, -1, -1}; // tableau contenant l'indice de ligne et colonne des
                             // pinces (la position du pivot est i,j)
        bool valide[3] = {false, false,
        false}; // ce tableau contient trois booléen indiquant si le
                // pivot et les deux pinces sont valides ou non
        for (int k = 0; k < 9; k++) {
          // première valeur du pivot
          if (g->notes[i][j][k] && pivot[0] == -1) {
            pivot[0] = k;
          }
          // seconde valeur du pivot  (on ne remplit la seconde que si la
          // première est remplie)
          else {
            if (g->notes[i][j][k]) {
              pivot[1] = k;
              valide[0] = true; // le pivot est rempli, on modifie donc le
                                // tableau de booléens
              //printf("On a trouvé un pivot : %d %d\n", i+1, j+1);
            }
          }
        }
        // On cherche la première pince (une valeur en commun avec le pivot)
        for (int i1 = 0; i1 < 9; i1++) {
          for (int j1 = 0; j1 < 9; j1++) {
            if ((i1 != i || j1 != j) && (compteur(g->notes[i1][j1]) == 2) &&
                same_zone(i, j, i1, j1) ) {
              // la case est différente du pivot et le compteur est de deux et
              // la case est en relation avec le pivot, on regarde donc les
              // notes
              pincer_1[0] = -1 ;
              pincer_1[1] = -1 ;
              
              for (int k = 0; k < 9; k++) {
                if (g->notes[i1][j1][k] && (k == pivot[0])) {
                  pincer_1[0] = k;
                } else {
                  if (g->notes[i1][j1][k]) {
                    pincer_1[1] = k;
                  }
                }
              }
              if (pincer_1[0] != -1 && pincer_1[1] != -1) {
                valide[1] = true;
                position_pince[0] = i1;
                position_pince[1] = j1;
                //printf("On a trouvé une premiere pince\n");
                // On cherche la seconde pince (une valeur en commun avec le pivot)
                for (int i2 = 0; i2 < 9; i2++) {
                  for (int j2 = 0; j2 < 9; j2++) {
                    if ((i2 != i || j2 != j) && (compteur(g->notes[i2][j2]) == 2) &&
                        same_zone(i, j, i2, j2) && 
                        !(same_zone(position_pince[0], position_pince[1], i2, j2))) {
                      pincer_2[0] = -1 ;
                      pincer_2[1] = -1 ;
                      // la case est différente du pivot et de la première pince, le
                      // compteur est de deux et la case est en relation avec le pivot,
                      // on regarde donc les notes
                      for (int k = 0; k < 9; k++) {
                        if (g->notes[i2][j2][k] && (k == pivot[1])) {
                          pincer_2[0] = k;
                        } else {
                          if (g->notes[i2][j2][k]) {
                            pincer_2[1] = k;
                          }
                        }
                      }
                      if (pincer_2[0] != -1 && pincer_2[1] != -1) {
                        valide[2] = true;
                        position_pince[2] = i2;
                        position_pince[3] = j2;
                        //printf("On a trouvé une deuxieme pince\n");
                        
                        // on regarde si les deux pinces sont remplies
                        if (valide[1] && valide[2]) {
                          //printf("Coucou1\n");
                          // les premières valeurs doivent être différentes et  les secondes
                          // identique, les deux pinces ne doivent pas être en relation directe
                          //printf("%d %d %d %d %d %d %d %d\n", pincer_1[0] , pincer_2[0], pincer_1[1] , pincer_2[1], position_pince[0], position_pince[1],position_pince[2], position_pince[3]);
                          if ((pincer_1[0] != pincer_2[0]) && (pincer_1[1] == pincer_2[1]) &&
                              !(same_zone(position_pince[0], position_pince[1],
                                          position_pince[2], position_pince[3]))) {
                            //printf("Coucou2\n");
                            // les pinces sont valides, on doit donc chercher à élaguer dans
                            // toutes les cases sous l'influence des DEUX pinces
                            /*ça pourrait être intéréssant d'utiliser les fonctions same(line,
                             * column, zone) et d'avoir un tableau stockant l'adresse du pivot
                             * est des pinces (le pivot c'est déjà i et j )*/
                            // on cherche les indices en relation est les deux pinces donc on
                            // parcours les lignes et colonnes associé à chaque pince en
                            // vérifiant si la case est en relation avec l'autre pince
                            for (int i3 = 0; i3 < 9; i3++) {
                              for (int j3 = 0; j3 < 9; j3++) {
                                if (g->notes[i3][j3][pincer_1[1]] &&
                                    same_zone(i3, j3, position_pince[0], position_pince[1]) &&
                                    same_zone(i3, j3, position_pince[2], position_pince[3])) {
                                  //printf("Coucou3\n");
                                  // la cellule est en contact avec les deux pinces et la notes
                                  // commune des pince est présente
                                  if ((i3 != position_pince[0] || j3 != position_pince[1]) &&
                                      (i3 != position_pince[2] || j3 != position_pince[3]) &&
                                      (i3 != i || j3 != j)) {
                                    // les indices ne sont pas ceux d'une pince ou du pivot,
                                    // c'est donc valide
                                    verif = true;
                                    // //printf("Y-Wing detecte :) \n");
                                    // //printf("Pivot en %d, %d avec comme valeurs %d et %d\n", 
                                    //   (i + 1), (j + 1), pivot[0]+1, pivot[1]+1);
                                    // //printf("pince 1 : %d, %d avec %d %d \n",
                                    //   position_pince[0] + 1, position_pince[1] + 1, 
                                    //   pincer_1[0]+1, pincer_1[1]+1);
                                    // //printf("pince 2 : %d, %d avec %d %d\n",
                                    //   position_pince[2] + 1, position_pince[3] + 1, 
                                    //   pincer_2[0]+1, pincer_2[1]+1);
                                    // //printf("elaguage de %d en %d, %d\n", pincer_1[1]+1,i3 + 1, j3 + 1);
                                    g->notes[i3][j3][pincer_1[1]] = false;
                                  }
                                }
                              }
                            }
                            if (verif) {
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
          }
        }
        
        
      }
    }
  }
  //printf("Pas de Y-wing :( \n");
  return false;
}
