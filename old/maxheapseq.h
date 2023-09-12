#ifndef __MAXHEAPSEQ_H__
#define __MAXHEAPSEQ_H__

#define SHOW_DECREASE_MAX_STEPS 1
#define MAX_HEAP_SIZE (1024*1024)
//#define parent(pos) ( pos/2 ) // SE nao usar posicao 0
#define parent(pos) ( (pos-1)/2 )

void drawHeapTree(int heap[], int size, int nLevels);
void maxHeapify(int heap[], int size, int i);
void heapifyUp(int heap[], int *size, int pos);
void insert( int heap[], int *size, int element);
int isMaxHeap(int heap[], int size);
void decreaseMax(int heap[], int size, int new_value);

#endif