#include "seqv2.h"

elemento* allocateVector(int size)
{
    elemento* vector = (elemento*) malloc(size * sizeof(elemento));
    return vector;
}

void fillVector(elemento* vector, int size)
{
    for (int i = 0; i < size; i++)
    {
        int a = rand();  // Returns a pseudo-random integer
	    int b = rand();  // same as above
	    float value = a * 100.0 + b;
        elemento e = {i, value};

        // inserir o elemento e na posição i
	    vector[i] = e;
    }
}

void freeVector(elemento* vector)
{
    free(vector);
}

// FIX ME!
void drawHeapTree(elemento heap[], int size, int nLevels)
{    
    int offset = 0;
    //int space = (int)pow(2, nLevels - 1);
    
    int nElements = 1;
    for (int level = 0; level < nLevels; level++) {
        for (int i = offset; i < size && i < (offset + nElements); i++) {
            printf("[(%2.0f, %3d)]", heap[i].chave, heap[i].valor);
        }
        printf("\n");
        
        offset += nElements;
        //space = nElements - 1;
        nElements *= 2;
    }
}

inline void swap(elemento *a, elemento *b) {
    elemento temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(elemento heap[], int size, int i) {
    while (1) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left].chave > heap[largest].chave)
            largest = left;

        if (right < size && heap[right].chave > heap[largest].chave)
            largest = right;

        if (largest != i) {
            swap(&heap[i], &heap[largest]);
            i = largest;
            
        } else {
            break;
        }
    }
}

void heapifyUp(elemento heap[], int *size, int pos) {
    elemento val = heap[pos];
    while (pos > 0 && val.chave > heap[parent(pos)].chave) {
        heap[pos] = heap[parent(pos)];
        pos = parent(pos);
    }
    heap[pos] = val;
}

void insert(elemento heap[], int *size, elemento element) {
    *size += 1;
    int last = *size - 1;
    
    heap[last] = element;
    heapifyUp(heap, size, last);
}

int isMaxHeap(elemento heap[], int size) {
    for (int i = 1; i < size; i++)
        if (heap[i].chave <= heap[parent(i)].chave)
            continue;
        else {
            printf("\nbroke at [%d]=%f\n", i, heap[i].chave);
            printf("father at [%d]=%f\n", parent(i), heap[parent(i)].chave);
            return 0;
        }
    return 1;
}

void decreaseMax(elemento heap[], int size, float new_value) {
    if (size == 0) // Heap is empty
        return;

    if (heap[0].chave > new_value) {
        heap[0].chave = new_value;
        // The drawing function might need modifications if the structure changes affect the visualization.
        #if SHOW_DECREASE_MAX_STEPS 
           drawHeapTree(heap, size, 4);
           printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        #endif
        maxHeapify(heap, size, 0);
    }
}