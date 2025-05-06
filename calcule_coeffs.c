#include<stdio.h>
#include<time.h>
#include<math.h>
#include<assert.h>
#include<stdlib.h>

void print_tab_float(float* tab, int size);
float calcule_cout(float* coeffs, float* coeffs_first_use, float** results, float* difficulties, int results_size);


float* copy(float* tab, int size){
    float* t = malloc(size*sizeof(float));
    assert(t!=NULL);
    for(int i = 0; i<size; i++){
        t[i] = tab[i];
    }
    return t;
}

void calcule_coeffs(float* coeffs, float* coeffs_first_use, float** results, float* difficulties, int results_size){
    /* Calcule les valeurs des tableaux coeffs et coeffs_first_use minimisant l'écart au difficultés, */
    /* selon les moindres carrés */
    /* Ce calcul se fera à l'aide d'une recherche linéaire */
    //srand(time(NULL));
    float cout = calcule_cout(coeffs, coeffs_first_use, results, difficulties, results_size);
    float* best_coeffs = copy(coeffs, 13);
    float* best_coeffs_first_use = copy(coeffs_first_use, 13);
    float best_cout = cout ;
	int i = 0;
    float T = 10. ;
	while (T > 0.00000001) {
		float* nouveaux_coeffs = copy(coeffs, 13);
        float* nouveaux_coeffs_first_use = copy(coeffs_first_use,13);

		for (int j = 0; j <13; j++) {
			nouveaux_coeffs[j] *= expf((-10 + (rand() % 21))/1000.);
			nouveaux_coeffs_first_use[j] *= expf((-10 + (rand() % 21))/1000.);
		}
        float nouveau_cout = calcule_cout(nouveaux_coeffs, nouveaux_coeffs_first_use, results, difficulties, results_size);
        if(nouveau_cout<cout || (((rand() % 1000000)/1000000.) < expf((cout-nouveau_cout)/T))){
            cout = nouveau_cout ;
            for(int i = 0; i<13; i++){
                coeffs[i] = nouveaux_coeffs[i];
                coeffs_first_use[i] = nouveaux_coeffs_first_use[i];
            }
            if(best_cout>cout){
                for(int i = 0; i<13; i++){
                    best_coeffs[i] = coeffs[i] ;
                    best_coeffs_first_use[i] = coeffs_first_use[i] ;
                }
                best_cout = cout ;
            }

        }
        else{
            free(nouveaux_coeffs);
            free(nouveaux_coeffs_first_use);
        }
        T = T*0.9999 ;

		if(i%10000 == 0){
			printf("i = %d : \n", i);
			print_tab_float(coeffs, 13);
			print_tab_float(coeffs_first_use, 13);
			printf("Cout = %f\n", cout);
			float ec = sqrt(cout);
			printf("ecart-type = %f\n", ec);
            printf("T = %f\n", T);
			
		}
		i++;
	}
    print_tab_float(best_coeffs, 13);
    print_tab_float(best_coeffs_first_use, 13);
    printf("Cout = %f\n", best_cout);
    float ec = sqrt(best_cout);
    printf("ecart-type = %f\n", ec);
    printf("T = %f\n", T);

    for(int i = 0; i<13; i++){
        coeffs[i] = best_coeffs[i] ;
        coeffs_first_use[i] = best_coeffs_first_use[i] ;
    }
    

}




// void calcule_coeffsv1(float* coeffs, float* coeffs_first_use, float** results, float* difficulties, int results_size){
//     /* Calcule les valeurs des tableaux coeffs et coeffs_first_use minimisant l'écart au difficultés, */
//     /* selon les moindres carrés */
//     /* Ce calcul se fera à l'aide d'une recherche linéaire */
    
//     float cout = calcule_cout(coeffs, coeffs_first_use, results, difficulties, results_size);
// 	float ancien_cout = cout + 42;
// 	int i = 0;
// 	while (ancien_cout > cout) {
// 		ancien_cout = cout ;
// 		for (int j = 0; j <13; j++) {
// 			//for (int k = 0; k < 100; k++) {
// 				coeffs[j] *= 0.99;
// 				float nouveau_cout = calcule_cout(coeffs, coeffs_first_use, results, difficulties, results_size);
// 				if (nouveau_cout >= cout) {
// 					coeffs[j] /= 0.99;
// 				} else {
// 					cout = nouveau_cout;
// 				}
// 				coeffs[j] *= 1.01;
// 				nouveau_cout = calcule_cout(coeffs, coeffs_first_use, results, difficulties, results_size);
// 				if (nouveau_cout >= cout) {
// 					coeffs[j] /= 1.01;
// 				} else {
// 					cout = nouveau_cout;
// 				}
// 				coeffs_first_use[j] *= 0.99;
// 				nouveau_cout = calcule_cout(coeffs, coeffs_first_use, results, difficulties, results_size);
// 				if (nouveau_cout >= cout) {
// 					coeffs_first_use[j] /= 0.99;
// 				} else {
// 					cout = nouveau_cout;
// 				}
// 				coeffs_first_use[j] *= 1.01;
// 				nouveau_cout = calcule_cout(coeffs, coeffs_first_use, results, difficulties, results_size);
// 				if (nouveau_cout >= cout) {
// 					coeffs_first_use[j] /= 1.01;
// 				} else {
// 					cout = nouveau_cout;
// 				}
// 			//}
// 		}
// 		if(i%10 == 0){
// 			printf("i = %d : \n", i);
// 			print_tab_float(coeffs, 13);
// 			print_tab_float(coeffs_first_use, 13);
// 			printf("Cout = %f\n", cout);
// 			float ec	= sqrt(cout);
// 			printf("ecart-type = %f\n", ec);
// 			fflush(stdout);
// 		}
// 		i++;
// 	}

// }