#include "funcoesFornecidas.h"
#include "speciesRoutines.h"
#include <stdio.h>
#include <stdlib.h>

int funcionality2(char inputFileName[])
{
    FILE *file_in;
    file_in = fopen(inputFileName, "r");
    if (!file_in)
    {
        printf("Falha no processamento do arquivo\n");
        return EXIT_FAILURE;
    }

    // enquanto der para ler
    Dinosaur dino;
    // read from binary
    // input dino on screen
    //
    return 1;
}

