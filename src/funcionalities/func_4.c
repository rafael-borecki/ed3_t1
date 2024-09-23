#include "./../../headers/func_4.h"

#define DEBUG 0
#define DEBUG1 0
// input1 = arquivo
// input2 = n
// input3 = resto da string de entrada

int funcionality4(char input1[], char input2[], char input3[])
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
        char field[MAX_CSV_LEN], value[MAX_CSV_LEN];
        scanf("%s", field);
        scan_quote_string(value);

        if (DEBUG1)
        {
            printf("%s %s\n", field, value);
            if (!strcmp("velocidade", field))
                printf("|%d|", atoi(value) == 5200000);
        }

        FILE *file_in;
        file_in = fopen(input2, "rb");
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

        // printf("%d %ld", head.proxRRN, ftell(file_in));
        //  printf("Busca %d\n", i);
        Dinosaur temp_dino;
        int isRemoved[head.proxRRN];

        for (int j = 0; j < head.proxRRN; j++)
        {
            ReadFromFile(&temp_dino, file_in);
            if (temp_dino.removed == '0')
            {
                if (compareDino(field, value, &temp_dino))
                    isRemoved[j] = 1;
                else
                    isRemoved[j] = 0;
            }
            else
                isRemoved[j] = 0;
        }
        fclose(file_in);

        if (DEBUG1)
        {
            for (int j = 0; j < head.proxRRN; j++)
                if (isRemoved[j])
                    printf("%d ", j);
            printf("\n");
        }

        FILE *file;
        file = fopen(input2, "rb+");
        if (!file)
        {
            printf("Falha no processamento do arquivo\n");
            return EXIT_FAILURE;
        }

        // se status = 0, deu ruim
        // se status = 1, deu bom
        if (head.status == '0')
        {
            printf("Falha no processamento do arquivo");
            return 0;
        }

        head.status = '0';
        // printf("Busca %d\n", i);
        for (int j = 0; j < head.proxRRN; j++)
        {
            if (isRemoved[j])
                removeDinoRRN(j, file, &head);
        }

        head.status = '1';
        updateHeader(&head, file);
        fclose(file);
    }
    binarioNaTela(input2);
    return 1;
}
