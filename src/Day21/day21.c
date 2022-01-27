#include "day21.h"
#define STRIP(s) if(s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';

int advance(int *playerPos, int *rolls){
	int move = 0;
	for(int i=0; i<3; i++)
		move += rolls[i];
	
	(*playerPos) += move;
	(*playerPos) = (*playerPos -1)%10 +1;
	return (*playerPos);
}

void getRolls(int *die, int *rolls){
	for(int i=0; i<3; i++){
		*die = (*die -1)%100 + 1;	
		rolls[i] = (*die)++;
	}	
}

int day21_p1(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[50];
	int p1Pos, p2Pos;

	fgets(line, sizeof(line),f);
	STRIP(line)
	strtok(line, ":");
	p1Pos = atoi(strtok(NULL, ":"));

	fgets(line, sizeof(line),f);
	STRIP(line)
	strtok(line, ":");
	p2Pos = atoi(strtok(NULL, ":"));

	int die = 1, diesRolled = 0, looser;
	int rolls[3];
	int p1Score = 0, p2Score = 0;

	while(true){
		getRolls(&die, rolls);
		p1Score += advance(&p1Pos, rolls);
		diesRolled += 3;
		if(p1Score >= 1000){
			looser = p2Score;
			break;
		}

		getRolls(&die, rolls);
		p2Score += advance(&p2Pos, rolls);
		diesRolled += 3;
		if(p2Score >= 1000){
			looser = p1Score;
			break;
		}
	}

	return diesRolled * looser;
}




#define HASH_MOD 262144

typedef struct wins{
	long long int p1Wins;
	long long int p2Wins;
}Wins;

typedef struct state{
	int p1Pos;
	int p2Pos;
	long long int p1Score;
	long long int p2Score;
	bool isP1Turn;
}State;

typedef struct key{
	State state;
	Wins wins;
	struct key *next;
}Key;

typedef struct cache{
	Key *keys[HASH_MOD];
}Cache;

//SDBM hash
unsigned long hash(State *state){
	unsigned long hash = 0;
	hash = state->p1Pos    + (hash << 6) + (hash << 16) - hash;
	hash = state->p2Pos    + (hash << 6) + (hash << 16) - hash;
	hash = state->p1Score  + (hash << 6) + (hash << 16) - hash;
	hash = state->p2Score  + (hash << 6) + (hash << 16) - hash;
	hash = state->isP1Turn + (hash << 6) + (hash << 16) - hash;
	return hash % HASH_MOD;
}

Cache *createCache(){
	Cache *cache = malloc(sizeof(Cache));
	if(cache != NULL){
		for(int i=0; i<HASH_MOD; i++){
			cache->keys[i] = NULL;
		}
	}
	return cache;
}

bool equalStates(State *s1, State *s2){
	return s1->p1Pos == s2->p1Pos && s1->p2Pos == s2->p2Pos 
	    && s1->p1Score == s2->p1Score && s1->p2Score== s2->p2Score
		&& s1->isP1Turn == s2->isP1Turn;
}

Key *createKey(State state, Wins wins){
	Key *key = malloc(sizeof(Key));
	if(key != NULL){
		key->state = state;
		key->wins = wins;
		key->next = NULL;
	}
	return key;
}

bool getKey(State *state, Wins *wins, Cache *cache){
	Key *aux = cache->keys[hash(state)];
	while(aux != NULL){
		if(equalStates(state, &aux->state)){
			wins->p1Wins = aux->wins.p1Wins;
			wins->p2Wins = aux->wins.p2Wins;
			return true;
		}
		aux = aux->next;
	}
	return false;
}

void addKey(State *state, Wins *wins, Cache *cache){
	Key *key = createKey(*state, *wins);
	unsigned long hashLoc = hash(state);
	key->next = cache->keys[hashLoc];
	cache->keys[hashLoc] = key;
}

Wins game(State *state, Cache *cache){
	Wins wins;
	if(state->p1Score >= 21){
		return (Wins){1,0};

	}else if(state->p2Score >= 21){
		return (Wins){0,1};

	}else if(getKey(state, &wins, cache)){
		return wins;

	}else{
		wins.p1Wins = wins.p2Wins = 0;
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				for(int k=0; k<3; k++){
					State newState = *state;
					if(state->isP1Turn){
						newState.isP1Turn = false;
						newState.p1Pos += (i+1) + (j+1) + (k+1);
						newState.p1Pos = (newState.p1Pos -1)%10 +1;
						newState.p1Score +=newState.p1Pos; 

					}else{
						newState.isP1Turn = true;
						newState.p2Pos += (i+1) + (j+1) + (k+1);
						newState.p2Pos = (newState.p2Pos -1)%10 +1;
						newState.p2Score += newState.p2Pos; 
					}
					Wins w = game(&newState, cache);
					wins.p1Wins += w.p1Wins;
					wins.p2Wins += w.p2Wins;	
				}
			}
		}
		addKey(state, &wins, cache);
		return wins;
	}
}

long long int day21_p2(char *file){
	FILE *f;

	if(NULL == (f = fopen(file, "r")))
		return -1;

 	char line[50];
	int p1Pos, p2Pos;

	fgets(line, sizeof(line),f);
	STRIP(line)
	strtok(line, ":");
	p1Pos = atoi(strtok(NULL, ":"));

	fgets(line, sizeof(line),f);
	STRIP(line)
	strtok(line, ":");
	p2Pos = atoi(strtok(NULL, ":"));

	Cache *cache = createCache();
	State initState;
	initState.p1Pos = p1Pos;
	initState.p2Pos = p2Pos;
	initState.p1Score = initState.p2Score = 0;
	initState.isP1Turn = true;
	Wins wins = game(&initState, cache);

	if(wins.p1Wins > wins.p2Wins)
		return wins.p1Wins;
	else
		return wins.p2Wins;
}



