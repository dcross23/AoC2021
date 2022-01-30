#include "day22.h"

#define STRIP(s) if(s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';

#define LIMIT_MIN(x) if(x < -50) x=-50;
#define LIMIT_MAX(x) if(x >  50) x=50; 

void parse(char *coordinate, int *min, int *max){
	char *values;
	strtok(coordinate, "=");
	values = strtok(NULL, "=");
	*min = atoi(strtok(values, "."));
	*max = atoi(strtok(NULL, "."));
}

int day22_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[100];
	char *coordinates;
	bool grid[101][101][101];
	bool onoff;
	int xmin, xmax, ymin, ymax, zmin, zmax;

	memset(grid, false, sizeof(grid));
	
	while(fgets(line, sizeof(line), f)){
		STRIP(line)
		if(strcmp(strtok(line, " "), "on") == 0)  onoff = true;
		else									  onoff = false;

		coordinates = strtok(NULL, " ");
		char *xcoord = strtok(coordinates, ",");
		char *ycoord = strtok(NULL, ",");
		char *zcoord = strtok(NULL, ",");
		parse(xcoord, &xmin, &xmax);
		LIMIT_MIN(xmin)
		LIMIT_MAX(xmax)
		parse(ycoord, &ymin, &ymax);
		LIMIT_MIN(ymin)
		LIMIT_MAX(ymax)
		parse(zcoord, &zmin, &zmax);
		LIMIT_MIN(zmin)
		LIMIT_MAX(zmax)

		for(int x=xmin; x<=xmax; x++){
			for(int y=ymin; y<=ymax; y++){
				for(int z=zmin; z<=zmax; z++){
					grid[x+50][y+50][z+50] = onoff;
				}
			}
		}
	}

	int cubesOn = 0;
	for(int x=0; x<101; x++){
		for(int y=0; y<101; y++){
			for(int z=0; z<101; z++){
				if(grid[x][y][z]) cubesOn++;
			}
		}
	}

	return cubesOn;
}





typedef struct cube{
	bool onoff;
	int xmin, xmax;
	int ymin, ymax;
	int zmin, zmax;
	struct cube *childs;
	int numChilds;
}Cube;

bool overlap(Cube *c1, Cube *c2){
	if(c2->xmin > c1->xmax || c1->xmin > c2->xmax) return false;
	if(c2->ymin > c1->ymax || c1->ymin > c2->ymax) return false;
	if(c2->zmin > c1->zmax || c1->zmin > c2->zmax) return false;
	return true;
}

Cube *getIntersection(Cube *c1, Cube *c2){
	Cube *c = malloc(sizeof(Cube));
	if(c1->xmin > c2->xmin) c->xmin = c1->xmin;
	else c->xmin = c2->xmin;

	if(c1->xmax < c2->xmax) c->xmax = c1->xmax;
	else c->xmax = c2->xmax;

	if(c1->ymin > c2->ymin) c->ymin = c1->ymin;
	else c->ymin = c2->ymin;

	if(c1->ymax < c2->ymax) c->ymax = c1->ymax;
	else c->ymax = c2->ymax;

	if(c1->zmin > c2->zmin) c->zmin = c1->zmin;
	else c->zmin = c2->zmin;

	if(c1->zmax < c2->zmax) c->zmax = c1->zmax;
	else c->zmax = c2->zmax;

	c->onoff = !c1->onoff;
	c->childs = NULL;
	c->numChilds = 0;
	return c;	
}

void intersect(Cube *c1, Cube *c2){
	if(overlap(c1,c2)){
		Cube *intersection = getIntersection(c1,c2);
		for(int i=0; i<c1->numChilds; i++){
			intersect(&c1->childs[i], c2);
		}

		if(c1->childs == NULL) c1->childs = malloc((c1->numChilds+1) * sizeof(Cube));
		else c1->childs = realloc(c1->childs, (c1->numChilds+1) * sizeof(Cube));
		c1->childs[c1->numChilds++] = *intersection;
	}
}

long long int calculateArea(Cube *c){
	long long int area = 1;
	area *= (c->xmax - c->xmin + 1);
	area *= (c->ymax - c->ymin + 1);
	area *= (c->zmax - c->zmin + 1);
	for(int i=0; i<c->numChilds; i++){
		area -= calculateArea(&c->childs[i]);
	}
	return area;
}

long long int day22_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[100];
	char *coordinates;
	bool grid[101][101][101];
	bool onoff;
	int xmin, xmax, ymin, ymax, zmin, zmax;

	memset(grid, false, sizeof(grid));
	
	Cube *listCubes = NULL;
	int numCubes = 0;

	while(fgets(line, sizeof(line), f)){
		STRIP(line)
		if(strcmp(strtok(line, " "), "on") == 0)  onoff = true;
		else									  onoff = false;

		coordinates = strtok(NULL, " ");
		char *xcoord = strtok(coordinates, ",");
		char *ycoord = strtok(NULL, ",");
		char *zcoord = strtok(NULL, ",");
		parse(xcoord, &xmin, &xmax);
		parse(ycoord, &ymin, &ymax);
		parse(zcoord, &zmin, &zmax);

		Cube newCube = {onoff, xmin, xmax, ymin, ymax, zmin, zmax, NULL, 0};
		Cube *newList = NULL;
		int newNumCubes = 0;

		for(int i=0; i<numCubes; i++){
			intersect(&listCubes[i], &newCube);
			if(newList == NULL) newList = malloc((newNumCubes+1) * sizeof(Cube));
			else newList = realloc(newList, (newNumCubes+1) * sizeof(Cube));

			newList[newNumCubes++] = listCubes[i];
		}

		if(newCube.onoff){
			if(newList == NULL) newList = malloc((newNumCubes+1) * sizeof(Cube));
			else newList = realloc(newList, (newNumCubes+1) * sizeof(Cube));
			newList[newNumCubes++] = newCube;
		}

		listCubes = newList;
		numCubes = newNumCubes;
	}

	long long int result = 0;
	for(int i=0; i<numCubes; i++){
		result += calculateArea(&listCubes[i]);
	}

	return result;
}



