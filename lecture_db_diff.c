/*Fichier pour la lecture de la base de données avec difficultés */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
  float D_TO ;
  float D_TR ;
  int** grid ;
} grid_diffs ;

// n : ligne à lire
//le compteur sera mis à jour dans le main
grid_diffs lecture_db_diffs(int n, char* nom_de_la_base, int cap){
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
	float d_tr = cap+1 ; 
	float d_to ;
	grid_diffs g ;
	
	int** mygrid = malloc(9*sizeof(int*));
	assert(mygrid!=NULL);
	for(int i =0; i<9; i++){
		mygrid[i] = malloc(9*sizeof(int));
		assert(mygrid[i]!=NULL);
	}
	while(d_tr >cap){
		while (fgetc(f) != ',');

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
		
		fscanf(f, "%f", &d_to);
		fgetc(f);
		
		fscanf(f, "%f", &d_tr);
		g.grid = mygrid;
		g.D_TO = d_to ;
		g.D_TR = d_tr ;
		while(fgetc(f) != '\n');
	}
	fclose(f);

	
	return g ;

}
