#include "../../headers/func_2.h"
#include <stdlib.h>

int funcionality2(char inputFileName[])
{
    // opening file for read
    FILE *file;
    file = fopen(inputFileName, "rb");
    if (!file)
    {
        msg_default_error();
        return 0;
    }

    // read header informations and save it on "head"
    Header head;
    if (readHeader(&head, file) == 0)
    {
        msg_no_registers();
        return 0;
    };

    if (head.status == '0')
    {
        msg_default_error();
        return 0;
    }

    // Loop through binary file
    Dinosaur temp_dino;
    for (int i = 0; i < head.nextRRN; i++)
    {
        ReadFromFile(&temp_dino, file);
        if (temp_dino.removed == '0')
            printDino(temp_dino);
    }

    fclose(file);

    printf("Numero de paginas de disco: %d\n\n", head.diskPageNum);

    return 1;
}
