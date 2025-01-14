#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int** grid_of_string(char* s){
	int** grid = malloc(9*sizeof(int*));
	assert(grid!=NULL);
	for(int i =0; i<9; i++){
		grid[i] = malloc(9*sizeof(grid));
		assert(grid!=NULL);
		for(int j = 0; j<9; j++){
			grid[i][j] = s[9*i + j] - '0';
		}
	}
	return grid ;
}