#include "day24.h"

#define STRIP(s) if(s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';

void parseMONAD(char *file, int *type1, int *type2, int *mod){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return;

 	char line[50];
	
	bool isType1, isType1Det;
	int idx = -1;
	while(fgets(line, sizeof(line), f)){
		STRIP(line)
		char *opcode = strtok(line, " ");
		if(strcmp(opcode, "inp") == 0){
			isType1 = isType1Det = false;
			idx++;
		
		}else{
			if(strcmp(opcode, "mod") == 0){
				strtok(NULL, " ");
				if(!isType1)
					*mod = atoi(strtok(NULL, " "));

			}else if(strcmp(opcode, "div") == 0 &&
			         strcmp(strtok(NULL, " "), "z") == 0){
					int value = atoi(strtok(NULL, " "));
				   	if(value == 1)
						isType1 = true;
					else 
						isType1 = false;

					isType1Det = true;
			
			}else if(strcmp(opcode, "add") == 0 ){
				char *var = strtok(NULL, " ");
				if(strcmp(var, "y") == 0){
					if(isType1){
						type1[idx] = atoi(strtok(NULL, " "));
						type2[idx] = INT_MAX;
					}
				}else if(strcmp(var, "x") == 0){
					if(isType1Det && !isType1){
						type1[idx] = INT_MAX;
						type2[idx] = atoi(strtok(NULL, " "));
					}	
				}
			}
		}
	}
	fclose(f);
}

long long int day24_p1(char *file){

	int type1[14], type2[14], mod;

	parseMONAD(file, type1, type2, &mod);

	for(int i=9999999; i>=1111111; i--){
		char number[8];
		snprintf(number,8, "%d",i);
		if(strchr(number, '0') != NULL)
			continue;

		char res[15];
		int z = 0, dig_idx = 0;
		bool correct = true;

		for(int d=0; d<14; d++){
			if(type1[d] == INT_MAX){
				int calc = ((z%mod) + type2[d]);
				if(calc < 1 || calc > 9){
					correct = false;
					break;
				}

				res[d] = calc + '0';
				z /= mod;
			
			}else{
				res[d] = number[dig_idx];
				z = mod*z + (number[dig_idx]-'0') + type1[d];
				dig_idx++;
			}
		}
		res[14] = '\0';
		if(correct){
			return atoll(res);
		}
	}
	return 0;
}




long long int day24_p2(char *file){
	int type1[14], type2[14], mod;

	parseMONAD(file, type1, type2, &mod);

	for(int i=1111111; i<=9999999; i++){
		char number[8];
		snprintf(number,8, "%d",i);
		if(strchr(number, '0') != NULL)
			continue;

		char res[15];
		int z = 0, dig_idx = 0;
		bool correct = true;

		for(int d=0; d<14; d++){
			if(type1[d] == INT_MAX){
				int calc = ((z%mod) + type2[d]);
				if(calc < 1 || calc > 9){
					correct = false;
					break;
				}

				res[d] = calc + '0';
				z /= mod;
			
			}else{
				res[d] = number[dig_idx];
				z = mod*z + (number[dig_idx]-'0') + type1[d];
				dig_idx++;
			}
		}
		res[14] = '\0';
		if(correct){
			return atoll(res);
		}
	}
	return 0;
}



