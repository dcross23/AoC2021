#include "day7.h"

int day7_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[5000];
	char *next;
	int numbers[5000], numbersSize = 0;
	int nextNum;
	int largestNumber = 0;
	int leastFuel = INT_MAX;
	int fuel;

	memset(numbers, 0, 5000 * sizeof(int));

	fgets(line, sizeof(line), f);

	next = strtok(line, ",");
	numbers[0] = atoi(next);
	numbersSize++;
	
	nextNum = 1;
	while(NULL != (next = strtok(NULL, ","))){
		numbers[nextNum++] = atoi(next);
		numbersSize++;
	}

	
	for(int i=0; i<numbersSize; i++)
		if(largestNumber < numbers[i]) 
			largestNumber = numbers[i];

	for(int i=0; i<largestNumber; i++){
		fuel = 0;
		for(int j=0; j<numbersSize; j++){
			fuel += abs(i - numbers[j]);
		}

		if(fuel < leastFuel)
			leastFuel = fuel;
	}

	return leastFuel;
}

int day7_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[5000];
	char *next;
	int numbers[5000], numbersSize = 0;
	int nextNum;
	int largestNumber = 0;
	int val;
	int leastFuel = INT_MAX;
	int fuel, steps;

	memset(numbers, 0, 5000 * sizeof(int));

	fgets(line, sizeof(line), f);

	next = strtok(line, ",");
	numbers[0] = atoi(next);
	numbersSize++;
	
	nextNum = 1;
	while(NULL != (next = strtok(NULL, ","))){
		numbers[nextNum++] = atoi(next);
		numbersSize++;
	}

		
	for(int i=0; i<numbersSize; i++)
		if(largestNumber < numbers[i]) 
			largestNumber = numbers[i];

	int permutations[largestNumber+1];
	for(int i=0; i<=largestNumber; i++){
		val = 0;
		for(int j=0; j<=i; j++)
			val += j;

		permutations[i] = val;
	}

	for(int i=0; i<largestNumber; i++){
		fuel = 0;
		for(int j=0; j<numbersSize; j++){
			steps = abs(i - numbers[j]);
			fuel += permutations[steps];
		}

		if(fuel < leastFuel)
			leastFuel = fuel;

	}
	
	return leastFuel;
}
