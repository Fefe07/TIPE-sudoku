#include <stdlib.h>
#include <stdbool.h>

void free_notes(bool*** notes){
	for(int i = 0; i<9; i++){
		for(int j = 0; j<9; j++){
			free(notes[i][j]);
		}
		free(notes[i]);
	}
	free(notes);
}