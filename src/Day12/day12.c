#include "day12.h"
#include "graph.h"

int day12_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	Graph *g = createGraph();
	char *name1, *name2;

	while(fgets(line, sizeof(line), f)){
		name1 = strtok(line, "-");
		name2 = strtok(NULL, "-");
		if(name2[strlen(name2)-1] == '\n')
			name2[strlen(name2)-1] = '\0';

		addLineNodes(name1, g, name2);
	}

	int numPaths = findNumPaths(g);
	return numPaths;
}



int day12_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	Graph *g = createGraph();
	char *name1, *name2;

	while(fgets(line, sizeof(line), f)){
		name1 = strtok(line, "-");
		name2 = strtok(NULL, "-");
		if(name2[strlen(name2)-1] == '\n')
			name2[strlen(name2)-1] = '\0';

		addLineNodes(name1, g, name2);
	}
	
	int numPaths = findNumPaths2(g);
	return numPaths;
}