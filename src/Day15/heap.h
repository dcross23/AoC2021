#ifndef __HEAP_H__
#define __HEAP_H__

#define MAX_SIZE 500*500

typedef struct point{
	int r,c;
}Point; 

typedef int heapKey;
typedef Point heapInfo;	

typedef struct{
	heapKey key;
	heapInfo info;
} heapElement;

typedef struct{ 
	heapElement elements[MAX_SIZE];
	int size;
} Heap;


// Heap methods 
int initHeap(Heap *h);
int isHeapEmpty(Heap *h);
int add(heapElement x, Heap *h);
int removeTop(Heap *h, heapElement *minElement);
int decrementKey(int pos, heapKey amount, Heap *h);
int incrementKey(int pos, heapKey amount, Heap *h);
int isHeap(Heap *h);

int heapify(Heap *h);

// Filtering functions
void descFiltering(Heap *h, int posToFilter);
void ascFiltering(Heap *h, int posToFilter);


#endif
