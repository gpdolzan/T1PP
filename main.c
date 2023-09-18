#include <stdlib.h>
#include "seqv2.h"
#include "input.h"

elemento* Input;
elemento* Heap;

int cmpfunc (const void * a, const void * b) {
    elemento ea = *(const elemento*) a;
    elemento eb = *(const elemento*) b;
    return (ea.chave > eb.chave) - (ea.chave < eb.chave);
}

int main(int argc, char const *argv[])
{
    readInput(argc, argv);
    int nTotalElements = getNTotalElements();
    int k = getK();

    Input = allocateVector(nTotalElements);
    fillVector(Input, nTotalElements);
    printVector(Input, nTotalElements);

    Heap = allocateVector(k);
    
    for(int i = 0; i < k; i++)
    {
        Heap[i] = Input[i];
    }

    for(int i = 0; i < nTotalElements; i++)
    {
        decreaseMax(Heap, k, Input[i]);
    }

    qsort(Input, nTotalElements, sizeof(elemento), cmpfunc);
    qsort(Heap, k, sizeof(elemento), cmpfunc);

    printVector(Input, nTotalElements);
    printVector(Heap, k);

    //drawHeapTree(Heap, k, 4);

    freeVector(Input);
    freeVector(Heap);

    return 0;
}