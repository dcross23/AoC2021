#include "day13.h"

#define ROWS 2000
#define COLS 2000

int day13_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[50];
	int c,r;
	char *fold; 
	int foldLine;

	bool table[ROWS][COLS];
	int rows = 0, cols = 0;

	memset(table, false, ROWS*COLS*sizeof(bool));

	while(fgets(line, sizeof(line), f)){
		if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
		if(line[0] == '\0') continue;
		
		if(line[0] != 'f'){
			c = atoi(strtok(line, ","));	
			r = atoi(strtok(NULL, ","));

			table[r][c] = true;
			if(r+1 > rows) rows = r+1;
			if(c+1 > cols) cols = c+1;
		
		}else {
			fold = line + strlen("fold along ");
			break;
		}	
	}


	if(strcmp(strtok(fold,"="), "y") == 0){
		//Fold horizontally, middle down to top
		int invr;
		foldLine = atoi(strtok(NULL,"="));

		for(int i=foldLine+1; i<rows; i++){
			for(int j=0; j<cols; j++){
				if(table[i][j]){
					invr = foldLine - (i - foldLine);
					table[invr][j] = true;
					table[i][j] = false;
				}
			}
		}

		rows = foldLine;

	}else{
		//Fold vertically, middle right to left
		int invc;
		foldLine = atoi(strtok(NULL,"="));

		for(int i=0; i<rows; i++){
			for(int j=foldLine+1; j<cols; j++){
				if(table[i][j]){
					invc = foldLine - (j - foldLine);
					table[i][invc] = true;
					table[i][j] = false;
				}
			}
		}

		cols = foldLine;
	}


	int numDots = 0;
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			if(table[i][j]) numDots++;
		}
	}

	return numDots;
}


bool isEmptyRow(int row, bool (*table)[COLS], int cols){
	for(int i=0; i<cols; i++){
		if(table[row][i]) return false;
	}
	return true;
}

int day13_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[50];
	int c,r;
	char folds[20][10];
	char *fold;
	int numFolds = 0, foldLine;

	bool table[ROWS][COLS];
	int rows = 0, cols = 0;

	memset(table, false, ROWS*COLS*sizeof(bool));
	memset(folds, '\0', 80*sizeof(char));

	while(fgets(line, sizeof(line), f)){
		if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
		if(line[0] == '\0') continue;
		
		if(line[0] != 'f'){
			c = atoi(strtok(line, ","));	
			r = atoi(strtok(NULL, ","));

			table[r][c] = true;
			if(r+1 > rows) rows = r+1;
			if(c+1 > cols) cols = c+1;
		
		}else {
			strcpy(folds[numFolds++], line + strlen("fold along "));
		}	
	}

	for(int f=0; f<numFolds; f++){
		if(strcmp(strtok(folds[f],"="), "y") == 0){
			//Fold horizontally, middle down to top
			int invr;
			foldLine = atoi(strtok(NULL,"="));

			for(int i=foldLine+1; i<rows; i++){
				for(int j=0; j<cols; j++){
					if(table[i][j]){
						invr = foldLine - (i - foldLine);
						table[invr][j] = true;
						table[i][j] = false;
					}
				}
			}

			rows = foldLine;

		}else{
			//Fold vertically, middle right to left
			int invc;
			foldLine = atoi(strtok(NULL,"="));

			for(int i=0; i<rows; i++){
				for(int j=foldLine+1; j<cols; j++){
					if(table[i][j]){
						invc = foldLine - (j - foldLine);
						table[i][invc] = true;
						table[i][j] = false;
					}
				}
			}

			cols = foldLine;
		}
	}

	bool empty;
	for(int i=0; i<rows; i++){
		empty = isEmptyRow(i, table, cols);
		for(int j=0; j<cols; j++){
			if(!empty){
				if(table[i][j]) 
					printf("#");
				else 
					printf(" ");	
			}
		}
		if(!empty) printf("\n");
	}
}



