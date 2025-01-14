#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int increase_difficulty(int n);

bool lastRemainingCell_row(int **grid);
bool lastRemainingCell_column(int **grid);
bool lastRemainingCell_zone(int **grid);

/*Fonction verif colonne / lignes
Entrée : une grille, une valeur recherché et la ligne ou colonne dans laquelle
elle est recherché 
Sortie : si la valeur est présente ou non*/

bool verif_ligne(int valeur, int **grille, int l) {
	for (int j = 0; j < 9; j++) {
		if (valeur == grille[l][j]) {
			return true;
		}
	}
	return false;
}

bool verif_colonne(int valeur, int **grille, int c) {
	for (int i = 0; i < 9; i++) {
		if (valeur == grille[i][c]) {
			return true;
		}
	}
	return false;
}

bool verif_zone(int valeur, int **grille, int row_zone, int col_zone){
	for(int i = 0; i<3; i++){ //itération sur les lignes et colonnes de la zone
		for(int j = 0; j<3; j++){
			if (valeur == grille[row_zone + i][col_zone + j]){
				return true ;
			}
		}
	}
	return false ;
}


// on réunit les trois
bool lastRemainingCell(int **grid) {

	bool ok = false;
	ok = lastRemainingCell_column(grid);
	if (!ok) {
		ok = lastRemainingCell_row(grid);
		if (!ok) {
			ok = lastRemainingCell_zone(grid);
		}
	}
	if(ok){
		increase_difficulty(2);
	}
	return ok;
}

