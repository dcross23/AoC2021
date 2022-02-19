#include "day25.h"

#define STRIP(s) if(s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';
#define ROWS 200
#define COLS 200

int day25_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[200];
	char grid[ROWS][COLS];
	int rows, cols;

	rows = 0;
	while(fgets(line, sizeof(line), f)){
		STRIP(line)
		cols = 0;
		for(int i=0; i<strlen(line); i++){
			grid[rows][cols++] = line[i];
		}
		rows++;
	}

	int steps = 0;
	char newGrid[rows][cols];
	bool isChange;

	while(true){
		steps++;
		isChange = false;

		for(int i=0; i<rows; i++){
			for(int j=0; j<cols; j++){
				newGrid[i][j] = grid[i][j];
			}
		}


		//East cucumbers
		for(int i=0; i<rows; i++){
			for(int j=0; j<cols; j++){
				if(grid[i][j] == '>'){
					int newRow = i;
					int newCol = (j+1) % cols;

					if(grid[newRow][newCol] == '.'){
						isChange = true;
						newGrid[newRow][newCol] = '>';
						newGrid[i][j] = '.';
					}
				}
			}
		}

		for(int i=0; i<rows; i++){
			for(int j=0; j<cols; j++){
				grid[i][j] = newGrid[i][j];
			}
		}

		//South cucumbers
		for(int i=0; i<rows; i++){
			for(int j=0; j<cols; j++){
				if(grid[i][j] == 'v'){
					int newRow = (i+1) % rows;
					int newCol = j;

					if(grid[newRow][newCol] == '.'){
						isChange = true;
						newGrid[newRow][newCol] = 'v';
						newGrid[i][j] = '.';
					}
				}
			}
		}


		if(!isChange) break;

		for(int i=0; i<rows; i++){
			for(int j=0; j<cols; j++){
				grid[i][j] = newGrid[i][j];
			}
		}
	}
	return steps;
}