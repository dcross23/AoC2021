#include "day9.h"
#include "list.h"

#define ROWS 100
#define COLS 100

int day9_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

	char line[110];
	int smokes[ROWS][COLS];
	int rows = 0, cols, k;

	while(fgets(line, sizeof(line), f)){
		k=0;
	        cols = 0;	
		while(line[k] != '\n' && line[k] != '\0'){
			smokes[rows][cols++] = line[k++] - '0';	
		}	
		rows++;
	}

	int count = 0;
	bool isSmaller = false;
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			isSmaller = true;	
			if(j-1>=0 && smokes[i][j] >= smokes[i][j-1])
				isSmaller = false;
			
			if(isSmaller && i-1>=0 && smokes[i][j] >= smokes[i-1][j])
				isSmaller = false;
			
			if(isSmaller && j+1<cols && smokes[i][j] >= smokes[i][j+1])
				isSmaller = false;

			if(isSmaller && i+1<rows && smokes[i][j] >= smokes[i+1][j])
				isSmaller = false;

			if(isSmaller){
				count += (smokes[i][j] + 1);
			}	
		}
	}
	
	return count;
}

void sortBasins(int *basins, int n){
	int a;
	for (int i = 0; i < n; i++){
     		for (int j = i + 1; j < n; j++){
         		if (basins[i] < basins[j]){
         			a = basins[i];
            			basins[i] = basins[j];
            			basins[j] = a;
         		}
      		}
   	}
}

int day9_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

	char line[110];
	int smokes[ROWS][COLS];
	int rows = 0, cols, k;

	while(fgets(line, sizeof(line), f)){
		k=0;
	        cols = 0;	
		while(line[k] != '\n' && line[k] != '\0'){
			smokes[rows][cols++] = line[k++] - '0';	
		}	
		rows++;
	}

	int count = 0;
	Point *smallestPoints = NULL;
       	int numPoints = 0;
	bool isSmaller = false;
	
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			isSmaller = true;	
			if(j-1>=0 && smokes[i][j] >= smokes[i][j-1])
				isSmaller = false;
			
			if(isSmaller && i-1>=0 && smokes[i][j] >= smokes[i-1][j])
				isSmaller = false;
			
			if(isSmaller && j+1<cols && smokes[i][j] >= smokes[i][j+1])
				isSmaller = false;

			if(isSmaller && i+1<rows && smokes[i][j] >= smokes[i+1][j])
				isSmaller = false;

			if(isSmaller){
				if(smallestPoints == NULL)
					smallestPoints = malloc((numPoints+1) * sizeof(Point));
				else
					smallestPoints = realloc(smallestPoints, (numPoints+1) * sizeof(Point));
				
				smallestPoints[numPoints].x = i;
				smallestPoints[numPoints++].y = j;
			}	
		}
	}


	PNode *toVisit = NULL;
	PNode *visited = NULL;
	Point p;
	int basins[numPoints];
	
	for(int i=0; i<numPoints; i++){
		clearPList(&toVisit);
		clearPList(&visited);
		addPNode(createPNode(smallestPoints[i]), &toVisit);
		count = 1;

		while(!isPListEmpty(toVisit)){
			p = getFromPList(&toVisit);
			addPNode(createPNode(p), &visited);

			if(p.y-1 >= 0 && smokes[p.x][p.y-1]!=9 && !isInPList((Point) {p.x, p.y-1}, visited) && !isInPList((Point) {p.x, p.y-1}, toVisit)) 
				addPNode(createPNode((Point) {p.x, p.y-1}), &toVisit);
			
			if(p.x-1 >= 0 && smokes[p.x-1][p.y]!=9 && !isInPList((Point) {p.x-1, p.y}, visited) && !isInPList((Point) {p.x-1, p.y}, toVisit))
				addPNode(createPNode((Point) {p.x-1, p.y}), &toVisit);
			
			if(p.y+1 < cols && smokes[p.x][p.y+1]!=9 && !isInPList((Point) {p.x, p.y+1}, visited) && !isInPList((Point) {p.x, p.y+1}, toVisit))
				addPNode(createPNode((Point) {p.x, p.y+1}), &toVisit);
			
			if(p.x+1 < rows && smokes[p.x+1][p.y]!=9 && !isInPList((Point) {p.x+1, p.y}, visited) && !isInPList((Point) {p.x+1, p.y}, toVisit))
				addPNode(createPNode((Point) {p.x+1, p.y}), &toVisit);
		}
	
		count = getPListSize(visited);
		basins[i] = count;
	}

	sortBasins(basins, numPoints);

	count = 1;
	for(int i=0; i<3; i++)
		count *= basins[i];	
	
	return count;
}
