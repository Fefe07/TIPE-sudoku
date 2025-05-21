#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



bool x_wing(bool ***notes){
	bool trouve = false ;

	
	// pour chaque chiffre
	for(int n = 1; n <= 9; n++){
		
		// compteur des occurences de n dans les notes dans chaque ligne
		int countl[9] = {0,0,0,0,0,0,0,0,0};  

		// indices de deux colonnes contenat des indices (utile si count[i] = 2)
		int colonne1[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
		int colonne2[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
		
		// on parcourt les lignes
		for(int i = 0; i<9; i++){
			// on parcourt la ligne choisie
			for(int j = 0; j<9; j++){
				// si la case ij peut accueillir n (Attention au décalage d'indices !)
				if (notes[i][j][n-1]){
					countl[i] ++ ;
					if(colonne1[i]==(-1)){
						colonne1[i] = j;
					}
					else{
						colonne2[i] = j;
					}
				}
			}
		}
		
		// pour toutes les paires de lignes
		for(int i1 = 0; i1<9; i1++){
			for(int i2 = 0; i2<9; i2++){
				// si elles remplissent les conditions :
				// - différentes 
				// - avec deux indices chacune
				// - avec leurs deux indices sur la mêm colonne
				// alors on applique la technique
				if((i1!=i2) && (countl[i1] ==2) && (countl[i2]==2)){
					if((colonne1[i1] == colonne1[i2]) && (colonne2[i1] == colonne2[i2])){
						for(int i = 0; i<9; i++){
							// si on ne modifie rien, il ne faut pas renvoyer true !
							if((i != i1) && (i != i2) && ((notes[i][colonne1[i1]][n-1] == true) || (notes[i][colonne2[i1]][n-1] == true))){
								notes[i][colonne1[i1]][n-1] = false ;
								notes[i][colonne2[i1]][n-1] = false ;
								//printf("Technique : x_wing\n");
								//printf("On retire %d ligne %d et colonnes %d et %d\n", n, i, colonne1[i1], colonne2[i1]);
								if (trouve == false){
									trouve = true ;
								}
							}
						}
					}
				}
				
			}
		}

		// compteur des occurences de n dans les notes dans chaque colonne
		int countc[9] = {0,0,0,0,0,0,0,0,0};  

		// indices de deux lignes contenat des indices (utile si count[i] = 2)
		int ligne1[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
		int ligne2[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

		// on parcourt les colonnes
		for(int j = 0; j<9; j++){

			// on parcourt la colonne choisie
			for(int i = 0; i<9; i++){
				// si la case ij peut accueillir n (Attention au décalage d'indices !)
				if (notes[i][j][n-1]){
					countc[j] ++ ;
					if(ligne1[j]==-1){
						ligne1[j] = i;
					}
					else{
						ligne2[j] = i;
					}
				}
			}
		}
		// pour toutes les paires de colonnes
		for(int j1 = 0; j1<9; j1++){
			for(int j2 = 0; j2<9; j2++){
				// si elles remplissent les conditions :
				// - différentes 
				// - avec deux indices chacune
				// - avec leurs deux indices sur la même ligne
				// alors on applique la technique
				if((j1!=j2) && (countc[j1] == 2) && (countc[j2]==2)){
					if((ligne1[j1] == ligne1[j2]) && (ligne2[j1] == ligne2[j2])){
						for(int j = 0; j<9; j++){
							// si on ne modifie rien, il ne faut pas renvoyer true !
							if((j != j1) && (j != j2) && ((notes[ligne1[j1]][j][n-1] == true) || (notes[ligne2[j1]][j][n-1] == true))){
								notes[ligne1[j1]][j][n-1] = false ;
								notes[ligne2[j1]][j][n-1] = false ;
								//printf("Technique : x_wing\n");
								//printf("On retire %d lignes %d et %d  et colonne %d\n", n, ligne1[j1], ligne2[j1], j);
								if (trouve == false){
									trouve = true ;
								}
							}
						}
					}
				}

			}
		}		
	}
	return trouve ;
}