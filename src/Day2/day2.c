#include "day2.h"

int day2_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[15];
	int horPos = 0, depth = 0;	
	char *command;
	int ammount;

	while(fgets(line, sizeof(line), f)){
		command = strtok(line, " ");
		ammount = atoi(strtok(NULL, " "));
		
		if(strcmp(command, "forward") == 0){
			horPos += ammount;	
		}
		else if(strcmp(command, "down") == 0){
			depth += ammount;
		}
		else if(strcmp(command, "up") == 0){
			depth -= ammount;
		}
	}
	
	return horPos * depth;
}

int day2_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[15];
	int horPos = 0, depth = 0, aim = 0;	
	char *command;
	int ammount;

	while(fgets(line, sizeof(line), f)){
		command = strtok(line, " ");
		ammount = atoi(strtok(NULL, " "));
		
		if(strcmp(command, "forward") == 0){
			horPos += ammount;
			depth += (aim * ammount);
		}
		else if(strcmp(command, "down") == 0){
			aim += ammount;
		}
		else if(strcmp(command, "up") == 0){
			aim -= ammount;
		}
	}
	
	return horPos * depth;

}

