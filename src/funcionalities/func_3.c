#include "./../../headers/func_3.h"

int funcionality3(char inputFileName[], char query_num[])
{
    // input2 is a string that has the name of the binary file

    // input3 is a string of the amount of times that the funcionality must be called
    int n = atoi(query_num);
    for (int i = 1; i <= n; i++)
    {
        char field[MAX_FIELD_LEN], value[MAX_VALUE_LEN];
        scanf("%s", field);
        scan_quote_string(value);

        // opening file with read mode
        FILE *file;
        file = fopen(inputFileName, "rb");
        if (!file)
        {
            msg_default_error();
            return 0;
        }

        // read the header information
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

        // doing the search by field and value
        // loop through all the file, and compare the information readed by input with the
        // information on register
        printf("Busca %d\n", i);

        int flag = 0; // flag that save if a register was succesfully found by the input information
        Dinosaur temp_dino;
        int i; // count the number of readed registers

        for (i = 0; i < head.nextRRN; i++)
        {
            ReadFromFile(&temp_dino, file);
            if (temp_dino.removed == '0')
            {
                if (compareDino(field, value, &temp_dino))
                {
                    printDino(temp_dino);
                    flag = 1;

                    // verify if the field is "unique"
                    if (!strcmp(field, "nome"))
                        break;
                    if (!strcmp(field, "especie"))
                        break;
                }
            }
        }

        // if no register was found
        if (flag == 0)
        {
            printf("Registro inexistente.\n\n");
        }
        fclose(file);

        int diskPageReaded = 1 + ((i + 9) / 10);

        // printing the number of disk pages
        printf("Numero de paginas de disco: %d\n\n", diskPageReaded);
    }
    return 1;
}
