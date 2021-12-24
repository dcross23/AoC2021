#include "day3.h"

#define BITS_C 20
#define NUMBERS 1000

int day3_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	unsigned short bits[BITS_C][2];
	int numBits = 0;
	unsigned short gamma = 0, epsilon = 0;

	memset(bits, 0, 2 * BITS_C * sizeof(bits[0][0]));
	
	while(fgets(line, sizeof(line), f)){
	 	numBits = strlen(line) - 1;
		for(int i=0; i<numBits; i++){
			bits[i][line[i] - '0']++;					
		}
	}
	
	for(int i=0; i<numBits; i++){
		if(bits[i][0] > bits[i][1])
			epsilon |= (1<<(numBits-1-i));
		else
			gamma |= (1<<(numBits-1-i));		
	}

	return gamma * epsilon;
}


int day3_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	unsigned short oxygenBits[2];
	unsigned short co2Bits[2];
	int numBits = 0, numLeft;
	
	unsigned short oxygen[NUMBERS];
	int oxygenIndexes[NUMBERS];
	unsigned short co2[NUMBERS];
	int co2Indexes[NUMBERS];
	char oxygenBit, co2Bit;

	int finalOxygen, finalCo2;

	memset(oxygenBits, 0, 2 * sizeof(oxygenBits[0]));
	memset(co2Bits, 0, 2 * sizeof(co2Bits[0]));
	memset(oxygen, 0, NUMBERS * sizeof(oxygen[0]));
	memset(co2, 0, NUMBERS * sizeof(co2[0]));
	memset(oxygenIndexes, -1, NUMBERS * sizeof(oxygenIndexes[0]));
	memset(co2Indexes, -1, NUMBERS * sizeof(co2Indexes[0]));

	int idx = 0;
	while(fgets(line, sizeof(line), f)){
		numBits = strlen(line) - 1;

		oxygenBits[line[0] - '0']++;
		co2Bits[line[0] - '0']++;

		for(int i=0; i<numBits; i++){
			oxygen[idx] |= ((line[i]-'0') << numBits-1-i);
			co2[idx] |= ((line[i]-'0') << numBits-1-i);

			oxygenIndexes[idx] = co2Indexes[idx] = idx;
		}
		idx++;
	}

	numLeft = idx;
	//Calculate oxygen generator rating
	for(int i=0; i<numBits; i++){
		for(int j=0; j<NUMBERS; j++){	
			oxygenBit = (oxygen[j] & (1<<(numBits-1-i))) >> (numBits-1-i); 
			
			if(oxygenBits[0] > oxygenBits[1]){
				if(oxygenIndexes[j]!=-1 && oxygenBit==1){
					oxygenIndexes[j] = -1;		
					numLeft--;
				}	

			}else{
				if(oxygenIndexes[j]!=-1 && oxygenBit==0){
					oxygenIndexes[j] = -1;		
					numLeft--;
				}	
			}
		}

		if(numLeft == 1) break;

		//Calculate next bit
		oxygenBits[0] = oxygenBits[1] = 0;
		for(int k=0; k<NUMBERS; k++){
			if(oxygenIndexes[k] != -1) 
				oxygenBits[(oxygen[k] & (1<<(numBits-i-2))) >> (numBits-i-2)]++;
		}
	}


	numLeft = idx;
	//Calculate CO2 scrubber rating
	for(int i=0; i<numBits; i++){
		for(int j=0; j<NUMBERS; j++){	
			co2Bit = (co2[j] & (1<<(numBits-1-i))) >> (numBits-1-i); 
			
			if(co2Bits[0] > co2Bits[1]){
				if(co2Indexes[j]!=-1 && co2Bit==0){
					co2Indexes[j] = -1;	
					numLeft--;
				}	

			}else{
				if(co2Indexes[j]!=-1 && co2Bit==1){
					co2Indexes[j] = -1;	
					numLeft--;
				}		
			}
		}

		if(numLeft == 1) break;

		//Calculate next bit
		co2Bits[0] = co2Bits[1] = 0;
		for(int k=0; k<NUMBERS; k++){
			if(co2Indexes[k] != -1)
				co2Bits[(co2[k] & (1<<(numBits-i-2))) >> (numBits-i-2)]++;
		}
	}

	//Get solutions
	for(int i=0; i<NUMBERS; i++){
		if(oxygenIndexes[i] != -1) finalOxygen = oxygen[i];

		if(co2Indexes[i] != -1) finalCo2 = co2[i];
	}

	return finalOxygen * finalCo2;
}


