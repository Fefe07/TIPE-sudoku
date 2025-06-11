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

int group(int i, int j) { return 3 * (i / 3) + j / 3; } // ok
// renvoie le numéro du sous-groupe (de 0 à 8)

bool same_zone(int i1, int j1, int i2, int j2) { // ok
	// i1, i2, j1, j2 entre 0 et 8
	return (i1 == i2) || (j1 == j2) || (group(i1, j1) == group(i2, j2));
} // même ligne ou même colonne ou même sous-groupe

void printGrid(int **grid); // ok

bool lastFreeCell(grid_t g);
bool lastRemainingCell(grid_t g);
bool lastPossibleNumber(grid_t g);

void updateNotes(grid_t g, int row, int col);
void initialize_notes(grid_t g);
void free_grid(int **grid);
void free_notes(bool ***notes);

bool hiddenSingle(int **grid, bool ***notes, float *nb_tech);
bool nakedSingle(int **grid, bool ***notes, float *nb_tech);

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
bool solve_notes(grid_t g, bool(**techniques)(grid_t g), int n);
bool backtrack(int **grid, bool ***notes, float *nb_techniques);
void solve_simple_notes_backtrack(grid_t g, bool(**techniques)(grid_t g), int n);

int **lecture(int n, char *nom_de_la_base);
typedef struct {
	float D_TO;
	float D_TR;
	int **grid;
} grid_diffs;
grid_diffs lecture_db_diffs(int n, char *nom_de_la_base, int cap);

typedef struct {
	int difficulty;
	int **grid;
} grid_one_diff;
grid_one_diff lecture_db_B(int n, char *nom_de_la_base, int cap);
grid_one_diff lecture_db_C(int n, char *nom_de_la_base, int cap);



int **grid_of_string(char *s);


void updateNotes(grid_t g, int row, int col);

void print_notes(bool ***notes);

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
float assess_repartition(int** grid);
float assess_repartition_valeurs(int** grid);
int assess_nb_clues(int** grid);

void solve_cnf(k_cnf f, var(*h)(k_cnf), int* nb_disjonctions, int* nb_quines);
void free_k_cnf(k_cnf f);
/* Random */
var heuristique_0(k_cnf f);
/* Minimum */
var heuristique_1(k_cnf f);
/* Maximum */
var heuristique_2(k_cnf f);

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
void calcule_coeffs_neg(float* coeffs, float* coeffs_first_use, float** results, float* difficulties, int results_size);
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
		//coeffs_first_use[i] = (rand() % 100 + 10) / 50. ;	
		coeffs_first_use[i] = 0;
	}
	//coeffs_first_use[2] = 0;
	//coeffs_first_use[0] = 0;
	return coeffs_first_use;
}


void test_heuristiques(){
	FILE *h = fopen("results_heuristics/db_B_heur_2_400.txt", "w");
	int results_size = 400 ;

	for(int nbGrille = 0; nbGrille<results_size; nbGrille++){
		grid_one_diff g1 = lecture_db_B(nbGrille+2, "grilles/db_B.csv", 5);
		k_cnf phi = sudoku_to_cnf(g1.grid);
		printGrid(g1.grid);
		print_k_cnf(phi);

		int profondeur_max = 42;

		int* nb_disjonctions = malloc(profondeur_max*sizeof(int));
		assert(nb_disjonctions!=NULL);
		int* nb_quines = malloc(profondeur_max*sizeof(int));
		assert(nb_quines!=NULL);
		for(int i = 0; i<profondeur_max; i++){
			nb_disjonctions[i] = 0; 
			nb_quines[i] = 0;
		}

		solve_cnf(phi, &heuristique_2, nb_disjonctions, nb_quines);
		print_tab_int(nb_disjonctions, profondeur_max);
		print_tab_int(nb_quines, profondeur_max);

		for(int i = 0; i<profondeur_max; i++){
			fprintf(h, "%d,  ",nb_disjonctions[i]);
		}
		for(int i = 0; i<profondeur_max; i++){
			fprintf(h, "%d,  ",nb_quines[i]);
		}
		fprintf(h,"%d, ", g1.difficulty);
		if(nbGrille<results_size-1){
			fprintf(h,";\n");
		}

		free_k_cnf(phi);
		free(nb_disjonctions);
		free(nb_quines);
		free_grid(g1.grid);
	}
	fclose(h);
}

