/*Fichier pour la lecture de la base de donnée */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// n : ligne à lire
//le compteur sera mis à jour dans le main
int** lecture(int n, char* nom_de_la_base){
	FILE* f ;
	f = fopen(nom_de_la_base, "r");

	// on va à la ligne souhaitée
	int line = 1;
	char c;
	while (line < n){
		c = fgetc(f);
		if (c == '\n'){
			line++;
		}
	}

	int** grid = malloc(9*sizeof(int*));
	assert(grid!=NULL);
	for(int i =0; i<9; i++){
		grid[i] = malloc(9*sizeof(int));
		assert(grid[i]!=NULL);
	}

	for(int i = 0; i<9; i++){
		for(int j = 0; j<9; j++){
			grid[i][j] = fgetc(f) - '0';
			// correctif ascii -> chiffre
		}
	}

	return grid ;
	
}