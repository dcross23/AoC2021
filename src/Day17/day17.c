#include "day17.h"

int day17_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[50];
	int areaBottom;

	fgets(line, sizeof(line), f);

	strtok(line, ",");
	strtok(strtok(NULL,","),"=");
	areaBottom = atoi(strtok(strtok(NULL,"="),"."));

	return ((-areaBottom) * ((-areaBottom)-1)/2);
}


bool isInRange(int value, int min, int max){
	return (value >= min && value <=max);
}

int day17_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[50];
	int xmin, xmax, ymin, ymax;
	char *pos, *xline, *yline;

	fgets(line, sizeof(line), f);

	strtok(line, ":");
	pos = line + strlen("target area: ");
	xline = strtok(pos, ",");
	yline = strtok(NULL, ",");
	strtok(xline, "=");
	xline = strtok(NULL, "=");
	strtok(yline, "=");
	yline = strtok(NULL, "=");
	xmin = atoi(strtok(xline,"."));
	xmax = atoi(strtok(NULL,"."));
	ymin = atoi(strtok(yline,"."));
	ymax = atoi(strtok(NULL,"."));


	int offset = xmin+1;
	int pyr =2*(-ymin)+offset, pyc = 2*(-ymin)+offset;
	int posibleYs[pyr][pyc];

	int pxr = (-ymin)+offset, pxc = pyr;
	int posibleXs[pxr][pxc];

	int posibleValues[pxc-1][pyr];
	memset(posibleValues, 0, pxc * pyr * sizeof(int));
	int total = 0;

	//Get suitable y positions
	for(int i=(pyr/2)-1, k=0; i>=-(pyr/2); i--, k++){
		int sum = i;
		posibleYs[k][0] = isInRange(sum, ymin, ymax);
		for(int j=1, cont=i-1; j<pyc; j++, cont--){
			sum += cont;
			posibleYs[k][j] = isInRange(sum, ymin, ymax);
		}
	}

	//Get suitable x positions
	for(int i=0; i<pxr; i++){
		int sum = i;
		posibleXs[i][0] = isInRange(sum, xmin, xmax);

		for(int j=1, cont=i-1; j<pxc; j++, cont--){
			if(cont < 0) cont = 0;
			sum += cont;
			posibleXs[i][j] = isInRange(sum, xmin, xmax);
		}
	}

	//Multiply both arrays to get suitable x,y velocities
	for(int i=0; i<pyr; i++){
		for(int k=0; k<pxr; k++){
			for(int j=0; j<pyc; j++){
				posibleValues[i][k] += posibleYs[i][j] * posibleXs[k][j];
			}
		}
	}

	//Count the amount of sutable x,y initial velocities
	for(int i=0; i<pxc-1; i++){
		for(int j=0; j<pxr; j++){
			if(posibleValues[i][j]) total++;
		}
	}

	return total;
}





