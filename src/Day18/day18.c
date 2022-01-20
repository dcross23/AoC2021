#include "day18.h"

#define STRIP(s) if(s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';

int day18_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[70];
	BinaryTree t1 = NULL, t2 = NULL;
	
	fgets(line, sizeof(line), f);
	STRIP(line)
	t1 = createBTree(line);

	while(fgets(line, sizeof(line), f)){
		STRIP(line)
		t2 = createBTree(line);
		t1 = addTrees(t1, t2);
		reduceTree(t1);
	}

	return treeMagnitude(t1);
}


int day18_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[70];
	BinaryTree sumTree = NULL;
	char lines[100][70];
	int lastLine = 0;
	int maxMagnitude = INT_MIN, mag;
	
	while(fgets(line, sizeof(line), f)){
		STRIP(line)
		strcpy(lines[lastLine++], line);
	}

	for(int i=0; i<lastLine; i++){
		for(int j=0; j<lastLine; j++){
			if(i != j){
				sumTree = addTrees(createBTree(lines[i]), createBTree(lines[j]));
				reduceTree(sumTree);
				mag = treeMagnitude(sumTree);
				if(mag > maxMagnitude)
					maxMagnitude = mag;				
			}
		}
	}

	return maxMagnitude;
}



