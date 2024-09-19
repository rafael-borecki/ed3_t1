#include "./../../headers/funcionalities.h"
#include "./../../headers/funcoesFornecidas.h"
#include "./../../headers/headerRoutines.h"

#define DEBUG_FUNC1_PRINT 0
#define DEBUG_FUNC1_FILE 1

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
/*int funcionality2(char inputFileName[])
{
    FILE *file_in;
    file_in = fopen(inputFileName, "r");
    if (!file_in)
    {
        printf("Falha no processamento do arquivo\n");
        return EXIT_FAILURE;
    }

    // enquanto der para ler
    Dinosaur dino;
    // read from binary
    // input dino on screen
    //
    return 1;
}
int funcionality3(char inputFileName[], char num[])
{
    int iterations = 1;
    // converter uma string em um int

    char field[MAX_STR_LEN], field_value[MAX_STR_LEN];
    for (int i = 0; i < iterations; i++)
    {
        // lê nome do campo
        // lê valor do campo
        fgets(field, MAX_STR_LEN, stdin);
        fgets(field_value, MAX_STR_LEN, stdin);

        // realiza procura(nome, valor)
        //
        // para cada espécie encontrada{
        // se achou =>
        // se não foi removido => input dino on screen
        //
        // se ja foi removido=>msg de não encontrada
        //
        // se não achou => msg de não encontrada
        // }
    }
    // numero de paginas de disco
    return 1;
}

int funcionality4(char inputFileName[], char num[])
{
    int iterations = 1;
    // converter num para int

    char field[MAX_STR_LEN], field_value[MAX_STR_LEN];
    for (int i = 0; i < iterations; i++)
    {
        fgets(field, MAX_STR_LEN, stdin);
        fgets(field_value, MAX_STR_LEN, stdin);
        // limpa o field_value

        // fazer a busca pelo parametro
        //
        // se encontrar {
        // apaga dinosaur
        // }
    }
    binarioNaTela(inputFileName);
    return 1;
}

int funcionality5(char inputFileName[], char num[])
{
    int iterations = 1;
    // tranformar char em int
    for (int i = 0; i < iterations; i++)
    {
        Dinosaur dino;
        // recebe os parâmetros
        //  insere no arquivo
    }
    binarioNaTela(inputFileName);
    return 1;
}

int funcionality6(char inputFileName[])
{
    // abre o arquivo
    Dinosaur dino1, dino2;
    // compacta
    // fecha o arquivo
    binarioNaTela(inputFileName);
    return 1;
}*/