void test_techniques(){
	int n = 12 ;
	bool(**techniques)(grid_t) = malloc(12*sizeof(bool(*)(grid_t)));
	assert(techniques!=NULL);
	techniques[0] = &lastFreeCell ;
	techniques[1] = (bool(*)(grid_t))&nakedSingle ;
	techniques[2] = (bool(*)(grid_t))&hiddenSingle ;
	techniques[3] = (bool(*)(grid_t))&pointingPair ;
	techniques[4] = (bool(*)(grid_t))&nakedPair ;
	techniques[5] = (bool(*)(grid_t))&hiddenPair ;
	techniques[6] = (bool(*)(grid_t))&nakedTriple ;
	techniques[7] = (bool(*)(grid_t))hiddenTriple ;
	techniques[8] = (bool(*)(grid_t))&boxLineReduction ;
	techniques[9] = (bool(*)(grid_t))x_wing ;
	techniques[10] = (bool(*)(grid_t))y_wing ;
	techniques[11] = (bool(*)(grid_t))swordfish ;



	srand(time(NULL));
	float *coeffs = cree_coeffs();
	float *coeffs_first_use = cree_coeffs_first_use();

	int results_size = 1000 ;
	FILE *f = fopen("resultats.txt", "w");


	float **results = malloc(results_size * sizeof(float *));
	assert(results != NULL);
	float *difficulties = malloc(results_size * sizeof(float));
	assert(difficulties != NULL);

	for (int nbGrille = 0; nbGrille < results_size ; nbGrille++) {
		if(nbGrille%100 == 0){
			printf("Grille n %d\n", nbGrille);
		}
		grid_one_diff g = lecture_db_B(nbGrille+2, "grilles/db_B.csv", 10);
		//int** g2 = lecture(nbGrille, "grilles/top50000.txt");
		
		//printGrid(g.grid);
		grid_t g2 = malloc(sizeof(struct grid_s));
		assert(g2!=NULL);
		g2->grid = g.grid ;
		difficulties[nbGrille] = (float) g.difficulty;
		g2->nb_techniques = malloc(13 * sizeof(float));
		assert(g2->nb_techniques!=NULL);
		for (int i = 0; i < 13; i++) {
			g2->nb_techniques[i] = 0.;
		}
		
		solve_simple_notes_backtrack(g2, techniques, 12);	
		if(nbGrille%100 == 0){
			print_tab_float(g2->nb_techniques, 13);
		}
		// print_tab_int(nb_tech, 10);
		results[nbGrille] = g2->nb_techniques;
		for (int i = 0; i < 13; i++) {
			fprintf(f, "%f, ", g2->nb_techniques[i]);
		}
		
		fprintf(f, "%f ;\n", difficulties[nbGrille]);
		
		free_grid(g.grid);
		free(g2);
	}
	
	for(int i = 0; i<13; i++){
		int count = 0 ;
		int n = 0;
		for(int j = 0; j<results_size; j++){
			count += (int) results[j][i];
			if (results[j][i]>0.01){
				n ++;
			}
		}
		printf("%d, %d \n", count, n);
	}
	printf("\n");
	

	calcule_coeffs_neg(coeffs,coeffs_first_use,results,difficulties, results_size);
	
	/* Calcul des coefficients par descente de gradient au formalisme douteux */
	for (int i = 0; i < 13; i++) {
		fprintf(f, "%f, ", coeffs[i]);
	}
	fprintf(f,"42;\n");
	for (int i = 0; i < 13; i++) {
		fprintf(f, "%f, ", coeffs_first_use[i]);
	}
	fprintf(f,"42\n");

	fclose(f);

	free(coeffs);
	free(coeffs_first_use);
	for(int i = 0; i<results_size; i++){
		free(results[i]);
	}
	free(results);
	free(difficulties);
	free(techniques);	
}

void test_criteres(float* coeffs, float* coeffs_first_use){
	FILE* g = fopen("results_db_0/results_criteria.txt", "w");
	int results_size = 344 ;
	for(int i = 0; i<results_size; i++){
		/* La résolution altère la grille donnée en argument*/
		//printf("################## Grille n° %d ############\n",i);
		grid_diffs g1 = lecture_db_diffs(i+2, "grilles/Base_de_donnees_evaluees.csv", 42);
		int nb_clues = assess_nb_clues(g1.grid);

		float f2 = assess_cnf(g1.grid);
		int nb_notes = assess_nb_notes(g1.grid);
		float repartition = assess_repartition(g1.grid);
		float repartition_valeurs = assess_repartition_valeurs(g1.grid);
		float f1 = assess_techniques(g1.grid, coeffs, coeffs_first_use);
		fprintf(g, "%f , %f , %f , %d, %d , %f, %f ",g1.D_TR, f1, f2,nb_clues, nb_notes, repartition, repartition_valeurs);
		if(i<results_size-1){
			fprintf(g,";\n");
		}
	}
	fclose(g);
}

int main() {
	
	test_heuristiques();

	//test_techniques() ;
	
	// test_criteres();
	
	return 0;
}
