#include "graph.h"

Graph* createGraph(){
	Graph *graph = malloc(sizeof(Graph));
	if(graph == NULL) 
		return NULL;

	graph->nodes = NULL;
	graph->sz = 0;
	return graph;	
}

GNode* createGNode(char *name){
	GNode *node = malloc(sizeof(GNode));
	if(node == NULL)
		return NULL;

	strcpy(node->name, name);
	node->isBigCave = (bool) isupper(name[0]);
	node->visited = false;
	node->numVisited = 0;
	node->next = NULL;
	node->nextSz = 0;
	return node;
}

int findNode(char *name, Graph *g){
	for(int i=0; i<g->sz; i++){
		if(strcmp(g->nodes[i]->name, name) == 0){
			return i;
		}
	}
	return -1;
}

int addGNode(GNode *node, Graph *g){
	if(g->nodes == NULL){
		g->nodes = malloc(sizeof(GNode*));
		g->nodes[0] = node;
		g->sz++;
		return 0;

	}else{
		int pos = findNode(node->name, g);
		if(pos != -1){
			return pos;

		}else{
			g->nodes = realloc(g->nodes, (g->sz+1) * sizeof(GNode));
			g->nodes[(g->sz)++] = node;	
			return (g->sz-1);
		}
	}
}

void addLineNodes(char *name, Graph *g, char *nextName){
	int pos1 = addGNode(createGNode(name), g);
	int pos2 = addGNode(createGNode(nextName), g);

	GNode *node1 = g->nodes[pos1];
	GNode *node2 = g->nodes[pos2];

	if(node1->next == NULL){
		node1->next = malloc(sizeof(GNode*));
	}else{
		node1->next = realloc(node1->next, (node1->nextSz+1) * sizeof(GNode*));
	}
	node1->next[node1->nextSz++] = node2;

	if(node2->next == NULL){
		node2->next = malloc(sizeof(GNode *));
	}else{
		node2->next = realloc(node2->next, (node2->nextSz+1) * sizeof(GNode*));
	}
	node2->next[node2->nextSz++] = node1;
}

void printGraph(Graph *g){
	printf("\nGRAPH\n");
	for(int i=0; i<g->sz; i++){
		printf("%s - ", g->nodes[i]->name);
		for(int j=0; j<g->nodes[i]->nextSz; j++){
			printf("%s / ", g->nodes[i]->next[j]->name);
		}
		printf("\n");
	}
}


//PART 1
int dfs(GNode *u, GNode *v, Graph *g){
	if(strcmp(u->name, v->name) == 0)
		return 1;
	else if(!u->isBigCave && u->visited) 
		return 0;


	u->visited = true;
	
	int paths = 0;
	for(int i=0; i<u->nextSz; i++){
		paths += dfs(u->next[i], v, g);
	}

	u->visited = false;
	return paths;
}

int findNumPaths(Graph *g){
	int startPos = findNode("start", g);
	GNode *start = g->nodes[startPos];

	int endPos = findNode("end", g);
	GNode *end = g->nodes[endPos];

	int numPaths = dfs(start, end, g);
	return numPaths;
}



//PART 2
int isInArray(char *s, char (*array)[SSIZE], int sz){
	for(int i=0; i<sz; i++){
		if(strcmp(s, array[i]) == 0) 
			return i;
	}
	return -1;
}

bool checkSmallCaveRepeated(Graph *g, char (*currentPath)[SSIZE], int idx){
	char nodes[g->sz][SSIZE];
	int repet[g->sz];
	int nodesSize = 0, pos;

	memset(repet, 0, g->sz * sizeof(int));
	memset(nodes, '\0', g->sz*SSIZE*sizeof(char));

	for(int i=0; i<idx; i++){
		pos = isInArray(currentPath[i], nodes, nodesSize);
		
		if(pos == -1){
			strcpy(nodes[nodesSize], currentPath[i]);
			repet[nodesSize++] = 1;

		}else{
			repet[pos]++;	
			if(!isupper(nodes[pos][0]) && repet[pos] >= 2)
				return true;
			
		}
	}
	return false;
}

int dfs2(GNode *u, GNode *v, Graph *g, char (*currentPath)[SSIZE], int *idx){
	bool smallCaveRep = checkSmallCaveRepeated(g, currentPath, *idx);

	if(strcmp(u->name, v->name) == 0)
		return 1;
	else if((strcmp(u->name, "start")==0 || strcmp(u->name, "end")==0) && u->numVisited >= 1)
		return 0;
	else if(!u->isBigCave && !smallCaveRep && u->numVisited >= 2)
		return 0;
	else if(!u->isBigCave && smallCaveRep && u->numVisited >= 1)
		return 0;
	

	u->numVisited++;
	strcpy(currentPath[(*idx)++], u->name);

	int paths = 0;
	for(int i=0; i<u->nextSz; i++){
		paths += dfs2(u->next[i], v, g, currentPath, idx);
	}

	currentPath[(*idx)--][0] = '\0';
	u->numVisited--;

	return paths;
}

int findNumPaths2(Graph *g){
	int startPos = findNode("start", g);
	GNode *start = g->nodes[startPos];

	int endPos = findNode("end", g);
	GNode *end = g->nodes[endPos];

	char currentPath[PATH_SIZE][SSIZE];
	int idx = 0;

	memset(currentPath, '\0', PATH_SIZE * SSIZE * sizeof(char));
	int numPaths = dfs2(start, end, g, currentPath, &idx);

	return numPaths;
}