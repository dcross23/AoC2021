#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct point{
	int x,y;
}Point;

typedef struct node{
	Point p;
	struct node *next;
}PNode; 

PNode* createPNode(Point p);
void addPNode(PNode* new, PNode **list);
void removeFromPList(Point p, PNode **list);
Point getFromPList(PNode **list);
bool isInPList(Point p, PNode *list);

bool isPListEmpty(PNode *list);
int getPListSize(PNode *list);

void clearPList(PNode **list);

void printPList(PNode *list);

#endif
