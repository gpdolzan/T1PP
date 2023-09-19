#include <stdlib.h>
#include "seqv2.h"
#include "input.h"

float* Input;
elemento* InputPair;
elemento* Output;

int main(int argc, char const *argv[])
{
    readInput(argc, argv);
    int nTotalElements = getNTotalElements();
    int k = getK();

    Input = (float*)malloc(nTotalElements * sizeof(float));
    InputPair = (elemento*)malloc(nTotalElements * sizeof(elemento));
    Output = (elemento*)malloc(k * sizeof(elemento));

    for (int i = 0; i < nTotalElements; i++)
    {
        int a = rand();  // Returns a pseudo-random integer
	    int b = rand();  // same as above
        elemento e;
        // Generate numbers from 1 to 100
        e.chave = a * 100.0 + b;
        e.valor = i;

        Input[i] = e.chave;
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