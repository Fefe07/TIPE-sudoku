#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

/*La technique de box line reduction consiste à éliminer des indices sur une lignes ou une colonne car ils sont forcément présents sur cette ligne et dans une autre zone*/

void updateNotes(grid_t g, int row, int col);


bool boxLineReduction(grid_t g){

	// on parcourt les lignes
	for(int i = 0; i<9; i++){
		// on parcourt les valeurs
		for(int value = 0; value < 9 ; value ++){

			// on parcourt les zones
			int count = 0 ;
			int zone = -1 ;
			for(int z = 0; z<3; z++){
				// si il y a un indice dans la zone on incrémente le nombre de zone contenant l'indice 
				if (g->notes[i][3*z][value]||g->notes[i][3*z+1][value]||g->notes[i][3*z+2][value]){
					count ++ ;
					zone = z ;
				}
			}
			// si une seule zone contient des indices de même valeur, cela signifie que ces indices sont tous dans la même zone, la technique peut alors être appliquée 
			//il est inutile de compter le nombre de fois ou l'indice apparaît puisque cela fonctionne avec un seul indice
			if(count == 1){
				// on modifie le reste de la zone, en enlevant les indices de la valeur dans le reste de la zone 
				assert(zone!=-1);
				bool verif = false;
				for(int k=0; k<9;k++){
					if((k<3*(i%3) || k > 3*(i%3)+2) && g->notes[3*(i/3)+k/3][3*zone+k%3][value]){  
						g->notes[3*(i/3)+k/3][3*zone+k%3][value] = false;
						//une valeur à élaguer a été trouvé donc on spécifie que la technique a été utilisé 
						verif = true ;
					}
				}
				// uniquement si on a modifié quelque chose !
				if(verif){
					//printf("Technique : boxLineReduction line\n");
					//printf("ligne = %d, zone = %d, valeur = %d\n", i, zone + 3*(i/3), value+1);
					return true;
				}
			}
		}
	}
	// Les boucles suivantes sont les mêmes que précédemment, à la différence prés que l'on itère sur les colonnes au lieu de le faire sur les lignes
	// on parcourt les colonnes
	for(int j = 0; j<9; j++){
		// on parcourt les valeurs
		for(int value = 0; value < 9 ; value ++){

			// on parcourt les zones
			int count = 0 ;
			int zone = -1 ;
			for(int z = 0; z<3; z++){
				// si il y a un indice dans la zone
				if (g->notes[3*z][j][value]||g->notes[3*z+1][j][value]||g->notes[3*z+2][j][value]){
					count ++ ;
					zone = z ;
				}
			}
			// si une seule zone contient des indices
			if(count == 1){
				assert(zone!=-1);
				// on modifie le reste de la zone
				bool verif = false ;
				for(int k=0; k<9;k++){
					if(k%3 != j%3 && g->notes[3*zone+k/3][3*(j/3)+k%3][value]) {
						g->notes[3*zone+k/3][3*(j/3)+k%3][value] = false;
						verif = true ;
					}
				}
				// uniquement si on a modifié quelque chose !
				if(verif){
					//printf("Technique : boxLineReduction column\n");
					//printf("colonne = %d, zone = %d, valeur = %d\n", j, 3*zone +j/3, value+1);
					return true;
				}
			}
		}
	}
	return false ;
}