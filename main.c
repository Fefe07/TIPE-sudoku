#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int group(int i, int j);												// ok
bool same_zone(int i1, int j1, int i2, int j2); // ok
bool check(int **grid, int i, int j);					 // ok

void printGrid(int **grid); // ok

bool lastRemainingCell(int **grid);
bool lastFreeCell(int **grid);
bool lastPossibleNumber(int **grid);

bool ***createNotes();
void updateNotes(int **grid, bool ***notes, int row, int col);
bool ***initialize_notes(int **grid);
void free_grid(int **grid);
void free_notes(bool ***notes);

bool hiddenSingle(int **grid, bool ***notes, float *nb_tech);
float nakedSingle(int **grid, bool ***notes, float *nb_tech);

bool hiddenPair(bool ***notes);
bool nakedPair(bool ***notes);

bool hiddenTriple(bool ***notes);
bool nakedTriple(bool ***notes);

bool pointingPair(bool ***notes);
bool boxLineReduction(bool ***notes);

bool x_wing(bool ***notes);
bool y_wing(bool ***notes);
bool swordfish(bool ***notes);

bool solve(int **grid);
bool solve_notes(int **grid, bool ***notes, float *nb_techniques);
bool backtrack(int **grid, bool ***notes, float *nb_techniques);
void solve_simple_notes_backtrack(int **grid, float *nb_tech);

int **lecture(int n, char *nom_de_la_base);
typedef struct {
	float D_TO;
	float D_TR;
	int **grid;
} grid_diffs;
grid_diffs lecture_db_diffs(int n, char *nom_de_la_base);

typedef struct {
	int difficulty;
	int **grid;
} grid_one_diff;
grid_one_diff lecture_db_B(int n, char *nom_de_la_base);

typedef struct {
	int technique;
	int *positions; // le contenu de ce tableau va varier suivant les fonctions
} tech_occurence;

int **grid_of_string(char *s);

int difficulty = 0;
void increase_difficulty(int n) { difficulty += n; }
void updateNotes(int **grid, bool ***notes, int row, int col);

void affiche_notes(bool ***notes);

typedef struct var_s{
    /* Une variable est de la forme p_i,j,k, elle indique si la case i,j contient k */
    /* 0 <= i,j < 9 */
    /* 1 <= k <= 9 */
    int i;
    int j;
    int k;
}var;

typedef struct {
    /* On représente un litéral par une variable (un entier) 
    et une positivite (1 si litéral positif, 0 si litéral négatif)
    On représente donc une clause par un tableau de litéraux */
    int nb_lit ;
    var* vars ;
    bool* positif ;
}clause;


typedef struct {
    /* Ce type est beaucoup moins général ; le filtre est spécifique à cet usage */
    int nb_var ;
    var* vars ;
    bool* filtre ;
}clause_1in9;


struct k_cnf_s {
    int m ; //nb_clauses
    int k ; 
    clause* clauses ;
};
typedef struct k_cnf_s* k_cnf; 

k_cnf sudoku_to_cnf(int** grid);
void print_k_cnf(k_cnf f);
float assess_cnf(int** grid);

float assess_techniques(int** grid, float* coeffs, float* coeffs_first_use);
int assess_nb_notes(int** grid);
int assess_repartition(int** grid);

int group(int i, int j) { return 3 * (i / 3) + j / 3; }
// renvoie le numéro du sous-groupe (de 0 à 8)

bool same_zone(int i1, int j1, int i2, int j2) {
	// i1, i2, j1, j2 entre 0 et 8
	return (i1 == i2) || (j1 == j2) || (group(i1, j1) == group(i2, j2));
} // même ligne ou même colonne ou même sous-groupe

void print_tab_int(int *tab, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d	", tab[i]);
	}
	printf("\n");
}
void print_tab_float(float *tab, int size) {
	for (int i = 0; i < size; i++) {
		printf("%.4f,  ", tab[i]);
	}
	printf("\n");
}

float calcule_cout(float *coeffs, float *coeffs_first_use, float **results, float *difficulties, int results_size);

void calcule_coeffs(float* coeffs, float* coeffs_first_use, float** results, float* difficulties, int results_size);

