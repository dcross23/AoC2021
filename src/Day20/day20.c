#include "day20.h"

#define ROWS 1000
#define COLS 1000

#define STRIP(s) if(s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';

typedef struct image{
	char image[1000][1000];
	int rows, cols;
}Image;

Image* createImage(int rows, int cols){
	Image *image = malloc(sizeof(Image));
	if(image != NULL){
		image->rows = rows;
		image->cols = cols;	
		for(int i=0; i<rows; i++){
			memset(image->image[i], '.', cols * sizeof(char));
		}
	}
	return image;
}

Image* expand(Image *input, int size){
	Image *expansion = createImage(input->rows + size, input->cols + size);
	for(int i=0; i<size/2; i++){
		for(int j=0; j<expansion->cols;j++){
			expansion->image[i][j] = '.';
		}
	}

	for(int i=size/2; i<size/2 + input->rows; i++){
		for(int j=0; j<size/2; j++) 
			expansion->image[i][j] = '.';

		for(int j=size/2; j<size/2+input->cols; j++)
			expansion->image[i][j] = input->image[i-size/2][j-size/2];
		
		for(int j=size/2+input->cols; j<expansion->cols; j++) 
			expansion->image[i][j] = '.';
	}

	for(int i=size/2 + input->rows; i<expansion->rows; i++){
		for(int j=0; j<expansion->cols; j++){
			expansion->image[i][j] = '.';
		}
	}

	return expansion;
}


int binaryToDec(char *bin){
	int sum = 0;
	int mask = 1;
	for(int i = strlen(bin)-1, j=0; i>=0; i--, j++){
		sum += ((int) (bin[i]-'0')*(mask<<j));
	}
	return sum;
}

Image* enhance(Image *input, char enchAlg[512]){
	Image *output = createImage(input->rows, input->cols);
	char combination[10];
	memset(combination, '\0', 10 * sizeof(char));

	//Calculate output without getting the edges
	for(int i=1; i<input->rows-1; i++){
		for(int j=1; j<input->cols-1; j++){
			combination[0] = input->image[i-1][j-1] == '.' ? '0' : '1';
			combination[1] = input->image[i-1][j  ] == '.' ? '0' : '1';
			combination[2] = input->image[i-1][j+1] == '.' ? '0' : '1';
			combination[3] = input->image[i  ][j-1] == '.' ? '0' : '1';
			combination[4] = input->image[i  ][j  ] == '.' ? '0' : '1';
			combination[5] = input->image[i  ][j+1] == '.' ? '0' : '1';
			combination[6] = input->image[i+1][j-1] == '.' ? '0' : '1';
			combination[7] = input->image[i+1][j  ] == '.' ? '0' : '1';
			combination[8] = input->image[i+1][j+1] == '.' ? '0' : '1';
			combination[9] = '\0';

			int sust = binaryToDec(combination);
			output->image[i][j] = enchAlg[sust];
		}
	}
	
	//Just copy in the edges the value of background. Background is just 
	// the same when we move away from the initial drawing, so we can
	// copy any value close to the edge.
	char background = output->image[1][1];
	for(int i=0; i<output->rows; i++){
		if(i==0 || i==output->rows-1){
			for(int j=0; j<output->cols; j++){
				output->image[i][j] = background;
			}
		
		}else{
			output->image[i][0] = background;
			output->image[i][output->cols-1] = background;
		}
	}

	return output;
}

void printImage(Image *image){
	for(int i=0; i<image->rows; i++){
		for(int j=0; j<image->cols; j++){
			printf("%c", image->image[i][j]);
		}
		printf("\n");
	}
}

int day20_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[600];
	char enchAlg[512];
	char inImage[ROWS][COLS];
	int rows, cols;

	fgets(line, sizeof(line), f); 
	STRIP(enchAlg)
	for(int i=0; i<512; i++)
		enchAlg[i] = line[i];

	fgets(line, sizeof(line), f); //Jump blank line
	
	rows = 0;
	while(fgets(line, sizeof(line), f)){
		STRIP(line)
		cols = 0;
		for(int i=0; i<strlen(line); i++){
			inImage[rows][cols++] = line[i];
		}
		rows++;
	}

	Image *input = createImage(rows, cols);
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			input->image[i][j] = inImage[i][j];
		}
	}

	Image *expansion, *output;
	expansion = expand(input, 400);

	input = expansion;
	int rounds = 2;
	for(int steps = 0; steps<rounds; steps++){
		output = enhance(input, enchAlg);
		input = output;
	}

	int numLit = 0;
	for(int i=0; i<output->rows; i++){
		for(int j=0; j<output->cols; j++){
			if(output->image[i][j] == '#')
				numLit++;
		}
	}

	return numLit;
}




int day20_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[600];
	char enchAlg[512];
	char inImage[ROWS][COLS];
	int rows, cols;

	fgets(line, sizeof(line), f); 
	STRIP(enchAlg)
	for(int i=0; i<512; i++)
		enchAlg[i] = line[i];

	fgets(line, sizeof(line), f); //Jump blank line
	
	rows = 0;
	while(fgets(line, sizeof(line), f)){
		STRIP(line)
		cols = 0;
		for(int i=0; i<strlen(line); i++){
			inImage[rows][cols++] = line[i];
		}
		rows++;
	}

	Image *input = createImage(rows, cols);
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			input->image[i][j] = inImage[i][j];
		}
	}

	Image *expansion, *output;
	expansion = expand(input, 400);

	input = expansion;
	int rounds = 50;
	for(int steps = 0; steps<rounds; steps++){
		output = enhance(input, enchAlg);
		input = output;
	}

	int numLit = 0;
	for(int i=0; i<output->rows; i++){
		for(int j=0; j<output->cols; j++){
			if(output->image[i][j] == '#')
				numLit++;
		}
	}

	return numLit;
}



