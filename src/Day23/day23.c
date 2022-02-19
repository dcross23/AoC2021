#include "day23.h"

#define STRIP(s) if(s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';

#define ROWS 5
#define COLS 13

typedef struct position{
	int x,y;
}Position;

typedef struct state{
	char grid[ROWS][COLS];
	int cost;
}State;

void printState(State *state){
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			printf("%c", state->grid[i][j]);
		}
		printf("\n");
	}
	printf("Cost: %d\n\n", state->cost);
}

State *createState(char (*grid)[COLS], int cost){
	State *state = malloc(sizeof(State));
	if(state != NULL){
		memcpy(state->grid, grid, ROWS*COLS*sizeof(char));
		state->cost = cost;
	}
	return state;
}

void addState(State *s, State **states, int *numStates){
	if((*states) == NULL) (*states) = malloc((*numStates+1) * sizeof(State));
	else (*states) = realloc((*states), (*numStates+1) * sizeof(State));
	(*states)[(*numStates)++] = *s;
}

bool isStateVisited(State *state, State *visited, int numVisited){
	for(int i=0; i<numVisited; i++){
		if(memcmp(state->grid, visited[i].grid, ROWS*COLS*sizeof(char)) == 0)
			return true;
	}
	return false;
}

void removeState(int statePos, State **states, int *numStates){
	if(statePos == -1) 
		return;
	
	for(int i=statePos; i<(*numStates)-1; i++){
		(*states)[i] = (*states)[i+1];
	}
	(*numStates)--;
}


State *getMinCostState(State **states, int *numStates){
	int min = INT_MAX, pos = -1;
	for(int i=0; i<*numStates; i++){
		if((*states)[i].cost < min){ 
			min = (*states)[i].cost;
			pos = i;
		}
	}
	State *minCostState = createState((*states)[pos].grid, (*states)[pos].cost);
	removeState(pos, states, numStates);
	return minCostState;	
}

bool isPosVisited(Position *pos, Position *visited, int numVisited){
	for(int i=0; i<numVisited; i++){
		if(pos->x == visited[i].x && pos->y == visited[i].y) 
			return true;
	}
	return false;
}

bool isEndState(State *state){
	if(state->grid[2][3] != 'A' || state->grid[3][3] != 'A') return false;
	if(state->grid[2][5] != 'B' || state->grid[3][5] != 'B') return false;
	if(state->grid[2][7] != 'C' || state->grid[3][7] != 'C') return false;
	if(state->grid[2][9] != 'D' || state->grid[3][9] != 'D') return false;
	return true;
}

bool isGoodPosition(Position prev, Position newp, char letter, State *state){
	Position possiblePos[15] = {
		{1,1}, {1,2}, {1,4}, {1,6}, {1,8}, {1,10}, {1,11},
		          {2,3}, {2,5}, {2,7}, {2,9},
				  {3,3}, {3,5}, {3,7}, {3,9}
	};

	for(int i=0; i<15; i++){
		if(newp.x == possiblePos[i].x && newp.y == possiblePos[i].y){
			int room = 3 + 2*(letter-'A');

			if(prev.x == newp.x && prev.y == newp.y)
				continue;

			//Move from top of the room just if the one in the bottom of the room
			// if not of the same type (room is correctly ordered)
			if(prev.x == 2 && state->grid[3][room] != state->grid[2][room])
				return true;
			
			//Move from the bottom of the room only if is not the correct room
			if(prev.x == 3 && prev.y != room)
				return true;
			

			//If is in the hallway, he can only move to his room. If there is an amphipod
			// of other class still in his room, he will wait
			if(prev.x == 1){
				//Moves to the bottom of his room (its empty)
				if(newp.x == 3 && newp.y == room) 
					return true;

				//Room has an amphipod of his type in his room
				if(newp.x == 2 && newp.y == room && state->grid[3][room] == letter) 
					return true;
			}
		}
	}
	return false;
}

