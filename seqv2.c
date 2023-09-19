#include "seqv2.h"

int pair_cmpfunc (const void * a, const void * b)
{
    pair_t ea = *(const pair_t*) a;
    pair_t eb = *(const pair_t*) b;
    return (ea.key > eb.key) - (ea.key < eb.key);
}

int cmpfunc (const void * a, const void * b)
{
    float ea = *(const float*) a;
    float eb = *(const float*) b;
    return (ea > eb) - (ea < eb);
}

void printVector(float* vector, int size)
{
    printf("Vector: [ ");
    for(int i = 0; i < size; i++)
    {
        printf("%.0f ", vector[i]);
    }
    printf("]\n");
}

void printPairVector(pair_t* vector, int size)
{
    printf("Vector: [ ");
    for(int i = 0; i < size; i++)
    {
        printf("%.0f ", vector[i].key);
    }
    printf("]\n");
}

int binary_search(pair_t *array, int size, pair_t target)
{
    int low = 0;
    int high = size - 1;
    
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (pair_cmpfunc(&target, &array[mid]) == 0)
        {
            return mid;  // Target found
        }
        else if (pair_cmpfunc(&target, &array[mid]) < 0)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    
    return -1;  // Target not found
}

void verifyOutput(const float *Input, const pair_t *Output, int nTotalElmts, int k)
{
    int ok = 1;
    
    // 1) Create an array I of pairs (key, value)
    pair_t *I = malloc(nTotalElmts * sizeof(pair_t));
    for(int i = 0; i < nTotalElmts; i++)
    {
        I[i].key = Input[i];
        I[i].val = i;
    }

    // 2) Sort the array I in ascending order
    qsort(I, nTotalElmts, sizeof(pair_t), pair_cmpfunc);

    // 3) For each pair (ki,vi) belonging to the Output array
    for (int i = 0; i < k; i++)
    {
        if (binary_search(I, nTotalElmts, Output[i]) == -1)
        {
            ok = 0;
            break;
        }
    }

    if (ok)
    {
        printf("\nOutput set verified correctly.\n");
    } else
    {
        printf("\nOutput set DID NOT compute correctly!!!\n");
    }

    free(I);
}

// FIX ME!
void drawHeapTree(pair_t heap[], int size, int nLevels)
{    
    int offset = 0;
    //int space = (int)pow(2, nLevels - 1);
    
    int nElements = 1;
    for (int level = 0; level < nLevels; level++)
    {
        for (int i = offset; i < size && i < (offset + nElements); i++)
        {
            printf("[(%2.0f, %3d)]", heap[i].key, heap[i].val);
        }
        printf("\n");
        
        offset += nElements;
        //space = nElements - 1;
        nElements *= 2;
    }
}

void heapifyUp(pair_t heap[], int *size, int pos) {
    pair_t val = heap[pos];
    while (pos > 0 && val.key > heap[parent(pos)].key)
    {
        heap[pos] = heap[parent(pos)];
        pos = parent(pos);
    }
    heap[pos] = val;
}

void insert(pair_t heap[], int *size, pair_t element)
{
    *size += 1;
    int last = *size - 1;
    
    heap[last] = element;
    heapifyUp(heap, size, last);
}

int isMaxHeap(pair_t heap[], int size) {
    for (int i = 1; i < size; i++)
        if (heap[i].key <= heap[parent(i)].key)
            continue;
        else
        {
            printf("\nbroke at [%d]=%f\n", i, heap[i].key);
            printf("father at [%d]=%f\n", parent(i), heap[parent(i)].key);
            return 0;
        }
    return 1;
}

inline void swap(pair_t *a, pair_t *b)
{
    pair_t temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(pair_t heap[], int size, int i)
{
    while (1) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left].key > heap[largest].key)
            largest = left;

        if (right < size && heap[right].key > heap[largest].key)
            largest = right;

        if (largest != i)
        {
            swap(&heap[i], &heap[largest]);
            i = largest;
            
        }
        else
        {
            break;
        }
    }
}

void decreaseMax(pair_t heap[], int size, pair_t new_elem) 
{
    if (size == 0) // Heap is empty
        return;

    if (heap[0].key > new_elem.key)
    {
        heap[0].key = new_elem.key;
        heap[0].val = new_elem.val;
        maxHeapify(heap, size, 0);
    }
}