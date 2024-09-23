#include "./../../headers/func_6.h"
#include <stdio.h>
#include <unistd.h>

#define DEBUG 0
#define DEBUG1 0
// input1 = arquivo
// input2 = n
// input3 = resto da string de entrada

int funcionality6(char input1[], char input2[], char input3[])
{
    if (DEBUG)
    {
        printf("%s\n", input1);
        int n = atoi(input3);
        printf("%d\n", n);
        printf("%s %ld\n", input3, strlen(input3));
    }

    FILE *file_in;
    file_in = fopen(input2, "rb+");
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
    head.status = '0';

    // dois ponteiros
    int i = 0, j = 0;
    // escrita leitura

    while (j < head.proxRRN)
    {
        if (!isDinoRemovedRRN(j, file_in))
        {
            if (i != j)
                copyDinoRRN(i, j, file_in);
            i++;
        }
        j++;
    }

    // se o rrn i está apagado //isRemoved()

    // seek para i+1 registro
    //  trunca o arquivo

    head.nroPagDisco = 1 + ((i + 9) / 10);
    head.proxRRN = i;
    head.qttCompacta += 1;
    head.status = '1';
    head.topo = -1;
    head.nroRegRem = 0;

    updateHeader(&head, file_in);

    truncate(input2, 1600 + (i * 160));

    fclose(file_in);

    binarioNaTela(input2);

    return 1;
}
