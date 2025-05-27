#include <stdbool.h>
#include<stdio.h>

struct grid_s {
	int** grid ;
	bool*** notes ;
	float* nb_techniques;
};
typedef struct grid_s* grid_t ;

bool swordfish(grid_t g){
	bool trouve = false ;

	// pour chaque chiffre
	for(int n = 1; n <= 9; n++){
		//printf("%d\n",n);
		// compteur des occurences de n dans les notes dans chaque ligne
		int countl[9] = {0,0,0,0,0,0,0,0,0};  


		// on parcourt les lignes
		for(int i = 0; i<9; i++){
			// on parcourt la ligne choisie
			for(int j = 0; j<9; j++){
				// si la case ij peut accueillir n (Attention au décalage d'indices !)
				if (g->notes[i][j][n-1]){
					countl[i] ++ ;
				}
			}
		}
		// pour toutes les paires de lignes
		for(int i1 = 0; i1<9; i1++){
			if(countl[i1] == 2 || countl[i1]==3){
				for(int i2 = i1+1; i2<9; i2++){
					if(countl[i2] == 2 || countl[i2]==3){
						for(int i3 = i2+1; i3<9; i3++){
							if(countl[i3] == 2 || countl[i3]==3){
								//printf("Triplet %d %d %d\n", i1, i2, i3);
								// si elles remplissent les conditions :
								// - différentes 
								// - avec deux indices chacune
								// - avec leurs deux indices sur la mêm colonne
								// alors on applique la technique
								bool place[9] = {false,false,false,false,false,false,false,false,false};
								int count = 0;
								for(int j = 0; j<9; j++){
									if (g->notes[i1][j][n-1]||g->notes[i2][j][n-1]||g->notes[i3][j][n-1]){
										place[j] = true;
										count ++;
									}
								}
								if(count <= 3){
									// normalement count == 3 mais dans le doute
									for(int j = 0; j<9; j++){
										// si on ne modifie rien, il ne faut pas renvoyer true !
										if(place[j]){
											for(int i = 0; i<9; i++){
												if((i != i1) && (i != i2) && (i!=i3) && g->notes[i][j][n-1]){
													g->notes[i][j][n-1] = false ;
													//printf("Technique : swordfish\n");
													//printf("On retire %d en %d %d\n", n, i, j);
													trouve = true ;
													
												}
											}
										}
									}
									if(trouve){
										return true;
									}
								}
							}
						}
					}
				}
			}
		}

		// compteur des occurences de n dans les notes dans chaque colonne
		int countc[9] = {0,0,0,0,0,0,0,0,0};  


		// on parcourt les colonnes
		for(int j = 0; j<9; j++){

			// on parcourt la colonne choisie
			for(int i = 0; i<9; i++){
				// si la case ij peut accueillir n (Attention au décalage d'indices !)
				if (g->notes[i][j][n-1]){
					countc[j] ++ ;
				}
			}
		}

		
		// pour toutes les paires de colonnes
		for(int j1 = 0; j1<9; j1++){
			if(countc[j1] == 2 || countc[j1]==3){
				for(int j2 = j1+1; j2<9; j2++){
					if(countc[j2] == 2 || countc[j2]==3){
						for(int j3 = j2+1; j3<9; j3++){
							if(countc[j3] == 2 || countc[j3]==3){
								//printf("Triplet %d %d %d\n", j1, j2, j3);
								// si elles remplissent les conditions :
								// - différentes 
								// - avec deux indices chacune
								// - avec leurs deux indices sur la même ligne
								// alors on applique la technique

								bool place[9] = {false,false,false,false,false,false,false,false,false};
								int count = 0;
								for(int i = 0; i<9; i++){
									if (g->notes[i][j1][n-1]||g->notes[i][j2][n-1]||g->notes[i][j3][n-1]){
										place[i] = true;
										count ++;
									}
								}

								
								if(count<=3){
									for(int i = 0; i <9; i++){
										if(place[i]){
											for(int j = 0; j<9; j++){
												// si on ne modifie rien, il ne faut pas renvoyer true !
												if((j != j1) && (j != j2) && (j!=j3) && g->notes[i][j][n-1]){
													g->notes[i][j][n-1] = false ;
													//printf("Technique : swordfish\n");
													//printf("On retire %d en %d %d\n", n, i, j);
													trouve = true ;
												}
											}
										}
									}
									if(trouve){
										return true ;
									}
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