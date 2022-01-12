#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define PATH_SIZE 100
#define SSIZE 20

typedef struct gnode{
	char name[10];
	bool isBigCave;
	bool visited;
	int numVisited;
	struct gnode **next;
	int nextSz; 
} GNode;

typedef struct graph{
	GNode **nodes;
	int sz;
}Graph;

Graph* createGraph();
GNode* createGNode(char *name);
int findNode(char *name, Graph *g);
int addGNode(GNode *node, Graph *g);
void addLineNodes(char *name, Graph *g, char *nextName);
void printGraph(Graph *g);

int dfs(GNode *u, GNode *v);
int findNumPaths(Graph *g);

int isInArray(char *s, char (*array)[SSIZE], int sz);
bool checkSmallCaveRepeated(Graph *g, char (*currentPath)[SSIZE], int idx);
int dfs2(GNode *u, GNode *v, Graph *g, char (*currentPath)[SSIZE], int *idx);
int findNumPaths2(Graph *g);

#endif
