#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


float calcule_cout(float* coeffs, float* coeffs_used, float** results, float* difficulties, int results_size){
	float cout = 0 ;
	for(int i = 0; i<results_size; i++){
		float diff_i = 0 ;
		for(int j = 0; j<13; j++){
			diff_i += results[i][j] * coeffs[j] ;
			if (results[i][j] > 0.01){
				diff_i += coeffs_used[j] - coeffs[j];
			}
		}
		cout += (diff_i-difficulties[i]) * (diff_i-difficulties[i]) ;
	}
	cout /= results_size ;
	return cout ;
}