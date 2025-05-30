#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

void updateNotes(grid_t g, int row, int col);
void printGrid(int** grid);
void consequences_new_number(int **grid, bool ***notes, int i, int j, float* nb_techniques);

/*Fonction hidden Single 
Entrée : une grille et les notes associèes 
Sortie : Booléen
Si une note n'est présente qu'une seule fois dans une ligne, colonne ou zones. Alors elle ne peut être ailleurs et aucune autre notes de peut être dans sa case */
int hiddenSingle(grid_t g){
	// renvoie true si on parvient à placer un chiffre avec la technique du hidden single et place ledit chiffre
	// renvoie false sinon

	for(int i = 0; i <9; i++){ // parcourt les lignes
		//on stocke les valeurs possibles sur la ligne
		bool possibilities[9] = {true, true, true, true, true, true, true, true, true};
		int nb_pos = 9;
		for (int j = 0; j < 9; j++){
			//si la valeur est présente sur la ligne, on met sa valeur de possibilities à false 
			if(g->grid[i][j]!= 0){
				possibilities[g->grid[i][j]-1] = false ;
				nb_pos -- ;
			}
		}
		
	//on cherche pour chaque valeur non présente si la note est unique 
		for(int value = 1; value <= 9; value ++){
			if(possibilities[value-1]){
				int count = 0 ;
				int col ;
				for(int j = 0; j<9; j++){
					//lorsque la notes est présente sur une ligne, on itère le compteur
					if(g->notes[i][j][value - 1]){
						count ++;
						col = j ;
					}
				}
				if (count == 1){ // si un seul emplacement est disponible alors on place l'indice 
					g->grid[i][col] = value ;
					//printf("Technique : hiddenSingle1\n");
					//printf("row = %d, col = %d, val = %d\n", i, col, value);
					//consequences_new_number(grid, notes, i, col, nb_techniques);
					updateNotes(g, i, col); //on renouvelle la grille de notes après avoir placé l'indice 
					assert(nb_pos>=1);
					return nb_pos;
				}
			}
		}
	}
//les boucles suivantes fonctionnes sur le même principes à la différences près que les boucles itèrent sur les colonnes et les zones 
	for(int j = 0; j <9; j++){ // parcourt les colonnes
		bool possibilities[9] = {true, true, true, true, true, true, true, true, true};
		int nb_pos = 9;
		for (int i = 0; i < 9; i++){
			if(g->grid[i][j]!= 0){
				possibilities[g->grid[i][j]-1] = false ;
				nb_pos--;
			}
		}

		for(int value = 1; value <= 9; value ++){
			if(possibilities[value-1]){
				int count = 0 ;
				int row ;
				for(int i = 0; i<9; i++){
					if(g->notes[i][j][value - 1]){
						count ++;
						row = i ;
					}
				}
				if (count == 1){ // si un seul emplacement est disponible
					g->grid[row][j] = value ;
					//printf("Technique : hiddenSingle2\n");
					//printf("row = %d, col = %d, val = %d\n", row, j, value);
					updateNotes(g, row, j);
					//consequences_new_number(grid, notes, row, j, nb_techniques);
					assert(nb_pos>=1);
					return nb_pos;
				}
			}
		}
	}

	for(int z = 0; z <9; z++){ // parcourt les zones
		bool possibilities[9] = {true, true, true, true, true, true, true, true, true};
		int nb_pos = 9;
		for (int i = 0; i < 3; i++){
			for(int j = 0; j<3; j++){
				if(g->grid[3*(z/3)+i][3*(z%3) + j]!= 0){
					possibilities[g->grid[3*(z/3)+i][3*(z%3) + j] - 1] = false ;
					nb_pos -- ;
				}
			}
		}

		for(int value = 1; value <= 9; value ++){
			if(possibilities[value-1]){
				int count = 0 ;
				int row ;
				int col ;
				for(int i = 0; i<3; i++){
					for(int j = 0; j<3 ; j++){
						if(g->notes[3*(z/3)+i][3*(z%3) + j][value - 1]){
							count ++;
							row = 3*(z/3) + i ;
							col = 3*(z%3) + j ;
						}
					}
				}
				if (count == 1){ // si un seul emplacement est disponible
					g->grid[row][col] = value ;
					//printf("Technique : hiddenSingle3\n");
					//printf("row = %d, col = %d, val = %d\n", row, col, value);
					updateNotes(g, row, col);
					//consequences_new_number(grid, notes, row, col, nb_techniques);
					assert(nb_pos>=1);
					return nb_pos;
				}
			}
		}
	}
	return false ;
}



