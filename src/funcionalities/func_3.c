#include "./../../headers/func_3.h"

#define DEBUG 0
// input1 = arquivo
// input2 = n
// input3 = resto da string de entrada

int funcionality3(char input1[], char input2[], char input3[])
{
    if (DEBUG)
    {
        printf("%s\n", input1);
        int n = atoi(input3);
        printf("%d\n", n);
        printf("%s %ld\n", input3, strlen(input3));
    }

    // input3[strlen(input3)] = '\0';
    // input3[strlen(input3) - 1] = ' ';

    // char *ptr = input3;
    // char *token;
    int n = atoi(input3);
    for (int i = 1; i <= n; i++)
    {
        char field[MAX_CSV_LEN], value[MAX_CSV_LEN];
        /*token = strsep(&ptr, " \n\r");
        // printf("%s %ld\n", token, strlen(token));
        strcpy(field, token);

        token = strsep(&ptr, " \n\r");
        // printf("%s %ld\n", token, strlen(token));
        strcpy(value,scan_quote_string(char *str))*/

        scanf("%s", field);
        scan_quote_string(value);

        if (DEBUG)
            printf("%s %s\n", field, value);

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

        printf("Busca %d\n", i);
        int flag = 0;
        Dinosaur temp_dino;
        for (int i = 0; i < head.proxRRN; i++)
        {
            ReadFromFile(&temp_dino, file_in);
            if (temp_dino.removed == '0')
            {
                if (compareDino(field, value, &temp_dino))
                {
                    printDino(temp_dino);
                    flag = 1;
                }
            }
        }

        if (flag == 0)
        {
            printf("Registro inexistente.\n\n");
        }
        fclose(file_in);

        printf("Numero de paginas de disco: %d\n\n", head.nroPagDisco);

        // printf("%s %s\n", field, value);

        // realiza query
    }
    return 1;
}
