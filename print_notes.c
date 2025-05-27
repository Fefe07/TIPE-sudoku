/*fonction d'affichage des notes*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>


void print_notes(bool ***notes);

void print_notes(bool ***notes) {
  for (int j1 = 0; j1 < 9; j1++) {       // boucle sur les lignes des cases
    for (int j2 = 0; j2 < 3; j2++) {     // boucle sur les lignes des notes
      for (int i1 = 0; i1 < 9; i1++) {   // boucle sur les colonnes des cases
        for (int i2 = 0; i2 < 3; i2++) { // boucle sur les colonnes des notes
          if (notes[j1][i1][3 * j2 + i2]) {
            printf("%d ", 3 * j2 + i2 + 1);
          } else {
            printf("  "); // si la note est à false on print un caractère vide
                          // sinon on print l'indice de la boucle
          }
        }
        if (i1 == 2 || i1 == 5) {
          printf(" |");
        }
        printf("|  ");
        if (i1 == 8) {
          printf("\n");
        }
      }
    }
    if (j1 == 2 || j1 == 5) {
      printf("-----------------------------------------------------------------------------------\n");
    } else {
      printf("------------------------ || ------------------------- || --------------------------\n");
    }
  }
}
