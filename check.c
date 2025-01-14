#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool same_zone(int i1, int j1, int i2, int j2); // ok

bool check(int** grid, int i, int j) {
	// Grille (taille 81) et deux indices i (ligne) et j (colonne)
	// Retourne un booléen indiquant si la valeur proposée en ij est valide vis
	// à vis des règles du sudoku
	for (int iTest = 0; iTest < 9; iTest++) {
		for(int jTest = 0; jTest < 9; jTest ++){
			// on teste toutes les cases
			if ((i != iTest || j != jTest) && same_zone(i,j, iTest, jTest) && grid[i][j] == grid[iTest][jTest]) {
				// pour les cases de la même zone autre que la case ij, on regarde
				// si les valeurs sont identiques
				return false; // si oui, on retourne false
			}
		}

	}
	return true; //aucune des cases de la même zone identique ; valeur ok
}