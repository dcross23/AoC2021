#include "list.h"

Node* createNode(char data){
	Node *new = malloc(sizeof(Node));
	new->data = data;
	new->next = NULL;
	return new;
}

void addNode(Node* new, Node **list){
	if((*list) == NULL){
		(*list) = new; 
	}else{
		Node *aux = *list;
		while(aux->next != NULL)
			aux = aux->next;	
		
		aux->next = new;	
	}
}

void printList(Node *list){
	if(list == NULL)
		printf("NULL");
	else{
		Node *aux = list;
		while(aux != NULL){
			printf("%c ", aux->data);
			aux = aux->next;
		}
	}
}

bool isInList(char c, Node *list){
	Node *aux = list;
	while(aux != NULL){
		if(aux->data == c) 
			return true;

		aux = aux->next;
	}
	return false;
}

void removeFromList(char data, Node **list){
	Node *aux = *list, *prev = NULL;

	if(*list != NULL){
		while(aux != NULL){
			if(aux->data == data){
				if(prev == NULL)
					*list = (*list)->next;
				else
					prev->next = aux->next;
				
				free(aux);
				return;
			}
			prev = aux;
			aux = aux->next;
		}
	}
}

void clearList(Node **list){
	Node *aux = *list, *toRemove = NULL;

	while(aux != NULL){
		toRemove = aux;
		aux = aux->next;

		if(toRemove != NULL) free(toRemove);
	}

	*list = NULL;
}
