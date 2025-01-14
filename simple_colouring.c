#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

// remarque : c'est rigolo, ça utilise les graphes bipartis 

/*
typedef struct chaine {
	int i1 ;
	int j1;
	int i2;
	int j2;
}chaine;
*/
void parcours(int i, int j, bool* is_a_chain_line, bool* is_a_chain_column, 
	bool* is_a_chain_zone, int* ligne1, int* ligne2, int* colonne1, int* colonne2,  
	int* lignez1, int* lignez2, int* colonnez1, int* colonnez2, int** colour);

bool simple_colouring(bool*** notes){

	for(int n = 0; n<9; n++){

		// Première partie : recherche des chaines
		//similaire au x-wing
		// essai
		//chaine* ligne[9] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

		// indices de départ de l'étape 2
		int i_dep = -1 ;
		int j_dep = -1 ;

		// indices de deux colonnes contenat des indices (utile si count[i] = 2)
		bool is_a_chain_line[9] = {false,false,false,false,false,false,false,false,false};
		int colonne1[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
		int colonne2[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
		for(int i = 0; i<9; i++){
			int count = 0;
			for(int j = 0; j<9; j++){
				if(notes[i][j][n]){
					count++ ;
					if(colonne1[i]==-1){
						colonne1[i] = j;
					}
					else{
						colonne2[i] = j;
					}
				}
			}
			if (count == 2){
				/*chaine* c = malloc(sizeof(chaine));
				c-> i1 = i;
				c->i2 = i;
				c->j1 = colonne2;
				ligne[i] = 
				*/
				i_dep = i;
				j_dep = colonne1[i];
				is_a_chain_line[i] = true;
			}
		}
		
		bool is_a_chain_column[9] = {false,false,false,false,false,false,false,false,false};
		int ligne1[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
		int ligne2[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
		for(int j = 0; j<9; j++){
			int count = 0;
			for(int i = 0; i<9; i++){
				if(notes[i][j][n]){
					count++ ;
					if(ligne1[j]==-1){
						ligne1[j] = i;
					}
					else{
						ligne2[j] = i;
					}
				}
			}
			if (count == 2){
				i_dep = ligne1[j];
				j_dep = j;
				is_a_chain_column[j] = true;
			}
		}
		
		bool is_a_chain_zone[9] = {false,false,false,false,false,false,false,false,false};
		int lignez1[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
		int lignez2[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
		int colonnez1[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
		int colonnez2[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
		for(int z = 0; z<9; z++){
			int count = 0;
			for(int c = 0; c<9; c++){
				if(notes[3*(z/3)+c/3][3*(z%3)+c%3][n]){
					count++ ;
					if(colonnez1[c]==-1){
						lignez1[c] = 3*(z/3)+c/3 ;
						colonnez1[c] = 3*(z%3)+c%3 ;
					}
					else{
						lignez2[c] = 3*(z/3)+c/3 ;
						colonnez2[c] = 3*(z%3)+c%3 ;
					}
				}
			}
			if (count == 2){
				i_dep = lignez1[z];
				j_dep = colonnez1[z];
				is_a_chain_zone[z] = true;
			}
		}

		// Deuxième partie : coloriage
		int i = i_dep ;
		int j = j_dep ;
		int** colour = malloc(9*sizeof(bool*));
		assert(colour!=NULL);
		for(int k = 0; k<9; k++){
			colour[k] = malloc(9*sizeof(bool));
			assert(colour[k]!=NULL);
			for(int l =0; l<9; l++){
				colour[k][l] = 0 ;
			}
		}
		colour[i_dep][j_dep] = 1 ;

		
		parcours(i, j, is_a_chain_line, is_a_chain_column, is_a_chain_zone,
		ligne1, ligne2, colonne1,colonne2, lignez1, lignez2, colonnez1, colonnez2, colour);
		
		


		
	}
	return false;
}



void parcours(int i, int j, bool* is_a_chain_line, bool* is_a_chain_column, 
	bool* is_a_chain_zone, int* ligne1, int* ligne2, int* colonne1, int* colonne2,  
	int* lignez1, int* lignez2, int* colonnez1, int* colonnez2, int** colour){
	
	if(is_a_chain_line[i]){
		int j2 ;
		if(colonne1[i] == j){
			j2 = colonne2[i];
		}
		else{
			j2 = colonne1[i];
		}
		if(colour[i][j2] == colour[i][j]){
				
		}
	}
}