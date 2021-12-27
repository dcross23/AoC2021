#include "day8.h"
#include "list.h"

int day8_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[200];
	char *input, *output, *next;
	int count = 0;

	while(fgets(line, sizeof(line), f)){
		input = strtok(line, "|");
		output = strtok(NULL, "|");	
		output[strlen(output)-1] = '\0';

		next = strtok(output, " ");
		switch(strlen(next)){
			case 2: 
			case 3:
			case 4:
			case 7: count++;
				break;
		}

		while(NULL != (next = strtok(NULL, " "))){
			switch(strlen(next)){
				case 2: 
				case 3:
				case 4:
				case 7: count++;
					break;
			}
	
		}
	}

	return count;
}


bool isVisited(char c, char *visited, int numVisited){
	for(int i=0; i<numVisited; i++){
		if(c == visited[i]) return true;	
	}
	return false;
}

bool isNumber5Seg(int n, Node **segments, char *str){
	Node *aux;

	switch(n){
		case 2: 
			bool isOk;
			int count = 0, otherCount = 0;

			for(int i=0; i<strlen(str); i++){
				isOk = true;
				for(int j=0; j<7; j++){
					if(isInList(str[i], segments[j])){
						isOk = false;
						break;	
					}
				}

				if(isOk) return true;
			}

			return false;


		case 3:
			//Check if possibilities for segments 2,5 are in the string
			aux = segments[2];
			while(aux != NULL){
				if(!strchr(str, aux->data)) 
					return false;	
				aux = aux->next;
			}
			return true;
	
	}
}

void checkOutput(char *str, Node **segments, char *value){
	char combination[8];

	for(int i=0; i<7; i++)
		combination[i] = '0';

	for(int i=0; i<strlen(str); i++){
		for(int j=0; j<7; j++){
			if(isInList(str[i], segments[j])){
				combination[j] = '1';
				break;		
			} 		
		}
	}
	combination[7] = '\0';
	
	switch(atoi(combination)){
		case 1110111: value[0] = '0'; break; 
		case   10010: value[0] = '1'; break; 
		case 1011101: value[0] = '2'; break; 
		case 1011011: value[0] = '3'; break; 
		case  111010: value[0] = '4'; break; 
		case 1101011: value[0] = '5'; break; 
		case 1101111: value[0] = '6'; break; 
		case 1010010: value[0] = '7'; break; 
		case 1111111: value[0] = '8'; break; 
		case 1111011: value[0] = '9'; break; 
	}
	
	value[1] = '\0';
}


int day8_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[200];
	char *input, *output, *next;
	char **inputs, **outputs;
	int numInputs, numOutputs;
	
	char visited[7];
	int numVisited = 0;	
		
	bool isInListB;
	int count = 0;

	Node* segments[7];
	for(int i=0; i<7; i++)
		segments[i] = NULL;
	/*
	 *    000
	 *  1     2
	 *  1     2
	 *    333
	 *  4     5 
	 *  4     5
	 *    666
	 */
		
	while(fgets(line, sizeof(line), f)){
		numInputs = numOutputs = 0;
		
		input = strtok(line, "|");
		output = strtok(NULL, "|");	
		output[strlen(output)-1] = '\0';

		numInputs++;
		inputs = malloc(numInputs * sizeof(char *));
		inputs[numInputs -1] = strtok(input, " ");
			
		while(NULL != (next = strtok(NULL, " "))){
			numInputs++;
			inputs = realloc(inputs, numInputs * sizeof(char *));
			inputs[numInputs -1] = next;
		}


		numOutputs++;
		outputs = malloc(numOutputs * sizeof(char *));
		outputs[0] = strtok(output, " ");
		while(NULL != (next = strtok(NULL, " "))){
			numOutputs++;
			outputs = realloc(outputs, numOutputs * sizeof(char *));
			outputs[numOutputs -1] = next;
		}
		
	
		numVisited = 0;
		//Find posibilities for number 1 (2 active segments)
		for(int i=0; i<numInputs; i++){
			if(strlen(inputs[i]) == 2){
				for(int j=0; j<strlen(inputs[i]); j++){
					addNode(createNode(inputs[i][j]), &segments[2]); 
					addNode(createNode(inputs[i][j]), &segments[5]); 
					visited[numVisited++] = inputs[i][j];
				}
				break;
			}
		}	

		//Find posibilities for number 7 (3 active segments)
		// 2 of them have to be the same for 7 than for 1, so the new letter
		//  is the segment[0] 
		for(int i=0; i<numInputs; i++){
			if(strlen(inputs[i]) == 3){
				for(int j=0; j<3; j++){
					if(!isVisited(inputs[i][j], visited, numVisited)){
						addNode(createNode(inputs[i][j]), &segments[0]); 
						visited[numVisited++] = inputs[i][j];
						break;				
					}
				}	
				break;
			}
		}

		//Find posibilited for number 4 (4 active segments)
		// 2 of them have to be the same for 4 than for 1, so the 2 new letters
		//  are possibilities for segment[1], segment[3]	
		for(int i=0; i<numInputs; i++){
			if(strlen(inputs[i]) == 4){
				for(int j=0; j<4; j++){
					if(!isVisited(inputs[i][j], visited, numVisited)){
						addNode(createNode(inputs[i][j]), &segments[1]); 
						addNode(createNode(inputs[i][j]), &segments[3]); 
						visited[numVisited++] = inputs[i][j];
					}
				}	
				break;
			}
		}


		//Now next numbers are 2,3,5 (5 active segments). Just by recognizing 2 and 3 segments we
		// can determine all of them
		
		//Check for number 3 
		for(int i=0; i<numInputs; i++){
			if(strlen(inputs[i]) == 5 && isNumber5Seg(3, segments, inputs[i])){
				for(int j=0; j<strlen(inputs[i]); j++){
					if(isInList(inputs[i][j], segments[3])){
						clearList(&segments[3]);
						addNode(createNode(inputs[i][j]), &segments[3]); 
						removeFromList(inputs[i][j], &segments[1]);
					
					}else if(!isInList(inputs[i][j], segments[0]) && !isInList(inputs[i][j], segments[2])){
						addNode(createNode(inputs[i][j]), &segments[6]); 
						visited[numVisited++] = inputs[i][j];
					}		
				}
				
				break;
			}
		}

	
		//Check for number 2	
		for(int i=0; i<numInputs; i++){
			if(strlen(inputs[i]) == 5 && isNumber5Seg(2, segments, inputs[i])){
				for(int k=0; k<strlen(inputs[i]); k++){
					isInListB = false;
					for(int j=0; j<7; j++){
						if(isInList(inputs[i][k], segments[j])){
							isInListB = true;

							if(j == 2){
								clearList(&segments[2]);
								addNode(createNode(inputs[i][k]), &segments[2]); 
								removeFromList(inputs[i][k], &segments[5]);
							}
							break;	
						}
					}

					if(!isInListB){
						addNode(createNode(inputs[i][k]), &segments[4]); 
						visited[numVisited++] = inputs[i][k];
					}
				}
				break;
			}
		}

		//Here we have in the lists each letter associated with each segment
		char outputValue[200] = "";
		char value[2];
		for(int i=0; i<numOutputs; i++){
			checkOutput(outputs[i], segments, value);
			strcat(outputValue, value);
		}
		
		count += atoi(outputValue);
		
		for(int i=0; i<7; i++){
			clearList(&segments[i]);
		}
		numVisited = 0;
	}
	
	return count;
}
