#include <stdlib.h>


void free_grid(int** grid){
	for(int i = 0; i<9; i++){
		free(grid[i]);
	}
	free(grid);
}