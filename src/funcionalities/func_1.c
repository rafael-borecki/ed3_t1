
#include "./../../headers/func_1.h"
#include "./../../headers/funcoesFornecidas.h"
#include "./../../headers/headerRoutines.h"

#define DEBUG_FUNC1_PRINT 0
#define DEBUG_FUNC1_FILE 0

int funcionality1(char inputFileName[], char outputFileName[])
{
    FILE *file_in, *file_out;
    file_in = fopen(inputFileName, "r");
    file_out = fopen(outputFileName, "wb");
    if (!file_in || !file_out)
    {
        printf("Falha no processamento do arquivo\n");
        return EXIT_FAILURE;
    }

    // inicializa header;
    Header head;
    head.status = '0';
    head.topo = -1;
    head.proxRRN = 0;
    head.nroRegRem = 0;
    head.nroPagDisco = 0;
    head.qttCompacta = 0;

    createHeader(&head, file_out);

    // escrita dos registros
    char lixo[160];
    fgets(lixo, 160, file_in);
    Dinosaur dino;
    int register_num = 0;
    while (1)
    {

        if (ReadFromCsv(&dino, file_in))
        {
            if (DEBUG_FUNC1_PRINT)
                printDino(dino);
            writeDinoFile(&dino, file_out);
            register_num++;
        }
        else
            break;
    }

    // atualiza o header
    head.status = '1';
    head.nroPagDisco = 1 + ((register_num + 9) / 10);
    head.proxRRN = register_num;
    updateHeader(&head, file_out);

    fclose(file_out);
    fclose(file_in);

    if (DEBUG_FUNC1_FILE)
        DebugFile(outputFileName, &head);

    binarioNaTela(outputFileName);

    return 1;
}
