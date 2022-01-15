#include "day14.h"

#define TABLE_SZ 'Z'-'A' + 1
#define TABLE_POS(l) (l - 'A')

typedef struct insertion{
	char p1, p2, ins;
}Insertion;

long long int day14(char *file, int numRounds){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[50], polymer[50];
	long long int polymerTable[TABLE_SZ][TABLE_SZ];
	long long int newPolymer[TABLE_SZ][TABLE_SZ];
	int r,c; 
	char *pair, insertion; 


	memset(polymerTable, 0, sizeof(polymerTable));

	fgets(polymer, sizeof(polymer), f);
	polymer[strlen(polymer)-1] = '\0';
	//Get polymer initial pairs
	for(int i=1, j=0; i<strlen(polymer); i++, j++){
		r = TABLE_POS(polymer[i]);
		c = TABLE_POS(polymer[j]);
		polymerTable[r][c]++;
	}
	
	fgets(line, sizeof(line), f); //Remove blank line
	
	Insertion newInsertion;
	Insertion *insertions = NULL;
	int insertions_sz = 0;
	
	while(fgets(line, sizeof(line), f)){
		if(line[strlen(line)-1] == '\n')
			line[strlen(line)-1] = '\0';

		pair = strtok(line, " -> ");
		insertion = strtok(NULL," ->")[0];

		newInsertion.p1 = pair[1];
		newInsertion.p2 = pair[0];
		newInsertion.ins = insertion;

		if(insertions == NULL)
			insertions = malloc((insertions_sz+1) * sizeof(Insertion));
		else
			insertions = realloc(insertions, (insertions_sz+1) * sizeof(Insertion));

		insertions[insertions_sz++] = newInsertion;
	}

	for(int rounds=0; rounds<numRounds; rounds++){
		memset(newPolymer, 0, sizeof(newPolymer));

		for(int i=0; i<insertions_sz; i++){
			long long int n = polymerTable[TABLE_POS(insertions[i].p1)][TABLE_POS(insertions[i].p2)];
			if(n > 0){
				newPolymer[TABLE_POS(insertions[i].p1)][TABLE_POS(insertions[i].ins)] += n;
				newPolymer[TABLE_POS(insertions[i].ins)][TABLE_POS(insertions[i].p2)] += n;	
			}
		}

		for(int i=0; i<TABLE_SZ; i++){
			for(int j=0; j<TABLE_SZ; j++){
				polymerTable[i][j] = newPolymer[i][j];
			}
		}
	}

	long long int leastCommon=LLONG_MAX, mostCommon=LLONG_MIN;
	for(int i=0; i<TABLE_SZ; i++){
		long long int sum = 0;
		for(int j=0; j<TABLE_SZ; j++){
			sum += 	polymerTable[i][j];
		}
		if(sum > 0 && sum < leastCommon) leastCommon = sum;
		if(sum > 0 && sum > mostCommon ) mostCommon  = sum;
	}
	
	free(insertions);
	return mostCommon - leastCommon;
}

long long int day14_p1(char *file){
	return day14(file, 10);
}

long long int day14_p2(char *file){
	return day14(file, 40);
}




