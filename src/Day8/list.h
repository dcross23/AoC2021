#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node{
	char data;
	struct node *next;
}Node; 


Node* createNode(char data);
void addNode(Node* new, Node **list);
void printList(Node *list);
bool isInList(char c, Node *list);
void removeFromList(char data, Node **list);
void clearList(Node **list);


#endif
