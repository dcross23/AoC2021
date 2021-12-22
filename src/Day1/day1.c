#include "day1.h"

int day1_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[10];	
	int prev = -1, act = -1;
	int numIncreases = 0;

	while(fgets(line, sizeof(line), f)){
		act = atoi(line);
	
		if(prev!=-1 && act > prev)
			numIncreases++;

		prev = act;
	}
	
	return numIncreases;
}

int day1_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[10];	
	int prev1 = -1, prev2 = -1, act = -1;
	int prevSum = -1, actSum = -1;
	int numIncreases = 0;

	while(fgets(line, sizeof(line), f)){
		act = atoi(line);

		if(prev1!=-1 && prev2!=-1){
			actSum = act + prev1 + prev2;
			if(prevSum!=-1 && actSum > prevSum)
				numIncreases++;

			prevSum = actSum;
		}

		prev1 = prev2;
		prev2 = act;
	}
	
	return numIncreases;

}

