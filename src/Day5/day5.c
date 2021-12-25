#include "day5.h"

#define ROWS 1000
#define COLS 1000

typedef struct line{
	int x0, y0;
	int x1, y1;
} Line;

void DrawHorLine(int (*board)[COLS], int x0, int x1, int y){
	for(int x=x0; x<=x1; x++)
		board[y][x]++;
}

void DrawVerLine(int (*board)[COLS], int y0, int y1, int x){
	for(int y=y0; y<=y1; y++)
		board[y][x]++;
}

int day5_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	int numLines = 0, aux, numOverlaped;
	int board[ROWS][COLS];
	char *point1, *point2;
	Line *lines;	

	int i=0;
	char c;
	//Calculate the number of bingos
	for (c = getc(f); c != EOF; c = getc(f))
        	if (c == '\n') numLines++;
	
	
	memset(board, 0, ROWS*COLS*sizeof(board[0][0]));
	lines = malloc(numLines * sizeof(Line));

	//Read file and parse it
	fseek(f, 0, SEEK_SET);
	
	i=0;
	while(fgets(line, sizeof(line), f)){
		point1 = strtok(line, " -> ");	
		point2 = strtok(NULL, " -> ");
		
		lines[i].x0 = atoi(strtok(point1, ","));
		lines[i].y0 = atoi(strtok(NULL, ","));
		lines[i].x1 = atoi(strtok(point2, ","));
		lines[i].y1 = atoi(strtok(NULL, ","));
	
		i++;
	}

	for(int i=0; i<numLines; i++){
		//Horizontal line
		if(lines[i].y0 == lines[i].y1){
			if(lines[i].x0 > lines[i].x1) DrawHorLine(board, lines[i].x1, lines[i].x0, lines[i].y0);
			else DrawHorLine(board, lines[i].x0, lines[i].x1, lines[i].y0);
		}
		//Vertical line
		else if(lines[i].x0 == lines[i].x1){
			if(lines[i].y0 > lines[i].y1) DrawVerLine(board, lines[i].y1, lines[i].y0, lines[i].x0);
			else DrawVerLine(board, lines[i].y0, lines[i].y1, lines[i].x0);
			
     		}
	}

	numOverlaped = 0;
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			if(board[i][j] > 1)
				numOverlaped++;
		}
	}

	return numOverlaped;
}




int day5_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	int numLines = 0, aux, numOverlaped;
	int board[ROWS][COLS];
	char *point1, *point2;
	Line *lines;	

	int i=0;
	char c;
	//Calculate the number of bingos
	for (c = getc(f); c != EOF; c = getc(f))
        	if (c == '\n') numLines++;
	
	
	memset(board, 0, ROWS*COLS*sizeof(board[0][0]));
	lines = malloc(numLines * sizeof(Line));

	//Read file and parse it
	fseek(f, 0, SEEK_SET);
	
	i=0;
	while(fgets(line, sizeof(line), f)){
		point1 = strtok(line, " -> ");	
		point2 = strtok(NULL, " -> ");
		
		lines[i].x0 = atoi(strtok(point1, ","));
		lines[i].y0 = atoi(strtok(NULL, ","));
		lines[i].x1 = atoi(strtok(point2, ","));
		lines[i].y1 = atoi(strtok(NULL, ","));
	
		i++;
	}

	for(int i=0; i<numLines; i++){
		//Horizontal line
		if(lines[i].y0 == lines[i].y1){
			if(lines[i].x0 > lines[i].x1) DrawHorLine(board, lines[i].x1, lines[i].x0, lines[i].y0);
			else DrawHorLine(board, lines[i].x0, lines[i].x1, lines[i].y0);
		}
		//Vertical line
		else if(lines[i].x0 == lines[i].x1){
			if(lines[i].y0 > lines[i].y1) DrawVerLine(board, lines[i].y1, lines[i].y0, lines[i].x0);
			else DrawVerLine(board, lines[i].y0, lines[i].y1, lines[i].x0);
			
     		}
		//45 degrees diagonal line
		else if(abs(lines[i].x0-lines[i].x1) == abs(lines[i].y0-lines[i].y1)){
			if(lines[i].x0 > lines[i].x1){
				if(lines[i].y0 > lines[i].y1){
					for(int x=lines[i].x0, y=lines[i].y0; x>=lines[i].x1 && y>=lines[i].y1; x--, y--){
						board[y][x]++;
					}

				}else{
					for(int x=lines[i].x0, y=lines[i].y0; x>=lines[i].x1 && y<=lines[i].y1; x--, y++){
						board[y][x]++;
					}
				}

			}else{
				if(lines[i].y0 > lines[i].y1){
					for(int x=lines[i].x0, y=lines[i].y0; x<=lines[i].x1 && y>=lines[i].y1; x++, y--){
						board[y][x]++;
					}

				}else{
					for(int x=lines[i].x0, y=lines[i].y0; x<=lines[i].x1 && y<=lines[i].y1; x++, y++){
						board[y][x]++;
					}
				}
			
			}
		}

	}

	numOverlaped = 0;
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			if(board[i][j] > 1)
				numOverlaped++;
		}
	}

	return numOverlaped;
}