// itère hiddenSingle autour d'une seule case, pour une seul valeur
int hiddenSingle_one_cell(int** grid, bool*** notes, int i, int j, int k, float* nb_techniques){
	// renvoie true si on parvient à placer un chiffre avec la technique du hidden single et place ledit chiffre
	// renvoie false sinon
	//printf("hiddenSingle_one_cell : i = %d, j = %d, k = %d\n", i, j, k);
	
	//on stocke les valeurs possibles sur la ligne
	bool possible = true;
	int nb_pos = 9;
	for (int j1 = 0; j1 < 9; j1++){
		//si la valeur est présente sur la ligne, on met sa valeur de possibilities à false 
		if(grid[i][j1]== k+1){
			possible=false ;
			nb_pos-- ;
		}
	}
//on cherche pour chaque valeur non présente si la note est unique 
	
	if(possible){
		int count = 0 ;
		int col ;
		for(int j1 = 0; j1<9; j1++){
			//lorsque la note est présente sur une ligne, on itère le compteur
			if(notes[i][j1][k]){
				count ++;
				col = j1 ;
			}
		}
		if (count == 1){ // si un seul emplacement est disponible alors on place l'indice 
			
			//printf("Technique : hiddenSingle1_one_cell\n");
			//printf("row = %d, col = %d, val = %d\n", i, col, k+1);
			grid[i][col] = k+1 ;
			//printGrid(grid);
			//updateNotes(grid, notes, i, col); //on renouvelle la grille de notes après avoir placé l'indice 
			//consequences_new_number(grid, notes, i, col, nb_techniques);
			return nb_pos;
		}
	}
	
	
//les boucles suivantes fonctionnes sur le même principes à la différences près que les boucles itèrent sur les colonnes et les zones 

	bool possibilities1[9] = {true, true, true, true, true, true, true, true, true};
	nb_pos = 9;
	for (int i1 = 0; i1 < 9; i1++){
		if(grid[i1][j]!= 0){
			possibilities1[grid[i1][j]-1] = false ;
			nb_pos -- ;
		}
	}

	//for(int value = 1; value <= 9; value ++){
		if(possibilities1[k]){
			int count = 0 ;
			int row ;
			for(int i1 = 0; i1<9; i1++){
				if(notes[i1][j][k]){
					count ++;
					row = i1 ;
				}
			}
			if (count == 1){ // si un seul emplacement est disponible
				
				//printf("Technique : hiddenSingle2_one_cell\n");
				//printf("row = %d, col = %d, val = %d\n", row, j, k+1);
				grid[row][j] = k+1 ;
				//printGrid(grid);
				//updateNotes(grid, notes, row, j);
				//consequences_new_number(grid, notes, row, j, nb_techniques);
				return nb_pos;
			}
		}
	//}
	

	int z = (3*(i/3)) + j/3 ;
	//printf("z = %d\n", z);
	bool possibilities2[9] = {true, true, true, true, true, true, true, true, true};
	nb_pos = 9;
	for (int i1 = 0; i1 < 3; i1++){
		for(int j1 = 0; j1<3; j1++){
			if(grid[3*(z/3)+i1][3*(z%3) + j1]!= 0){
				possibilities2[grid[3*(z/3)+i1][3*(z%3) + j1] - 1] = false ;
				nb_pos -- ;
			}
		}
	}

	//for(int k = 1; k <= 9; k ++){
		if(possibilities2[k]){
			int count = 0 ;
			int row ;
			int col ;
			for(int i1 = 0; i1<3; i1++){
				for(int j1 = 0; j1<3 ; j1++){
					if(notes[3*(z/3)+i1][3*(z%3) + j1][k]){
						count ++;
						row = 3*(z/3) + i1 ;
						col = 3*(z%3) + j1 ;
					}
				}
			}
			if (count == 1){ // si un seul emplacement est disponible
				
				//printf("Technique : hiddenSingle3_one_cell\n");
				//printf("row = %d, col = %d, val = %d\n", row, col, k+1);
				grid[row][col] = k+1 ;
				//printGrid(grid);
				//updateNotes(grid, notes, row, col);
				//consequences_new_number(grid, notes, row, col, nb_techniques);
				return nb_pos;
			}
		}
	//}
	
	return false ;
}
