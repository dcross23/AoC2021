#include "day16.h"

char hexRep[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char binRep[16][5] = {"0000","0001","0010","0011",
                      "0100","0101","0110","0111",
					  "1000","1001","1010","1011",
					  "1100","1101","1110","1111"};

int lton(char c){
	if(c < 'A') return (c-'0');
	else return (c-'0'-7);
}

void substr(char *str,int i,int j, char *dst){
	strncpy(dst,str+i,j-i+1);
}

char* hexToBin(char hex){
	return binRep[lton(hex)];
}

char binToHex(char *bin){
	char b[5] = "";
	if(strlen(bin) < 4){
		while(strlen(b) < 4 - strlen(bin)) strcat(b, "0");
	}
	strcat(b, bin);
	for(int i=0; i<16; i++)
		if(strcmp(b, binRep[i])==0) {
			return hexRep[i];
		}
}

int64_t binToDec(char *bin){
	int64_t sum = 0;
	int64_t mask = 1;
	for(int i = strlen(bin)-1, j=0; i>=0; i--, j++){
		sum += ((int64_t) lton(bin[i])*(mask<<j));
	}
	return sum;
}

int parsePackage(char *binstr, int *package_sz){
	char packetVersion[4]="", packetTypeID[4]="";
	char packet[6]="", literal[1500] = "";
	char lenghtTypeID[2] = "", nBitsSP[16]="", numSP[12]="", subpacket[16] = "";
	int pv, ptid, lit, sp_len, sp_num;

	//Get packet version and packet type id (all packages have them)
	substr(binstr, 0, 2, packetVersion);
	substr(binstr, 3, 5, packetTypeID);
	pv = hexRep[lton(binToHex(packetVersion))];
	ptid = hexRep[lton(binToHex(packetTypeID))];
	*package_sz = 6;

	//Types of packages depending on package type id
	//LITERAL PACKAGE
	if(ptid == '4'){
		int i=0;
		do{
			substr(binstr, 6+5*i, 10+5*i, packet);
			strcat(literal, packet + 1);
			i++;
			(*package_sz) += 5;
		}while(packet[0] == '1');

		lit = binToDec(literal);
		return lton(pv);
	

	//OPERATOR PACKAGE
	}else{
		int versionSum = lton(pv);

		//Get lenght type id
		substr(binstr, 6, 6, lenghtTypeID);
		(*package_sz)++;

		//Mode depeding on length type id
		//15-bit subpackages lenght
		if(lenghtTypeID[0] == '0'){
			//Get total length of subpackages
			substr(binstr, 7, 7+14, nBitsSP);	
			sp_len = binToDec(nBitsSP);
			(*package_sz)+=15;

			//Process subpackages
			char subpackages[(*package_sz)+1];
			int prevp_sz = (*package_sz), newp_sz = 0;
			
			while((*package_sz)-prevp_sz < sp_len){	
				versionSum += parsePackage(binstr + (*package_sz), &newp_sz);
				(*package_sz) += newp_sz;
			}

		}
		//11-bin number of subpackages
		else{
			//Get number of subpackages
			substr(binstr, 7, 7+10, numSP);	
			sp_num = binToDec(numSP);
			(*package_sz)+=11;

			int newp_sz = 0;
			for(int i=0; i<sp_num; i++){
				versionSum += parsePackage(binstr + (*package_sz), &newp_sz);
				(*package_sz) += newp_sz;
			}
		}
		return versionSum;
	}
}

int day16_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[1500];
	fgets(line, sizeof(line), f);

	char binstr[4 * strlen(line)];
	
	binstr[0] = '\0';
	for(int i=0; i<strlen(line); i++){
		strcat(binstr, hexToBin(line[i]));
	}

	int package_sz;
	return parsePackage(binstr, &package_sz);
}


