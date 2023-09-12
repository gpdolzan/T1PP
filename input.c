#include "input.h"

int nTotalElements, k, nThreads;

void readInput(int argc, char const *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <nTotalElements> <k> <nThreads>\n", argv[0]);
        exit(1);
    }

    nTotalElements = atoi(argv[1]);
    k = atoi(argv[2]);
    nThreads = atoi(argv[3]);

    if(nTotalElements < 1)
    {
        printf("nTotalElements must be greater than 0\n");
        exit(1);
    }

    if(k > nTotalElements || k < 1)
    {
        printf("k must be greater than 0 and less or equal than nTotalElements\n");
        exit(1);
    }

    if(nThreads > 8 || nThreads < 1)
    {
        printf("nThreads must be greater than 0 but less or equal to 8\n");
        exit(1);
    }
}

void printInput()
{
    printf("nTotalElements: %d\n", nTotalElements);
    printf("k: %d\n", k);
    printf("nThreads: %d\n", nThreads);
}

int getNTotalElements()
{
    return nTotalElements;
}

int getK()
{
    return k;
}

int getNThreads()
{
    return nThreads;
}