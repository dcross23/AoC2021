#include "day4.h"

#define ROWS 5
#define COLS 5

typedef struct bingoNumber{
	int number;
	bool mark;
} BingoNumber;

typedef struct bingo{
	BingoNumber numbers[ROWS][COLS];
	bool finished;
} Bingo;


int checkRows(Bingo *bingo){
	int marked = 0;	
	for(int i=0; i<ROWS; i++){
		marked = 0;
		for(int j=0; j<COLS; j++){
			if(bingo->numbers[i][j].mark) marked++;
		}	

		if(marked == COLS) return i;
	}
	return -1;
}

int checkColumns(Bingo *bingo){
	int marked = 0;	
	for(int i=0; i<COLS; i++){
		marked = 0;
		for(int j=0; j<ROWS; j++){
			if(bingo->numbers[j][i].mark) marked++;
		}	

		if(marked == ROWS) return i;
	}
	return -1;
}

/**
 * Checks if a bingo has win
 */
int checkBingos(Bingo *bingos, int numBingos){
	int winner = -1;
	int ret;

	for(int i=0; i<numBingos; i++){
		if(!bingos[i].finished){
			//Check rows
			if(-1 != (ret = checkRows(&bingos[i])))
				return i;

			//Check columns
			else if(-1 != (ret = checkColumns(&bingos[i])))
				return i;
		}
	}

	return -1;
}


/**
 * Checks all bingos that win with that number
 */
int checkAllBingos(Bingo *bingos, int numBingos, int *bingosLeft){
	int winner = -1;
	int ret;
	int lastBingo = 0;
		
	for(int i=0; i<numBingos; i++){
		if(!bingos[i].finished){
			//Check rows
			if(-1 != (ret = checkRows(&bingos[i]))){
				bingos[i].finished = true;
				(*bingosLeft)--;
				lastBingo = i;
			}
			//Check columns
			else if(-1 != (ret = checkColumns(&bingos[i]))){
				bingos[i].finished = true;
				(*bingosLeft)--;
				lastBingo = i;
			}
		}
	}

	if(!(*bingosLeft)) return lastBingo;
	else return -1;	
}


/**
 * Creates a bingo from a string
 */
void parseBingo(char *str, int bingo, Bingo *bingos){
	char *nextNum;
	int i,j;

	nextNum = strtok(str, " ");
	bingos[bingo].numbers[0][0].number = atoi(nextNum);
        bingos[bingo].numbers[0][0].mark = false;
	
	i = 0;
	j = 1;
	while(NULL != (nextNum = strtok(NULL, " "))){
		bingos[bingo].numbers[i][j].number = atoi(nextNum);
        	bingos[bingo].numbers[i][j].mark = false;
		
		j++;
		if(j == COLS){
			j=0;  i++;
		}
	}	

	bingos[bingo].finished = false;
}


int day4_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	char secuence[300];
	char bingoString[80];

	char *nextSecNum;
	int numBingos = 0;
	Bingo *bingos = NULL;

	int bingoWinner, lastNumber, result;

	int i;
	char c;
	//Calculate the number of bingos
	for (c = getc(f); c != EOF; c = getc(f))
        	if (c == '\n') numBingos++;
	
	numBingos = (numBingos-1)/6;

	//Create bingos
	bingos = malloc(numBingos * sizeof(Bingo));


	//Read file and parse it
	fseek(f, 0, SEEK_SET);
	fgets(secuence, sizeof(secuence), f);
	fgets(line, sizeof(line), f); //Ignore blank line	
	
	strcpy(bingoString, "");
	i=0;
	while(fgets(line, sizeof(line), f)){
		if(line[0] == '\n'){
			parseBingo(bingoString, i, bingos);
			strcpy(bingoString, "");
			i++;	

		}else{
			line[strlen(line)-1] = '\0';
			strcat(bingoString, " ");
			strcat(bingoString, line);	
		}
	}

	parseBingo(bingoString, i, bingos);

	//Play bingo	
	nextSecNum = strtok(secuence, ",");	
	while(NULL != nextSecNum){
		for(int i=0; i<numBingos; i++){
			for(int c=0; c<ROWS; c++){
				for(int j=0; j<COLS; j++){
					if(bingos[i].numbers[c][j].number == atoi(nextSecNum)){
						bingos[i].numbers[c][j].mark = true;
						break;
					}
				}
			}
		}

		//Check if any bingo has finished
		if(-1 != (bingoWinner = checkBingos(bingos, numBingos))){
			lastNumber = atoi(nextSecNum);
			break;
		}

		nextSecNum = strtok(NULL, ",");
	}

	//Calculate data with winner
	result = 0;
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			if(!bingos[bingoWinner].numbers[i][j].mark)	
				result += bingos[bingoWinner].numbers[i][j].number;	
		}
	}	

	return result * lastNumber;
}




int day4_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	char secuence[300];
	char bingoString[80];

	char *nextSecNum;
	int numBingos = 0;
	Bingo *bingos = NULL;

	int bingoWinner, lastNumber, result;
	int bingosLeft;

	int i;
	char c;
	//Calculate the number of bingos
	for (c = getc(f); c != EOF; c = getc(f))
        	if (c == '\n') numBingos++;
	
	numBingos = (numBingos-1)/6;
	bingosLeft = numBingos;

	//Create bingos
	bingos = malloc(numBingos * sizeof(Bingo));


	//Read file and parse it
	fseek(f, 0, SEEK_SET);
	fgets(secuence, sizeof(secuence), f);
	fgets(line, sizeof(line), f); //Ignore blank line	
	
	strcpy(bingoString, "");
	i=0;
	while(fgets(line, sizeof(line), f)){
		if(line[0] == '\n'){
			parseBingo(bingoString, i, bingos);
			strcpy(bingoString, "");
			i++;	

		}else{
			line[strlen(line)-1] = '\0';
			strcat(bingoString, " ");
			strcat(bingoString, line);	
		}
	}

	parseBingo(bingoString, i, bingos);

	//Play bingo	
	nextSecNum = strtok(secuence, ",");	
	while(NULL != nextSecNum){
		for(int i=0; i<numBingos; i++){
			if(!bingos[i].finished){
				for(int c=0; c<ROWS; c++){
					for(int j=0; j<COLS; j++){
						if(bingos[i].numbers[c][j].number == atoi(nextSecNum)){
							bingos[i].numbers[c][j].mark = true;
							break;
						}
					}
				}
			}
		}

		//Check if any bingo has finished
		if(-1 != (bingoWinner = checkAllBingos(bingos, numBingos, &bingosLeft))){
			lastNumber = atoi(nextSecNum);
			if(bingosLeft == 0) 
				break;
		}

		nextSecNum = strtok(NULL, ",");
	}

	//Calculate data with winner
	result = 0;
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			if(!bingos[bingoWinner].numbers[i][j].mark)	
				result += bingos[bingoWinner].numbers[i][j].number;	
		}
	}	

	return result * lastNumber;
}