int64_t operation(int ptid, int64_t *sp_values, int nValues){
	int64_t res;
	switch(ptid){
		case 0: //SUM 
				res = 0;
				for(int i=0; i<nValues; i++) res += sp_values[i];
				return res;

		case 1: //PRODUCT 
				res = 1;
				for(int i=0; i<nValues; i++) res *= sp_values[i];
				return res;

		case 2: //MINIMUM 
			res = LLONG_MAX;
			for(int i=0; i<nValues; i++) 
				if(sp_values[i] < res) res = sp_values[i];
			return res;

		case 3: //MAXIMUM 
			res = LLONG_MIN;
			for(int i=0; i<nValues; i++) 
				if(sp_values[i] > res) res = sp_values[i];
			return res;

		case 5: //GREATER THAN 
			return (sp_values[0] > sp_values[1]);

		case 6: //LESS THAN 
			return (sp_values[0] < sp_values[1]);

		case 7: //EQUAL TO
			return (sp_values[0] == sp_values[1]);
	}
}

int64_t parsePackage2(char *binstr, int *package_sz){
	char packetVersion[4]="", packetTypeID[4]="";
	char packet[6]="", literal[4 * 1500] = "";
	char lenghtTypeID[2] = "", nBitsSP[16]="", numSP[12]="";
	int pv, ptid;
	int64_t sp_len, sp_num, lit;
	int64_t *sp_values = NULL; 
	int64_t nValues = 0;

	//Get packet version and packet type id (all packages have them)
	substr(binstr, 0, 2, packetVersion);
	substr(binstr, 3, 5, packetTypeID);
	pv = hexRep[lton(binToHex(packetVersion))];
	ptid = hexRep[lton(binToHex(packetTypeID))];
	*package_sz = 6;

	//Types of packages depending on package type id
	//LITERAL PACKAGE
	if(ptid == '4'){
		int i=0;
		do{
			substr(binstr, 6+5*i, 10+5*i, packet);
			strcat(literal, packet + 1);
			i++;
			(*package_sz) += 5;
		}while(packet[0] == '1');

		lit = binToDec(literal);
		return lit;
	

	//OPERATOR PACKAGE
	}else{
		//Get lenght type id
		substr(binstr, 6, 6, lenghtTypeID);
		(*package_sz)++;

		//Mode depeding on length type id
		//15-bit subpackages lenght
		if(lenghtTypeID[0] == '0'){
			//Get total length of subpackages
			substr(binstr, 7, 7+14, nBitsSP);	
			sp_len = binToDec(nBitsSP);
			(*package_sz)+=15;

			//Process subpackages
			int prevp_sz = (*package_sz), newp_sz = 0;
			int64_t sp_value;
			
			while((*package_sz)-prevp_sz < sp_len){	
				sp_value = parsePackage2(binstr + (*package_sz), &newp_sz);
				
				if(sp_values == NULL) 
					sp_values = malloc((nValues+1) * sizeof(int64_t));
				else 
					sp_values = realloc(sp_values, (nValues+1) * sizeof(int64_t));

				sp_values[(nValues)++] = sp_value;
				(*package_sz) += newp_sz;
			}

		}
		//11-bin number of subpackages
		else{
			//Get number of subpackages
			substr(binstr, 7, 7+10, numSP);	
			sp_num = binToDec(numSP);
			(*package_sz)+=11;

	 		int newp_sz = 0;
            int64_t sp_value; 
     		for(int i=0; i<sp_num; i++){
				sp_value = parsePackage2(binstr + (*package_sz), &newp_sz);
				
				if(sp_values == NULL) 
					sp_values = malloc((nValues+1) * sizeof(int64_t));
				else 
					sp_values = realloc(sp_values, (nValues+1) * sizeof(int64_t));

				sp_values[nValues++] = sp_value;
				(*package_sz) += newp_sz;
			}
		}

		int64_t op = operation(lton(ptid), sp_values, nValues);
		free(sp_values);
		return op;
	}
}



int64_t day16_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[1500];
	fgets(line, sizeof(line), f);
	if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';

	char binstr[4 * strlen(line)];
	
	binstr[0] = '\0';
	for(int i=0; i<strlen(line); i++){
		strcat(binstr, hexToBin(line[i]));
	}

	int package_sz;
	int64_t res = parsePackage2(binstr, &package_sz);
	return res;
}

int64_t testDay16_p2(char *str){
	char binstr[4 * strlen(str)];

	if(str[strlen(str)-1] == '\n') str[strlen(str)-1] = '\0';
	
	binstr[0] = '\0';
	for(int i=0; i<strlen(str); i++){
		strcat(binstr, hexToBin(str[i]));
	}

	int package_sz;
	int64_t res = parsePackage2(binstr, &package_sz);
	return res;
}



