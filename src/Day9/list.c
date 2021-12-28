#include "list.h"

PNode* createPNode(Point p){
	PNode *new = malloc(sizeof(PNode));
	new->p = p;
	new->next = NULL;
	return new;
}

bool isPListEmpty(PNode *list){
	return list == NULL;
}

int getPListSize(PNode *list){
	PNode *aux = list;
	int size = 0;
	while(aux != NULL){
		size++;
		aux = aux->next;
	}
	return size;
}

void addPNode(PNode* new, PNode **list){
	if((*list) == NULL){
		(*list) = new; 
	}else{
		PNode *aux = *list;
		while(aux->next != NULL)
			aux = aux->next;	
		
		aux->next = new;	
	}
}

void removeFromPList(Point p, PNode **list){
	PNode *aux = *list, *prev = NULL;

	if(*list != NULL){
		while(aux != NULL){
			if(aux->p.x==p.x && aux->p.y==p.y){
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

Point getFromPList(PNode **list){
	PNode *aux = *list;
	Point p;
	p.x = aux->p.x; 
	p.y = aux->p.y;

	*list = (*list)->next;
	free(aux);
	return p;
}

bool isInPList(Point p, PNode *list){
	PNode *aux = list;
	while(aux != NULL){
		if(aux->p.x==p.x && aux->p.y==p.y) 
			return true;

		aux = aux->next;
	}
	return false;

}

void printPList(PNode *list){
	if(list == NULL)
		printf("NULL");
	else{
		PNode *aux = list;
		while(aux != NULL){
			printf("(%d,%d) ", aux->p.x, aux->p.y);
			fflush(stdout);
			aux = aux->next;
		}
	}

}


void clearPList(PNode **list){
	PNode *aux = *list, *toRemove = NULL;

	while(aux != NULL){
		toRemove = aux;
		aux = aux->next;

		if(toRemove != NULL) free(toRemove);
	}

	*list = NULL;
}
