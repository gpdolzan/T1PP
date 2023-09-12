#ifndef __SEQV2_H__
#define __SEQV2_H__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SHOW_DECREASE_MAX_STEPS 1
#define MAX_HEAP_SIZE (1024*1024)
#define parent(pos) ( (pos-1)/2 )

typedef struct elemento
{
    float chave;
    int valor;
}elemento;

elemento* allocateVector(int size);
void fillVector(elemento* vector, int size);
void freeVector(elemento* vector);

void drawHeapTree(elemento heap[], int size, int nLevels);
void maxHeapify(elemento heap[], int size, int i);
void heapifyUp(elemento heap[], int *size, int pos);
void insert(elemento heap[], int *size, elemento element);
int isMaxHeap(elemento heap[], int size);
void decreaseMax(elemento heap[], int size, float new_value);

#endif