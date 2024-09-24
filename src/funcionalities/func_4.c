#include "./../../headers/func_4.h"

#define DEBUG 0
#define DEBUG1 0

int funcionality4(char inputFileName[], char query_num[])
{
    // input2 is a string that has the name of the binary file

    // input3 is a string of the amount of times that the funcionality must be called
    // similar to the funcionality3, instead of print the register on screen, remove it logically on
    // the file
    int n = atoi(query_num);
    for (int i = 1; i <= n; i++)
    {
        char field[MAX_FIELD_LEN], value[MAX_VALUE_LEN];
        scanf("%s", field);
        scan_quote_string(value);

        if (DEBUG1)
            printf("%s %s\n", field, value);

        // opening file with read mode
        FILE *file;
        file = fopen(inputFileName, "rb+");
        if (!file)
        {
            printf("Falha no processamento do arquivo\n");
            return EXIT_FAILURE;
        }

        // reading header information
        Header head;
        if (readHeader(&head, file) == 0)
        {
            printf("Registro inexistente.\n");
            return 0;
        };
        if (head.status == '0')
        {
            printf("Falha no processamento do arquivo\n");
            return 0;
        }

        // loop through file in the same way as funcionality 3, but instead of printing it on
        // screen, remove the register
        Dinosaur temp_dino;
        for (int j = 0; j < head.nextRRN; j++)
        {
            ReadFromFile(&temp_dino, file);
            if (temp_dino.removed == '0') // posible remove
            {
                if (compareDino(field, value, &temp_dino)) // if
                {
                    removeDinoRRN(j, file, &head);
                }
            }
        }

        // finish modifying
        head.status = '1';
        // update header informations
        updateHeader(&head, file);
        fclose(file);
    }
    binarioNaTela(inputFileName);
    return 1;
}
