#include "./../../headers/func_1.h"

int funcionality1(char inputFileName[], char outputFileName[])
{
    // opening files
    // read from .csv (inputFileName) and write on .bin(outputFileName)
    FILE *file_in, *file_out;
    file_in = fopen(inputFileName, "r");
    file_out = fopen(outputFileName, "wb");
    if (!file_in || !file_out)
    {
        msg_default_error();
        return EXIT_FAILURE;
    }

    // initialize and write header on outputFileName
    Header head;
    head.status = '0';
    head.top = -1;
    head.nextRRN = 0;
    head.remRegNum = 0;
    head.diskPageNum = 0;
    head.compactNum = 0;
    createHeader(&head, file_out);

    // Loop through all the lines inputFileName, save the information of each line at struct
    // Dinosaur and write it on outputFileName
    char thrash[MAX_CSV_LINE_LEN + 1];
    fgets(thrash, MAX_CSV_LINE_LEN, file_in); // reading first line of .csv
    Dinosaur dino;
    int register_num = 0;
    while (1)
    {
        // if a register was readed, then write it on binary file
        if (ReadFromCsv(&dino, file_in))
        {
            writeDinoFile(&dino, file_out);
            register_num++;
        }
        else
            break;
    }

    // update the header with the correct information
    head.status = '1';
    head.diskPageNum = 1 + ((register_num + 9) / 10);
    head.nextRRN = register_num;
    updateHeader(&head, file_out);

    fclose(file_out);
    fclose(file_in);

    binarioNaTela(outputFileName);

    return 1;
}
