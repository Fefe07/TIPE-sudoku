/*Fichier pour la lecture de la base de données avec difficultés */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
  int difficulty ;
  int** grid ;
} grid_one_diff ;

// n : ligne à lire
//le compteur sera mis à jour dans le main
grid_one_diff lecture_db_C(int n, char* nom_de_la_base, int cap){
	FILE* f ;
	f = fopen(nom_de_la_base, "r");


	// on va à la ligne souhaitée
	int line = 1;
	char c;
	while (line < n){
		while (fgetc(f) != ','); // on saute l'identifiant

		for(int i = 0; i<9; i++){
			for(int j = 0; j<9; j++){
				fgetc(f) ;
			}
		}
		fgetc(f); // on saute la virgule
		while (fgetc(f) != ','); // on saute le nombre de joueurs
		int diff;
		fscanf(f, "%d", &diff);
		if(diff<cap	){
			line++;
		}
		while(fgetc(f) != '\n');
	}

	grid_one_diff g ;
	
	int** mygrid = malloc(9*sizeof(int*));
	assert(mygrid!=NULL);
	for(int i =0; i<9; i++){
		mygrid[i] = malloc(9*sizeof(int));
		assert(mygrid[i]!=NULL);
	}
	g.difficulty = 42069 ;
	while(g.difficulty>=cap){
		while (fgetc(f) != ','); // on saute l'identifiant

		for(int i = 0; i<9; i++){
			for(int j = 0; j<9; j++){
				char d = fgetc(f) ;
				if (d == '.'){
					d = '0' ;
				} 
				mygrid[i][j] = d - '0';
				// correctif ascii -> chiffre
			}
		}
		fgetc(f); // on saute la virgule
		while (fgetc(f) != ','); // on saute le nombre de joueurs
		
		fscanf(f, "%d", &g.difficulty);
		g.grid = mygrid;

		while(fgetc(f) != '\n');
	}
	fclose(f);
	

	
	return g ;

}
