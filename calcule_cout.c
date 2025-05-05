#include <assert.h>
#include <stdbool.h>



float calcule_cout(float* coeffs, float* coeffs_first_use, float** results, float* difficulties, int results_size){
	float cout = 0 ;
	for(int i = 0; i<results_size; i++){
		float diff_i = 0 ;
		for(int j = 0; j<13; j++){
			diff_i += results[i][j] * coeffs[j] ;
			if (results[i][j] > 0.001){
				diff_i += coeffs_first_use[j];
			}
		}
		cout += (diff_i-difficulties[i]) * (diff_i-difficulties[i]) ;
	}
	cout = cout /(1. * results_size) ;
	return cout ;
}