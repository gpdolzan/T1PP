#include <stdlib.h>
#include "seqv2.h"
#include "input.h"

float* Input;
pair_t* InputPair;
pair_t* Output;

/*int main(int argc, char const *argv[])
{
    readInput(argc, argv);
    int nTotalElements = getNTotalElements();
    int k = getK();

    Input = (float*)malloc(nTotalElements * sizeof(float));
    InputPair = (pair_t*)malloc(nTotalElements * sizeof(pair_t));
    Output = (pair_t*)malloc(k * sizeof(pair_t));

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
    
    for(int i = 0; i < k; i++)
    {
        Output[i] = InputPair[i];
    }

    for(int i = 0; i < nTotalElements; i++)
    {
        decreaseMax(Output, k, InputPair[i]);
    }

    verifyOutput(Input, Output, nTotalElements, k);

    free(Input);
    free(InputPair);
    free(Output);

    return 0;
}*/

void printThreadInfo(void* ptr)
{
    // Now convert int* to int
    int threadId = *(int*)ptr;

    printf("This thread will process %d elements\n", threadId);
}

int main(int argc, char const *argv[])
{
    readInput(argc, argv);

    // Calculate size of new vectors dividing nTotal / nThreads
    // If number is not divisible, add 1 to the first thread
    int nTotalElements = getNTotalElements();
    //int k = getK();
    int nThreads = getNThreads();

    Input = (float*)malloc(nTotalElements * sizeof(float));
    InputPair = (pair_t*)malloc(nTotalElements * sizeof(pair_t));

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

    // Create an int vector representing the number of elements each thread will process
    int* nElements = (int*)malloc(nThreads * sizeof(int));
    // Check if number is divisible
    if(nTotalElements % nThreads == 0)
    {
        for(int i = 0; i < nThreads; i++)
        {
            nElements[i] = nTotalElements / nThreads;
        }
    }
    else
    {
        for(int i = 0; i < nThreads; i++)
        {
            nElements[i] = nTotalElements / nThreads;
        }
        // Place in the first thread the remaining elements
        nElements[0] += nTotalElements % nThreads;
    }

    // Loop through InputPair and create a new vector for each thread
    // Each thread will have a vector of pairs
    pair_t** InputPairThread = (pair_t**)malloc(nThreads * sizeof(pair_t*));
    
    for(int i = 0; i < nThreads; i++)
    {
        InputPairThread[i] = (pair_t*)malloc(nElements[i] * sizeof(pair_t));
        // Do a for loop to copy the elements from InputPair to InputPairThread
        for(int j = 0; j < nElements[i]; j++)
        {
            InputPairThread[i][j] = InputPair[j];
        }
    }

    return 0;
}
