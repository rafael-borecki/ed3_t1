#include "./../../headers/func_5.h"

#define DEBUG 0
#define DEBUG1 0

int funcionality5(char inputFileName[], char query_num[])
{
    int n = atoi(query_num);
    for (int i = 1; i <= n; i++)
    {
        // read the informations from input
        Dinosaur temp_dino;
        readFromInput(&temp_dino);

        if (DEBUG)
            printDino(temp_dino);

        // opening file to make modificantions: read and write mode
        FILE *file;
        file = fopen(inputFileName, "rb+");
        if (!file)
        {
            printf("Falha no processamento do arquivo\n");
            return EXIT_FAILURE;
        }

        // read header informations
        Header head;
        if (readHeader(&head, file) == 0)
        {
            printf("Registro inexistente.\n");
            return 0;
        };
        if (head.status == '0')
        {
            printf("Falha no processamento do arquivo");
            return 0;
        }

        // modifying the file
        head.status = '0';

        // insert on the end of file
        if (head.top == -1)
        {
            int RRN = head.nextRRN;
            writeDinoRRN(RRN, file, &temp_dino);
            // update header informations
            head.nextRRN += 1;
            head.diskPageNum = ((head.nextRRN + 9) / 10) + 1;
        }

        // insert on the top of the "removed stack"
        else
        {
            int RRN = head.top;
            head.top = searchNextChain(RRN, file, &temp_dino);
            // updating header informations
            writeDinoRRN(RRN, file, &temp_dino);
            head.remRegNum -= 1;
        }

        // finished modifying the file
        head.status = '1';
        // update header informatons
        updateHeader(&head, file);
        fclose(file);
    }
    binarioNaTela(inputFileName);
    return 1;
}
