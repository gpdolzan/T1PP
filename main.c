#include "seqv2.h"
#include "input.h"

elemento* Input;

int main(int argc, char const *argv[])
{
    readInput(argc, argv);
    int nTotalElements = getNTotalElements();

    Input = allocateVector(nTotalElements);
    fillVector(Input, nTotalElements);
    freeVector(Input);

    return 0;
}