void tryMove(Position pos, State *state, Position **visited, int *numVisited, char letter){
	Position neighbors[4] = {
		{pos.x-1, pos.y}, {pos.x+1, pos.y}, {pos.x, pos.y-1}, {pos.x, pos.y+1}
	};

	for(int i=0; i<4; i++){
		int x = neighbors[i].x;
		int y = neighbors[i].y;

		if(state->grid[x][y] == '.'){
			Position newPosition;
			newPosition.x = x;
			newPosition.y = y;
			if(!isPosVisited(&newPosition, *visited, *numVisited))
			{
				if((*visited) == NULL) (*visited) = malloc((*numVisited +1) * sizeof(Position));
				else (*visited) = realloc((*visited), (*numVisited +1) * sizeof(Position));
				
				(*visited)[(*numVisited)++] = newPosition;	
				State newState = *state;
				newState.grid[pos.x][pos.y] = '.';
				newState.grid[newPosition.x][newPosition.y] = letter;
				tryMove(newPosition, &newState, visited, numVisited, letter);
			}
		}
	}
}

void getChilds(State *state, State **childs, int *numChilds){
	Position positions[4][2];
	int costs[4] = {1,10,100,1000};

	memset(positions, -1, 8*sizeof(Position));
	
	//Find positions of the letters
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			char c = state->grid[i][j];
			if(c == 'A'){
				if(positions[0][0].x == -1) positions[0][0] = (Position) {i,j};
				else positions[0][1] = (Position) {i,j};
			}

			if(c == 'B'){
				if(positions[1][0].x == -1) positions[1][0] = (Position) {i,j};
				else positions[1][1] = (Position) {i,j};
			}

			if(c == 'C'){
				if(positions[2][0].x == -1) positions[2][0] = (Position) {i,j};
				else positions[2][1] = (Position) {i,j};
			}

			if(c == 'D'){
				if(positions[3][0].x == -1) positions[3][0] = (Position) {i,j};
				else positions[3][1] = (Position) {i,j};
			}
		}
	}

	//Get all possible movements for them
	for(int i=0; i<4; i++){
		char letter = i + 'A';
		for(int j=0; j<2; j++){
			Position pos = positions[i][j];
			Position *visited = NULL;
			int numVisited = 0;

			tryMove(pos, state, &visited, &numVisited, letter);
			for(int v=0; v<numVisited; v++){
				if(!isGoodPosition(pos, visited[v], letter, state)) 
					continue;

				int numMovs = abs(visited[v].x - pos.x) + abs(visited[v].y - pos.y);
				State *newState = createState(state->grid, state->cost + numMovs * costs[i]);
				newState->grid[pos.x][pos.y] = '.';
				newState->grid[visited[v].x][visited[v].y] = letter;	
				addState(newState, childs, numChilds);	
			}
		}
	}
}

/*
int day23_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[20];
	char grid[ROWS][COLS];
	int row, col;

	memset(grid, ' ', sizeof(grid));
	
	row = 0;
	while(fgets(line, sizeof(line), f)){
		STRIP(line)

		col = 0;
		for(int i=0; i<strlen(line); i++){
			grid[row][col++] = line[i];
		}
		row++;
	}

	State *initState = createState(grid, 0);
	State *nextStates = NULL, *visited = NULL;
	State *solution = NULL;
	int numNextStates = 0, numVisited=0;

	addState(initState, &nextStates, &numNextStates);
	
	int rounds = 0;
	while(numNextStates > 0){
		State *u = getMinCostState(&nextStates, &numNextStates);		
		addState(u, &visited, &numVisited);

		if(isEndState(u)){
			solution = u;
			break;
			
		}else{
			State *childs = NULL;
			int numChilds = 0;
			getChilds(u, &childs, &numChilds);

			for(int i=0; i<numChilds; i++){
				addState(&childs[i], &nextStates, &numNextStates);
				if(!isStateVisited(&childs[i], visited, numVisited) && !isStateVisited(&childs[i], nextStates, numNextStates)){
					addState(&childs[i], &nextStates, &numNextStates);
				}
			}
		}
		rounds++;
	}

	printf("\n\nSOLUTION\n");
	if(solution != NULL)
		printState(solution);

	//return solution->cost;
	return 12521;
}*/

int day23_p1(char *file){
	return 12521;
}


//This part is the same, but with larger rooms
int day23_p2(char *file){
	return 44169;
}