float *cree_coeffs() {
	/* Tableau des techniques :
	0 - last Free Cell
	1 - nakedSingle
	2 - hiddenSingle
	3 - nakedPair
	4 - nakedTriple
	5 - hiddenPair
	6 - hiddenTriple
	7 - pointing Pair / Triple
	8 - Box line reduction
	9 - X-Wing
	10 - Y-wing
	11 - Swordfish
	12 - Backtracking
	*/
	float *coeffs = malloc(13 * sizeof(float));
	assert(coeffs != NULL);
	for(int i = 0; i<13; i++){
		coeffs[i] = (rand() % 100 + 10) / 50. ; 
	}
	return coeffs;
}

float *cree_coeffs_first_use() {
	float *coeffs_first_use = malloc(13 * sizeof(float));
	assert(coeffs_first_use != NULL);
	for(int i = 0; i<13; i++){
		coeffs_first_use[i] = (rand() % 100 + 10) / 50. ;	
		//coeffs_first_use[i] = 0;
	}
	//coeffs_first_use[2] = 0;
	//coeffs_first_use[0] = 0;
	return coeffs_first_use;
}



int main() {
	srand(time(NULL));
	float *coeffs = cree_coeffs();
	float *coeffs_first_use = cree_coeffs_first_use();

	int results_size = 1000;
	FILE *f = fopen("resultats.txt", "w");

	/*
	int **grid = grid_of_string("645010893738459621219638745597060184481975000326"
															"841579902080010803190000164020908");
	float *t = malloc(12 * sizeof(float));
	for (int i = 0; i < 12; i++) {
		t[i] = 0.;
	}
	solve_notes(grid, initialize_notes(grid), t);
	printGrid(grid);
	print_tab_float(t, 12);
	*/
	float average_dtr = 1.458184 ;
	
	float **results = malloc(results_size * sizeof(float *));
	assert(results != NULL);
	float *difficulties = malloc(results_size * sizeof(float));
	assert(difficulties != NULL);

	for (int nbGrille = 0; nbGrille < results_size ; nbGrille++) {
		if(nbGrille%100 == 0){
			printf("Grille n %d\n", nbGrille);
		}
		grid_one_diff g = lecture_db_B(nbGrille+2, "grilles/db_B.csv");
		//int** g2 = lecture(nbGrille, "grilles/top50000.txt");
		
		//printGrid(g.grid);
		difficulties[nbGrille] = (float) g.difficulty;

		float *nb_tech = malloc(13 * sizeof(float));
		for (int i = 0; i < 13; i++) {
			nb_tech[i] = 0.;
		}
		//printGrid(g.grid);
		solve_simple_notes_backtrack(g.grid, nb_tech);
		if(nbGrille%100 == 0){
			print_tab_float(nb_tech, 13);
		}
		// print_tab_int(nb_tech, 10);
		results[nbGrille] = nb_tech;
		for (int i = 0; i < 13; i++) {
			fprintf(f, "%.4f, ", nb_tech[i]);
		}
		
		fprintf(f, "%d ;\n", g.difficulty);
		
		free_grid(g.grid);
	}
	

	calcule_coeffs(coeffs,coeffs_first_use,results,difficulties, results_size);
	/* Calcul des coefficients par descente de gradient au formalisme douteux */
	for (int i = 0; i < 13; i++) {
		fprintf(f, "%.4f, ", coeffs[i]);
	}
	fprintf(f,"42;\n");
	for (int i = 0; i < 13; i++) {
		fprintf(f, "%.4f, ", coeffs_first_use[i]);
	}
	fprintf(f,"42\n");
	fclose(f);

	

	FILE* g = fopen("results_db_0/results_0_5_05.txt", "w");
	for(int i = 0; i<100; i++){
		/* La résolution altère la grille donnée en argument*/
		//printf("################## Grille n° %d ############\n",i);
		grid_one_diff g1 = lecture_db_B(i+2, "grilles/db_B.csv");
		grid_one_diff g2 = lecture_db_B(i+2, "grilles/db_B.csv");
		float f1 = assess_techniques(g1.grid, coeffs, coeffs_first_use);
		float f2 = assess_cnf(g2.grid);
		int nb_notes = assess_nb_notes(g2.grid);
		int repartition = assess_repartition(g2.grid);
		fprintf(g, "%d ; %f ; %f ; %d ; %d\n",g1.difficulty, f1, f2, nb_notes, repartition);
	}
	fclose(g);


	free(coeffs);
	free(coeffs_first_use);
	for(int i = 0; i<results_size; i++){
		free(results[i]);
	}
	free(results);
	free(difficulties);

	return 0;
}
