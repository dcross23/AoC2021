#include "day15.h"

#define STRIP(s) if(s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';
#define ROWS 500
#define COLS 500

bool isPointVisited(Point p, Point *list, int sz){
	for(int i=0; i<sz; i++){
		if(p.r == list[i].r && p.c == list[i].c) return true;
	}
	return false;
}

//Based on Dijkstra`s algorithm
int pathFind(int (*table)[COLS], int rows, int cols){
	Heap queue;
	Point visited[rows*cols];
	int costs[rows][cols];
	int visited_sz = 0;
	heapElement he, neighbor;
	Point p;
	Point neighbors[4] = {{-1,0},{1,0},{0,-1},{0,1}};

	memset(costs, 0, sizeof(costs));

	initHeap(&queue);
	he.info = (Point) {0,0};
	he.key = 0;
	add(he, &queue);

	while(queue.size > 0){
		removeTop(&queue, &he);

		if(isPointVisited(he.info, visited, visited_sz)) 
			continue;

		visited[visited_sz++] = he.info;
		costs[he.info.r][he.info.c] = he.key;

		//Is the end point
		if(he.info.r == rows-1 && he.info.c == cols-1)
			break;

		//Add neighbors
		for(int i=0; i<4; i++){
			p.r = he.info.r + neighbors[i].r;
			p.c = he.info.c + neighbors[i].c; 
			if(p.r<0 || p.r>=rows || p.c<0 || p.c>=cols)
				continue;

			neighbor.info = p;
			neighbor.key = he.key + table[p.r][p.c];
			add(neighbor, &queue);
		}

	}
	
	return costs[rows-1][cols-1];
}

int day15_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[COLS];	
	int table[ROWS][COLS];
	int rows = 0, cols = 0;
	
	while(fgets(line, sizeof(line), f)){
		STRIP(line)

		cols = 0;
		for(int i=0; i<strlen(line); i++){
			table[rows][cols++] = line[i] - '0';
		}
		rows++;
	}

	return pathFind(table, rows, cols);
}


void expandTable(int (*table)[COLS], int *rows, int *cols){
	//Expand first row
	int nr,nc; 
	for(int i=1; i<5; i++){
		for(int r=0; r<(*rows); r++){
			for(int c=0; c<(*cols); c++){
				nc=c+i*(*cols);
				table[r][nc] = ((table[r][c] + (i-1)) % 9)+1;
			}
		}
	}
	(*cols) *= 5;
	//Expand columns from first row
	for(int i=1; i<5; i++){
		for(int r=0; r<(*rows); r++){
			nr = r + i*(*rows);
			for(int c=0; c<(*cols); c++){
				table[nr][c] = ((table[r][c] + (i-1)) % 9)+1;
			}
		}
	}
	(*rows) *= 5;
}

int day15_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[COLS];	
	int table[ROWS][COLS];
	int rows = 0, cols = 0;
	while(fgets(line, sizeof(line), f)){
		STRIP(line)

		cols = 0;
		for(int i=0; i<strlen(line); i++){
			table[rows][cols++] = line[i] - '0';
		}
		rows++;
	}
	expandTable(table, &rows, &cols);	
	return pathFind(table, rows, cols);
}