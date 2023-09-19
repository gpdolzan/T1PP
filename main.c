#include <stdlib.h>
#include "seqv2.h"
#include "input.h"

float* Input;
pair_t* InputPair;
pair_t* Output;

int main(int argc, char const *argv[])
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
        // Generate numbers from 1 to 100
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
}