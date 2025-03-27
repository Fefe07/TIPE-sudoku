#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void updateNotes(int** grid, bool*** notes, int row, int col);
void increase_difficulty(int n);
void free_zones(bool*** zones);

bool pointingPair(bool*** notes){
	
	// conversion de la grille en zones
	bool ***zones = malloc(9 * sizeof(bool **));
	// on construit une grille répartis en zones :
	// plus simple pour cette étude
	// même morceau de fonction que last_remaining_cell_zone
	assert(zones != NULL);
	for (int z = 0; z < 9; z++) {
		zones[z] = malloc(9 * sizeof(bool **));
		assert(zones[z] != NULL);
		for (int c = 0; c < 9; c++) {
			zones[z][c] = notes[3 * (z / 3) + c / 3][3 * (z % 3) + c % 3] ;
		}
	}
	

	
	// on parcourt les zones
	for(int z = 0; z<9; z++){
		// on parcourt les valeurs
		for(int value = 0; value < 9 ; value ++){

			// on parcourt les lignes
			int count = 0 ;
			int line = -1 ;
			for(int i = 0; i<3; i++){
				// si il y a un indice dans la ligne
				if (zones[z][3*i][value]||zones[z][3*i+1][value]||zones[z][3*i+2][value]){
					count ++ ;
					line = i ;
				}
			}
			// si une seule ligne contient des indices
			if(count == 1){
				// on modifie le reste de la ligne
				assert(line!=-1);
				bool verif = false;
				for(int j=0; j<9;j++){
					if((j<3*(z%3) || j > 3*(z%3)+2) && notes[3*(z/3) + line][j][value]){
						notes[3*(z/3) + line][j][value] = false;
						verif = true ;
					}
				}
				// uniquement si on a modifié quelque chose !
				if(verif){
					//printf("Technique : pointing Pair/Triple line\n");
					//printf("Ligne = %d, zone = %d, valeur = %d\n", 3*(z/3) + line, z, value+1);
					free_zones(zones);
					return true;
				}
			}


			// on parcourt les colonnes
			count = 0 ;
			int column = -1 ;
			for(int j = 0; j<3; j++){
				// si il y a un indice dans la colonne
				if (zones[z][j][value]||zones[z][j+3][value]||zones[z][j+6][value]){
					count ++ ;
					column = j ;
				}
			}
			// si une seule colonne contient des indices
			if(count == 1){
				// on modifie le reste de la colonne
				assert(column!=-1);
				bool verif = false ;
				for(int i=0; i<9;i++){
					if((i<3*(z/3) || i > 3*(z/3)+2) && notes[i][3*(z%3)+column][value]){
						notes[i][3*(z%3)+column][value] = false;
						verif = true ;
					}
				}
				// uniquement si on a modifié quelque chose !
				if(verif){
					//printf("Technique : pointing Pair/Triple column\n");
					//printf("Colonne = %d, zone = %d, valeur = %d\n", 3*(z%3)+column, z, value+1);
					free_zones(zones);
					return true;
				}
			}
		}
	}
	free_zones(zones);
	return false ;
	
}



bool pointingPair_one_zone_one_value(bool*** notes, int z, int value){
	
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
			zones[i][j] = notes[3*(i/3)+j/3][3*(i%3)+j%3];
		}
	}
	
	

	
	// on parcourt les lignes
	int count = 0 ;
	int line = -1 ;
	for(int i = 0; i<3; i++){
		// si il y a un indice dans la ligne
		if (zones[z][3*i][value]||zones[z][3*i+1][value]||zones[z][3*i+2][value]){
			count ++ ;
			line = i ;
		}
	}
	// si une seule ligne contient des indices
	if(count == 1){
		// on modifie le reste de la ligne
		assert(line!=-1);
		bool verif = false;
		for(int j=0; j<9;j++){
			if((j<3*(z%3) || j > 3*(z%3)+2) && notes[3*(z/3) + line][j][value]){
				notes[3*(z/3) + line][j][value] = false;
				verif = true ;
			}
		}
		// uniquement si on a modifié quelque chose !
		if(verif){
			//printf("Technique : pointing Pair/Triple line\n");
			//printf("Ligne = %d, zone = %d, valeur = %d\n", 3*(z/3) + line, z, value+1);
			free_zones(zones);
			return true;
		}
	}


	// on parcourt les colonnes
	count = 0 ;
	int column = -1 ;
	for(int j = 0; j<3; j++){
		// si il y a un indice dans la colonne
		if (zones[z][j][value]||zones[z][j+3][value]||zones[z][j+6][value]){
			count ++ ;
			column = j ;
		}
	}
	// si une seule colonne contient des indices
	if(count == 1){
		// on modifie le reste de la colonne
		assert(column!=-1);
		bool verif = false ;
		for(int i=0; i<9;i++){
			if((i<3*(z/3) || i > 3*(z/3)+2) && notes[i][3*(z%3)+column][value]){
				notes[i][3*(z%3)+column][value] = false;
				verif = true ;
			}
		}
		// uniquement si on a modifié quelque chose !
		if(verif){
			//printf("Technique : pointing Pair/Triple column\n");
			//printf("Colonne = %d, zone = %d, valeur = %d\n", 3*(z%3)+column, z, value+1);
			free_zones(zones);
			return true;
		}
	}
	free_zones(zones);
	return false ;
	
}