#include "./../../headers/func_6.h"

int funcionality6(char inputFileName[])
{
    // open file in "insert" mode: read and write mode
    FILE *file;
    file = fopen(inputFileName, "rb+");
    if (!file)
    {
        msg_default_error();
        return 0;
    }

    // read header informations
    Header head;
    if (readHeader(&head, file) == 0)
    {
        msg_no_registers();
        return 0;
    }
    if (head.status == '0')
    {
        msg_default_error();
        return 0;
    }

    head.status = '0';

    // two pointers technique
    //  i is "write" and j is "read"
    int i = 0, j = 0;
    while (j < head.nextRRN) // j passes through all registers
    {
        if (isDinoRemovedRRN(j, file) == 0) // if not removed
        {
            if (i != j)
                swapDinoRRN(i, j, file); // swap register content
            i++;
        }
        j++;
    }

    // update header information
    head.diskPageNum = 1 + ((i + 9) / 10);
    head.nextRRN = i;
    head.compactNum += 1;
    head.status = '1';
    head.top = -1;
    head.remRegNum = 0;
    updateHeader(&head, file);

    // truncate the file in the "nextRRN" position
    truncate(inputFileName, DISK_PAGE_LEN + (i * REGISTER_LEN));

    fclose(file);

    binarioNaTela(inputFileName);

    return 1;
}
