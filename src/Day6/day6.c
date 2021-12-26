#include "day6.h"

#define MAP_SIZE 9
#define DAYS_PART1 80
#define DAYS_PART2 256


long long int day6_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[1000];
	char *next;
	int nextNum;
	long long int map[MAP_SIZE];
	long long int newMap[MAP_SIZE];	
	long long int suma = 0;

	memset(map, -1, MAP_SIZE * sizeof(long long int));

	fgets(line, sizeof(line), f);

	nextNum = atoi(strtok(line, ","));	
	if(map[nextNum] == -1)
		map[nextNum] = 0;
	map[nextNum]++;
	
	while(NULL != (next = strtok(NULL, ","))){
		nextNum = atoi(next);
		if(map[nextNum] == -1)
			map[nextNum] = 0;

		map[nextNum]++;
	}


	
	for(int d=0; d<DAYS_PART1; d++){
		memset(newMap, -1, MAP_SIZE * sizeof(long long int));
	
		if(map[0] > -1){
			if(newMap[6] == -1) newMap[6] = 0;
			newMap[6] += map[0];	
		
			if(newMap[8] == -1) newMap[8] = 0;
			newMap[8] += map[0];	
		}

		for(int i=1; i<MAP_SIZE; i++){
			if(map[i] > -1){
				if(newMap[i-1] == -1) newMap[i-1] = 0;
				newMap[i-1] += map[i];		
			}

		}
		
		
		for(int i=0; i<MAP_SIZE; i++)
			map[i] = newMap[i];
	}	

	for(int i=0; i<MAP_SIZE; i++)
		if(map[i] > -1)
			suma += map[i];

	return suma;
}


long long int day6_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[1000];
	char *next;
	int nextNum;
	long long int map[MAP_SIZE];
	long long int newMap[MAP_SIZE];	
	long long int suma = 0;

	memset(map, -1, MAP_SIZE * sizeof(long long int));

	fgets(line, sizeof(line), f);

	nextNum = atoi(strtok(line, ","));	
	if(map[nextNum] == -1)
		map[nextNum] = 0;
	map[nextNum]++;
	
	while(NULL != (next = strtok(NULL, ","))){
		nextNum = atoi(next);
		if(map[nextNum] == -1)
			map[nextNum] = 0;

		map[nextNum]++;
	}


	
	for(int d=0; d<DAYS_PART2; d++){
		memset(newMap, -1, MAP_SIZE * sizeof(long long int));
	
		if(map[0] > -1){
			if(newMap[6] == -1) newMap[6] = 0;
			newMap[6] += map[0];	
		
			if(newMap[8] == -1) newMap[8] = 0;
			newMap[8] += map[0];	
		}

		for(int i=1; i<MAP_SIZE; i++){
			if(map[i] > -1){
				if(newMap[i-1] == -1) newMap[i-1] = 0;
				newMap[i-1] += map[i];		
			}

		}
		
		
		for(int i=0; i<MAP_SIZE; i++)
			map[i] = newMap[i];
	}	

	for(int i=0; i<MAP_SIZE; i++)
		if(map[i] > -1)
			suma += map[i];

	return suma;
}




