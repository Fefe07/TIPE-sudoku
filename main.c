#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

float assess_techniques(int** grid, float* coeffs, float* coeffs_used);


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
		printf("%.4f,	", tab[i]);
	}
	printf("\n");
}

float calcule_cout(float *coeffs, float *coeffs_used, float **results, float *difficulties, int results_size);

float *cree_coeffs() {
	/* Tableau des techniques :
	0 - nakedSingle
	1 - hiddenSingle
	2 - nakedPair
	3 - nakedTriple
	4 - hiddenPair
	5 - hiddenTriple
	6 - pointing Pair / Triple
	7 - Box line reduction
	8 - X-Wing
	9 - Backtracking
	*/
	float *coeffs = malloc(13 * sizeof(float));
	assert(coeffs != NULL);
	for(int i = 0; i<13; i++){
		coeffs[i] = (rand() % 100) / 50. ; 
	}
	return coeffs;
}

float *cree_coeffs_used() {
	float *coeffs_used = malloc(13 * sizeof(float));
	assert(coeffs_used != NULL);
	for(int i = 0; i<13; i++){
		coeffs_used[i] = (rand() % 100 + 10) / 50. ;	
	}
	coeffs_used[2] = 0;
	coeffs_used[0] = 0;
	return coeffs_used;
}

int main() {
	srand(time(NULL));
	float *coeffs = cree_coeffs();
	float *coeffs_used = cree_coeffs_used();

	int results_size = 300;
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

		printf("Grille n %d\n", nbGrille);
		grid_diffs g = lecture_db_diffs(nbGrille+2, "grilles/Bases_de_donnees_evaluees.csv");
		//int** g2 = lecture(nbGrille, "grilles/top50000.txt");
		
		//printGrid(g.grid);
		difficulties[nbGrille] = g.D_TR;

		float *nb_tech = malloc(13 * sizeof(float));
		for (int i = 0; i < 13; i++) {
			nb_tech[i] = 0.;
		}
		//printGrid(g.grid);
		solve_simple_notes_backtrack(g.grid, nb_tech);
		// print_tab_int(nb_tech, 10);
		results[nbGrille] = nb_tech;
		for (int i = 0; i < 13; i++) {
			fprintf(f, "%.4f ; ", nb_tech[i]);
		}
		fprintf(f, "%f ; %f ;\n", g.D_TO, g.D_TR);
		free_grid(g.grid);
	}
	fclose(f);
	printf("Coucou\n");

	/* Calcul des coefficients par descente de gradient au formalisme douteux */
	float cout = calcule_cout(coeffs, coeffs_used, results, difficulties, results_size);
	float ancien_cout = cout + 42;
	int i = 0;
	while (ancien_cout > cout) {
		ancien_cout = cout ;
		for (int j = 0; j <13; j++) {
			//for (int k = 0; k < 100; k++) {
				coeffs[j] *= 0.99;
				float nouveau_cout = calcule_cout(coeffs, coeffs_used, results, difficulties, results_size);
				if (nouveau_cout > cout) {
					coeffs[j] /= 0.99;
				} else {
					cout = nouveau_cout;
				}
				coeffs[j] *= 1.01;
				nouveau_cout = calcule_cout(coeffs, coeffs_used, results, difficulties, results_size);
				if (nouveau_cout >= cout) {
					coeffs[j] /= 1.01;
				} else {
					cout = nouveau_cout;
				}
				coeffs_used[j] *= 0.99;
				nouveau_cout = calcule_cout(coeffs, coeffs_used, results, difficulties, results_size);
				if (nouveau_cout > cout) {
					coeffs_used[j] /= 0.99;
				} else {
					cout = nouveau_cout;
				}
				coeffs_used[j] *= 1.01;
				nouveau_cout = calcule_cout(coeffs, coeffs_used, results, difficulties, results_size);
				if (nouveau_cout >= cout) {
					coeffs_used[j] /= 1.01;
				} else {
					cout = nouveau_cout;
				}
			//}
		}
		if(i%100 == 0){
			printf("i = %d : \n", i);
			print_tab_float(coeffs, 13);
			print_tab_float(coeffs_used, 13);
			printf("Cout = %f\n", cout);
			//float ec	= sqrt(cout);
			//printf("ecart-type = %f\n", ec);
			fflush(stdout);
		}
		i++;
	}
	printf("Coucou\n");

	int** grid42 = grid_of_string("081600090000000000004037600600400500030000070007002004005210300000000000070004810");
	k_cnf h = sudoku_to_cnf(grid42);
	print_k_cnf(h); 
	printGrid(grid42);

	FILE* g = fopen("results_sudoku_evaluated.txt", "w");
	for(int i = 0; i<100; i++){
		/* La résolution altère la grille donnée en argument*/
		grid_diffs g1 = lecture_db_diffs(i+2, "grilles/Bases_de_donnees_evaluees.csv");
		grid_diffs g2 = lecture_db_diffs(i+2, "grilles/Bases_de_donnees_evaluees.csv");
		float f1 = assess_techniques(g1.grid, coeffs, coeffs_used);
		float f2 = assess_cnf(g2.grid);
		fprintf(g, "%f ; %f ; %f ; %f\n",g1.D_TR,g1.D_TO, f1, f2);
	}
	fclose(g);


	free(coeffs);
	free(coeffs_used);
	for(int i = 0; i<results_size; i++){
		free(results[i]);
	}
	free(results);
	free(difficulties);

	return 0;
}