/*fonction last remaining cell sur les lignes */
bool lastRemainingCell_row(int **grid) {
	// //printf("Technique essayee : dernière case restante ligne\n");
	for (int i = 0; i < 9; i++) {
		int possibilities[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
		// on reinitialise les chiffres possibles pour chaque ligne

		// si un chiffre est déjà présent dans la ligne, on l'exclut des possibilités
		for (int j = 0; j < 9; j++) {
			if (grid[i][j] != 0) {
				possibilities[grid[i][j] - 1] = 0;
				// on ne testera donc que les valeur non présentes
			}
		}

		for (int chiffre = 1; chiffre < 10; chiffre++) {
			if (possibilities[chiffre - 1] != 0) {

				bool cell[9] = {true, true, true, true, true, true, true, true, true}; 
				// pour chaque chiffre, on cree un tableau des cases disponibles 
				// dans la ligne pour ce chiffre

				// si une case est pleine, alors elle n'est pas disponible
				for (int j = 0; j < 9; j++) {
					if (grid[i][j] != 0) {
						cell[j] = false;
					}
				}

				// si une des règles empêche le chiffre d'être sur une case,
				// on retire cette case de cell, le tableau des cases possibles
				for(int j =0; j<9; j++){
					if (cell[j] && (verif_zone(chiffre, grid, 3*(i/3), 3*(j/3)) || verif_colonne(chiffre, grid, j))) {
						cell[j] = false;
					}

				}

				int count = 0;
				for (int i = 0; i < 9; i++) { 
					// on compte le nombre de place possible pour cette valeur
					if (cell[i]) {
						count++;
					}
				}

				if (count == 1) { 
					// il y a une unique place pour cette valeur on peut donc la placer
					int k = 0;
					while (k < 9 && !cell[k]) {
						k++;
					}
					grid[i][k] = chiffre; 
					// mise à jour des grilles : une valeur a été placée
					//printf("Technique : Last Remaining Cell Row\n");
					//printf("row = %d, col = %d, val = %d\n", i, k, chiffre);
					return true;
				}
			}
		}
	}
	return false;
}


bool lastRemainingCell_column(int **grid) {

	for (int j = 0; j < 9; j++) {
		// //printf("attaque de la colonne %d \n", j);


		int possibilities[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
		// on reinitialise les possibilités pour chaque lignes
		for (int i = 0; i < 9; i++) {
			if (grid[i][j] != 0) {
				possibilities[grid[i][j] - 1] = 0; // on ne filtre donc que les valeur non présentes
			}
		}

		for (int chiffre = 1; chiffre <= 9; chiffre++) {
			if (possibilities[chiffre - 1] != 0) {
				// si le chiffre n'est pas déjà présent sur la colonne

				bool cell[9] = {true, true, true, true, true, true, true, true, true}; 
				// pour chaque chiffre, on cree un tableau des cases disponibles

				// si la case n'est pas vide, alors elle n'est pas disponible
				for (int i = 0; i < 9; i++) {
					if (grid[i][j] != 0) {
						cell[i] = false;
					}
				}

				// si la case ne peut pas accueillir ce chiffre à cause d'une des règles,
				// alors on la retire des cases disponibles 
				for (int i = 0; i < 9; i++) {
					if (verif_zone(chiffre, grid, 3*(i/3) , 3*(j/3)) || verif_ligne(chiffre, grid, i)) {
						cell[i] = false;
					}
				}

				int count = 0;
				for (int k = 0; k < 9; k++) { 
					// on compte le nombre de place possible pour cette valeur
					if (cell[k]) {
						count++;
					}
				}

				if (count == 1) { 
					// il y a une unique place pour cette valeur on peut donc la placer
					int k = 0;
					while (k < 9 && !cell[k]) {
						k++;
					}
					grid[k][j] = chiffre; // mise à jour des grilles : une valeur a été placée
					//printf("Technique : Last Remaining Cell Column\n");
					//printf("row = %d, col = %d, val = %d\n", k, j, chiffre);
					return true;
				}
			}
		}
	}
	return false;
}


bool lastRemainingCell_zone(int **grid) { 
	// la grille sera de 9 par 9 (tableau de dimension 2)

	int **zones = malloc(9 * sizeof(int *)); 
	// on construit une grille répartis en zones :
	// plus simple pour cette étude
	assert(zones != NULL);
	for (int i = 0; i < 9; i++) {
		zones[i] = malloc(9 * sizeof(int));
		assert(zones[i] != NULL);
	}

	for (int z = 0; z < 9; z++) {
		for (int c = 0; c < 9; c++) {
		  zones[z][c] = grid[3*(z/3) + c / 3][3 * (z % 3) + c % 3];
		}
	}

	for (int z = 0; z < 9; z++) { 
		// pour chaque zone de la grille

		int possibilities[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		// on reinitialise le tableau des chiffres possibles pour chaque zone

		for (int j = 0; j < 9; j++) { // on trouve les places disponibles
			if (zones[z][j] != 0) {
				possibilities[zones[z][j]-1] = 0;
				// il ne restera que les valeurs non présentes
			}
		}


		for (int chiffre = 1; chiffre <= 9; chiffre++){

			if (possibilities[chiffre - 1] != 0) {
				// le chiffre n'est pas présent dans la zone : on cherche alors sa
				// place

				bool cell[9] = {true, true, true, true, true, true, true, true, true};
				// cell : tableau des cellules possibles, pour un chiffre donné

				// Si une case est pleine, elle ne peut pas accueillir le chiffre
				for (int j = 0; j < 9; j++) { 
					if (zones[z][j] != 0) {
						cell[j] = false;
					}
				}


				for (int j = 0; j < 9; j++) { // on cherche les cases vides
					if (cell[j]) {
						// si  la case est libre
						// appel à une fonction auxiliaire verif de ligne ou colonne
						// voisines
						for (int i = 0; i < 3; i++) {
							if (verif_ligne(possibilities[chiffre - 1], grid, 3 * (z / 3) + i)) {
								for (int k = 0; k < 3; k++) {
									cell[3 * i + k] = false; 
									// on retire les cases présentes dans cette
									// ligne du tableau des possibilités;
								}
							}
							if (verif_colonne(possibilities[chiffre - 1], grid, 3 * (z % 3) + i)) {
								for (int k = 0; k < 3; k++) {
									cell[i + 3 * k] = false; 
									// on retire les cases présentes dans cette
									// colonne du tableau des possibilités;
								}
							}
						}
					}
				}

				int count = 0;
				for (int i = 0; i < 9; i++) { 
					// on compte le nombre de place possible pour cette valeur
					if (cell[i]) {
						count++;
					}
				}
				if (count == 1) { 
					// il y a une unique place pour cette valeur on peut donc la placer
					int k = 0;
					while (k < 9 && !cell[k]) {
						k++;
					}
					// mise à jour des grilles : une valeur a été placée
					grid[3*(z/3) + k / 3][3 * (z % 3) + k % 3] = chiffre;
					//printf("Technique : Last Remaining Cell zone\n");
					//printf("Row = %d , col = %d, val = %d \n", 3*(z/3) + k/3, 3*(z%3) + k%3, chiffre);
					return true;
				}
			}

		}

	}
	return false;
}

