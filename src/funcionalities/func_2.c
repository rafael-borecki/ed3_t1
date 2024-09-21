#include "../../headers/func_2.h"
#include <stdio.h>

int funcionality2(char inputFileName[])
{

    FILE *file_in;
    file_in = fopen(inputFileName, "rb");
    if (!file_in)
    {
        printf("Falha no processamento do arquivo\n");
        return EXIT_FAILURE;
    }

    // lê o cabeçalho
    Header head;
    if (readHeader(&head, file_in) == 0)
    {
        printf("Registro inexistente.\n");
        return 0;
    };

    // se status = 0, deu ruim
    // se status = 1, deu bom
    if (head.status == '0')
    {
        printf("Falha no processamento do arquivo");
        return 0;
    }
    // loop
    //
    // verifica se está removido ou não
    //
    // printa Dino

    Dinosaur temp_dino;
    for (int i = 0; i < head.proxRRN; i++)
    {
        ReadFromFile(&temp_dino, file_in);
        if (temp_dino.removed == '0')
            printDino(temp_dino);
    }

    fclose(file_in);

    printf("Numero de paginas de disco: %d\n\n", head.nroPagDisco);

    return 1;
}
