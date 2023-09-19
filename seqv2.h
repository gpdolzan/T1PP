#ifndef __SEQV2_H__
#define __SEQV2_H__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

#define SHOW_DECREASE_MAX_STEPS 1
#define MAX_HEAP_SIZE (1024*1024)
#define parent(pos) ( (pos-1)/2 )

typedef struct pair_t
{
    float key;
    int val;
}pair_t;

int pair_cmpfunc (const void * a, const void * b);
int cmpfunc (const void * a, const void * b);
void printVector(float* vector, int size);
void printPairVector(pair_t* vector, int size);
int binary_search(pair_t *array, int size, pair_t target);
void verifyOutput(const float *Input, const pair_t *Output, int nTotalElmts, int k);


void drawHeapTree(pair_t heap[], int size, int nLevels);
void maxHeapify(pair_t heap[], int size, int i);
void heapifyUp(pair_t heap[], int *size, int pos);
void insert(pair_t heap[], int *size, pair_t element);
int isMaxHeap(pair_t heap[], int size);
void decreaseMax(pair_t heap[], int size, pair_t new_elem);

#endif