#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "seqv2.h"
#include "input.h"

#define MAXTHREADS 8

typedef struct data_t
{
    int tID;
    int nElements;
    int start;
    int end;
    int heapSize;
}data_t;

int k;
int nThreads;
int nTotalElements;

float* Input;
pair_t* InputPair;
pair_t* Output;

pair_t* THeaps[MAXTHREADS];
pthread_t threads[MAXTHREADS];
data_t* data[MAXTHREADS];

void* heapMaker(void* arg)
{
    // Now convert void* to data_t*
    data_t* data = (data_t*)arg;

    int nElements = data->nElements;
    int start = data->start;
    int tID = data->tID;
    //int end = data->end;
    //int heapSize = data->heapSize;

    // Create a copy of the vector
    //pair_t* vector = (pair_t*)malloc(nElements * sizeof(pair_t));
    // use memcpy to copy the vector from start to end
    //memcpy(vector, InputPair + start, nElements * sizeof(pair_t));

    // print all int fields declared above
    //printf("Thread %d: nElements = %d\nstart = %d, end = %d\nSize of vector = %d\n\n", tID, nElements, start, end, end - start + 1);

    // print thread id
    //printf("Thread %d: nElements = %d\n", tID, nElements);
    // print thread id and vector using for loop
    /*for(int i = start; i <= end; i++)
    {
        printf("Thread %d: Input[%d] = %.0f\n", tID, i, Input[i]);
    }*/

    // Check if nElements is greater than k
    if(nElements >= k)
    {
        // Insert in THeaps until THeaps has k elements
        int i;
        for(i = 0; i < k;)
        {
            insert(THeaps[tID], &i, InputPair[start + i]);
        }

        // Keep using decreaseMax from where i stopped
        for(; i < nElements; i++)
        {
            decreaseMax(THeaps[tID], k, InputPair[start + i]);
        }
    }
    else
    {
        // Insert in THeaps until THeaps has nElements elements
        for(int i = 0; i < nElements;)
        {
            insert(THeaps[tID], &i, InputPair[start + i]);
        }
    }

    // Check if is max heap
    //printf("Thread %d: Is max heap? %d\n", tID, isMaxHeap(THeaps[tID], k));

    // Draw heap
    //printf("Thread %d: Heap\n", tID);
    //drawHeapTree(THeaps[tID], heapSize, 4);
    //printf("\n\n");

    // Return NULL
    return NULL;
}

int main(int argc, char const *argv[])
{
    readInput(argc, argv);
    nTotalElements = getNTotalElements();
    k = getK();
    nThreads = getNThreads();

    Input = (float*)malloc(nTotalElements * sizeof(float));
    InputPair = (pair_t*)malloc(nTotalElements * sizeof(pair_t));
    Output = (pair_t*)malloc(k * sizeof(pair_t));
    // Allocate memory for the heaps
    for(int i = 0; i < nThreads; i++)
    {
        THeaps[i] = (pair_t*)malloc(k * sizeof(pair_t));
    }

    for (int i = 0; i < nTotalElements; i++)
    {
        int a = rand();  // Returns a pseudo-random integer
	    int b = rand();  // same as above
        pair_t e;
        
        e.key = a * 100.0 + b;
        e.val = i;

        Input[i] = e.key;
	    InputPair[i] = e;
    }

    // Insert in Output until Output has k elements
    for(int i = 0; i < k;)
    {
        insert(Output, &i, InputPair[i]);
    }

    int elementsPerThread = nTotalElements / nThreads;
    int remainder = nTotalElements % nThreads;

    for(int i = 0; i < nThreads; i++)
    {
        // Allocate memory for data_t
        data[i] = (data_t*)malloc(sizeof(data_t));
        data[i]->tID = i;
    
        if (i == 0)
        {
            // Assign remainder to the first thread
            data[i]->nElements = elementsPerThread + remainder;
            data[i]->start = 0;
            data[i]->end = data[i]->start + data[i]->nElements - 1;
        }
        else
        {
            data[i]->nElements = elementsPerThread;
            data[i]->start = (i * elementsPerThread) + remainder;
            data[i]->end = data[i]->start + data[i]->nElements - 1;
        }

        // Allocate memory for the heap
        if(data[i]->nElements >= k)
        {
            THeaps[i] = (pair_t*)malloc(k * sizeof(pair_t));
            data[i]->heapSize = k;
        }
        else
        {
            data[i]->heapSize = data[i]->nElements;
            THeaps[i] = (pair_t*)malloc(data[i]->nElements * sizeof(pair_t));
        }
    }

    clock_t start = clock();

    // Create all threads
    for(int i = 0; i < nThreads; i++)
    {
        pthread_create(&threads[i], NULL, heapMaker, (void*)data[i]);
    }

    // Join all threads
    for(int i = 0; i < nThreads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();

    // For loop to merge all heaps
    for(int i = 0; i < nThreads; i++)
    {
        // For loop to insert all elements from THeaps[i] to Output
        for(int j = 0; j < data[i]->heapSize; j++)
        {
            // Use decreaseMax
            decreaseMax(Output, k, THeaps[i][j]);
        }
    }

    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    verifyOutput(Input, Output, nTotalElements, k);

    free(Input);
    free(InputPair);
    free(Output);

    return 0;
}