#include "day10.h"

const char opened[4] = {'(', '[', '{', '<'};
const char closed[4] = {')', ']', '}', '>'};

typedef struct stack{
		char stack[150];
		int size;
} Stack;

Stack* createStack(){
	Stack *stack = malloc(sizeof(Stack));
	if(stack == NULL) return NULL;
	stack->size = 0;
}

void push(char c, Stack *stack){
	stack->stack[stack->size++] = c;
}

char pop(Stack *stack){
	char c = stack->stack[stack->size-1];
	stack->size--;
	return c;
}

void printStack(Stack *stack){
	printf("S: ");
	for(int i=0; i<stack->size; i++){
		printf("%c", stack->stack[i]);
	}
}

long long int checkLine(char *line, bool *corrupted){
	char c;
	
	Stack *stack = createStack();
	if(stack == NULL){
		printf("xD\n");
		return -1;
	} 

	*corrupted = false;
	for(int i=0; i<strlen(line); i++){
		c = line[i];
		if(c == '\n') continue;

		for(int j=0; j<4; j++){
			if(c == opened[j]){
				push(c, stack);
				break;
					
			}else if(c == closed[j]){
				switch(pop(stack)){
					case '(': if(c != ')') *corrupted = true; 
							break;
					case '[': if(c != ']') *corrupted = true; 
							break;
					case '{': if(c != '}') *corrupted = true; 
							break;
					case '<': if(c != '>') *corrupted = true; 
							break;
				}
				break;
			}
		}

		if(*corrupted) break;
	}

	long long int value = 0;
	if(*corrupted){
		switch(c){
			case ')': value = 3; break;
			case ']': value = 57; break;
			case '}': value = 1197; break;
			case '>': value = 25137; break;
		}

	}else{
		value = 0;
		while(stack->size > 0){
			c = pop(stack);
			switch (c){
				case '(': value*=5; value+=1; break;
				case '[': value*=5; value+=2; break;
				case '{': value*=5; value+=3; break;
				case '<': value*=5; value+=4; break;
			}
			
		}
	}

	free(stack);
	return value;
}


long long int day10_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

	char line[150];
	long long int linePoints, count;
	bool corrupted;

	count = 0;
	while(fgets(line, sizeof(line), f)){
		if(-1 != (linePoints = checkLine(line, &corrupted))){
			if(corrupted) count += linePoints;
		}
	}

	return count;
}



void sort(long long int *array, int n){
	long long int a;
	for (int i = 0; i < n; i++){
     		for (int j = i + 1; j < n; j++){
         		if (array[i] > array[j]){
         			a = array[i];
            		array[i] = array[j];
            		array[j] = a;
         		}
      		}
   	}
}


long long int day10_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

	char line[150];
	long long int linePoints;
	long long int *array = NULL;
	int arraySz = 0;
	bool corrupted;

	while(fgets(line, sizeof(line), f)){
		linePoints = checkLine(line, &corrupted);
		if(-1 != linePoints && !corrupted){
				if(array == NULL) 
					array = malloc(1 * sizeof(long long int));
				else 
					array = realloc(array, (arraySz+1) * sizeof(long long int));

				array[arraySz++] = linePoints;
		}
	}

	sort(array, arraySz);
	return array[arraySz/2];
}
