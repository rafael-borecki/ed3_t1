#include "./../../headers/func_5.h"

#define DEBUG 0
#define DEBUG1 0
// input1 = arquivo
// input2 = n
// input3 = resto da string de entrada

int funcionality5(char input1[], char input2[], char input3[])
{
    if (DEBUG)
    {
        printf("%s\n", input1);
        int n = atoi(input3);
        printf("%d\n", n);
        printf("%s %ld\n", input3, strlen(input3));
    }

    int n = atoi(input3);
    for (int i = 1; i <= n; i++)
    {

        Dinosaur temp_dino;
        readFromInput(&temp_dino);
        if (DEBUG1)
            printDino(temp_dino);

        /*if (DEBUG1)
        {
            printf("%s %s\n", field, value);
            if (!strcmp("velocidade", field))
                printf("|%d|", atoi(value) == 5200000);
        }*/

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
        // se topo -1 ->
        // adiciona no final
        // atualiza header
        head.status = '0';

        if (head.topo == -1)
        {
            int RRN = head.proxRRN;
            writeDinoRRN(RRN, file_in, &temp_dino);
            head.proxRRN += 1;
            head.nroPagDisco = ((head.proxRRN - 1 + 9) / 10) + 1;
        }

        else
        {
            int RRN = head.topo;
            head.topo = searchNextChain(RRN, file_in, &temp_dino);
            writeDinoRRN(RRN, file_in, &temp_dino);
            head.nroRegRem -= 1;
        }

        head.status = '1';
        updateHeader(&head, file_in);
        fclose(file_in);
    }
    binarioNaTela(input2);
    return 1;
}
