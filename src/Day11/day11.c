#include "day11.h"

#define ROWS 10
#define COLS 10

void updateNeighbors(int (*octopuses)[COLS], int i, int j, bool (*flashed)[COLS]){
	for(int x=-1; x<=1; x++){
		for(int y=-1; y<=1; y++){
			if((i+x)>=0 && (i+x)<ROWS && (j+y)>=0 && (j+y)<COLS){
				if(!flashed[i+x][j+y])
					octopuses[i+x][j+y]++;
			}
		}
	}
}

int update(int (*octopuses)[COLS], bool (*flashed)[COLS]){
	//Increment all 
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			octopuses[i][j]++;
		}
	}

	//Check for flashes
	int flashes = 0;
	bool stop = false;

	memset(flashed, false, ROWS*COLS*sizeof(bool));

	while(!stop){
		stop = true;
		for(int i=0; i<ROWS; i++){
			for(int j=0; j<COLS; j++){
				if(octopuses[i][j] > 9){
					octopuses[i][j] = 0;
					flashed[i][j] = true;
					flashes++;

					//Increase neighbors
					updateNeighbors(octopuses, i, j, flashed);
					stop = false;
				}
			}
		}
	}
	return flashes;
}

int day11_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	int octopuses[ROWS][COLS];
	bool flashed[ROWS][COLS];
	int r, flashes;

	r = 0;
	while(fgets(line, sizeof(line), f)){
		for(int i=0; i<COLS; i++){
			octopuses[r][i] = line[i] - '0';	
		}
		r++;
	}

	flashes = 0;
	for(int i=0; i<100; i++){
		flashes += update(octopuses, flashed);
	}
	
	return flashes;
}



bool checkSynchronized(int (*octopuses)[COLS]){
	bool synchronized = true;
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			if(octopuses[i][j] != 0)
				synchronized = false;
		}
	}

	return synchronized;
}

int day11_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	int octopuses[ROWS][COLS];
	bool flashed[ROWS][COLS];
	int r, steps;

	r = 0;
	while(fgets(line, sizeof(line), f)){
		for(int i=0; i<COLS; i++){
			octopuses[r][i] = line[i] - '0';	
		}
		r++;
	}

	steps = 0;
	while(!checkSynchronized(octopuses)){
		update(octopuses, flashed);
		steps++;
	}
	
	return steps;
}



