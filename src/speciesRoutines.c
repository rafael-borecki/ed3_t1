#include "./speciesRoutines.h"
#include "./funcoesFornecidas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
void readSpeciesFile(Species *temp_species, FILE *file)
{
    fread(&temp_species->species_id, sizeof(int), 1, file);
    fread(temp_species->name, sizeof(char), NAME_SIZE, file);
    fread(temp_species->scientific_name, sizeof(char), SCIENTIFIC_SIZE, file);
    fread(&temp_species->population, sizeof(int), 1, file);
    fread(temp_species->status, sizeof(char), STATUS_SIZE, file);
    fread(&temp_species->location, sizeof(float), 2, file);
    fread(&temp_species->human_impact, sizeof(int), 1, file);
}

  writeSpeciesFile
 *
 * Recebe um registro salvo em struct Species e escreve no arquivo (binário) passado pelo ponteiro
 * file.

void writeSpeciesFile(Species *temp_species, FILE *file)
{
    fwrite(&temp_species->species_id, sizeof(int), 1, file);
    fwrite(temp_species->name, NAME_SIZE * sizeof(char), 1, file);
    fwrite(temp_species->scientific_name, SCIENTIFIC_SIZE * sizeof(char), 1, file);
    fwrite(&temp_species->population, sizeof(int), 1, file);
    fwrite(temp_species->status, STATUS_SIZE * sizeof(char), 1, file);
    fwrite(&temp_species->location[0], sizeof(float), 1, file);
    fwrite(&temp_species->location[1], sizeof(float), 1, file);
    fwrite(&temp_species->human_impact, sizeof(int), 1, file);
}

 searchSpecies
 *
 * Procura no arquivo "filename" algum registro com o mesmo ID passado no argumento da função
 *
 * Se achar um registro com ID igual, retorna 1
 * Se não, retorna 0;

int searchSpecies(char *filename, int ID)
{
    // abertura do arquivo para leitura
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long int file_end = ftell(file); // byteoffset do fim do arquivo

    fseek(file, 0, SEEK_SET);
    int temp;

    // determinando o tamanho, em bytes, de um registro
    Species temp_species;
    long long int jump_size = sizeof(temp_species.species_id) + sizeof(temp_species.name) +
                              sizeof(temp_species.scientific_name) +
                              sizeof(temp_species.population) + sizeof(temp_species.status) +
                              sizeof(temp_species.location) + sizeof(temp_species.human_impact);

    while (file_end - ftell(file) > 130) // enquanto houver registro
    {
        fread(&temp, sizeof(int), 1, file); // le os 4 primeiros bytes (1 int)
        if (temp == ID)
        {
            return 1;
        }
        fseek(file, -4, SEEK_CUR);        // retorna 4 bytes
        fseek(file, jump_size, SEEK_CUR); // pula para o próximo registro
    }

    fclose(file);

    return 0;
}
void printSpecies(Species temp_species)
{
    printf("ID: %d\n", temp_species.species_id);
    printf("Nome: %s\n", temp_species.name);
    printf("Nome Científico: %s\n", temp_species.scientific_name);
    if (temp_species.population)
        printf("População: %d\n", temp_species.population);
    else
        printf("População: NULO\n");
    printf("Status: %s\n", temp_species.status);
    printf("Localização: (%.2f, %.2f)\n", temp_species.location[0], temp_species.location[1]);
    if (temp_species.human_impact)
        printf("Impacto Humano: %d\n\n", temp_species.human_impact);
    else
        printf("Impacto Humano: NULO\n\n");
}*/

int ReadInput(char *command, char string1[], char string2[], char raw_string[])
{
    fgets(raw_string, MAX_STR_LEN, stdin);

    // verifica primeiro caractere
    *command = raw_string[0];
    if (*command < '1' || *command > '6')
    {
        printf("Falha no processamento do arquivo\n");
        return 0;
    }

    // verifica segundo caractere
    if (raw_string[1] != ' ')
    {
        printf("Falha no processamento do arquivo");
        return 0;
    }

    // procura o primeiro e segundo <ESPAÇO> ou caractere especial
    int position1;
    int position2;
    int second_input_flag = 0; // indica se tem uma segunda entrada

    // procur o primeiro <ESPAÇO> ou caractere especial
    for (int i = 2; i < MAX_STR_LEN - 2; i++)
    {
        if (raw_string[i] == ' ')
        {
            position1 = i;
            second_input_flag = 1;
            break;
        }
        if (raw_string[i] < 32 || raw_string[i] > 126)
        {
            position1 = i;
            second_input_flag = 0;
            break;
        }
    }

    // procura o segundo <ESPAÇO> ou caractere especial
    for (int i = position1 + 1; i < MAX_STR_LEN; i++)
    {
        if (raw_string[i] == ' ')
        {
            printf("Falha no processamento do arquivo\n");
            return 0;
        }
        if (raw_string[i] < 32 || raw_string[i] > 126)
        {
            position2 = i;
            break;
        }
    }

    if ((*command == '1' && second_input_flag == 0) ||
        (*command == '2' && second_input_flag == 1) ||
        (*command == '3' && second_input_flag == 0) ||
        (*command == '4' && second_input_flag == 0) ||
        (*command == '5' && second_input_flag == 0) || (*command == '6' && second_input_flag == 1))
    {
        printf("Erro no processamento do arquivo\n");
        return 0;
    }

    // copiando as strings para as variaveis
    for (int i = 2; i < position1; i++)
        string1[i - 2] = raw_string[i];
    string1[position1 - 2] = '\0';

    for (int i = position1 + 1; i < position2; i++)
        string2[i - position1 - 1] = raw_string[i];
    string2[position2 - position1 - 1] = '\0';

    if (DEBUG)
        printf("%d %d %c %s %s %ld %ld\n", position1, position2, *command, string1, string2,
               strlen(string1), strlen(string2));

    return 1;
}

/*
 registerSpecies (COMANDO 1)
 *
 * Registra uma espécie a partir do teclado(stdin) no arquivo binário "filename".
 *
 * Antes de adicionar a espécie ao arquivo, verifica se o ID dela é unico.
 * Se não existir, adiciona a espécie normalmente no arquivo "filename".
 * Se existir o ID, não registra a espécie no arquivo e pula para a próxima
 * entrada do teclado.

void registerSpecies(char *filename)
{
    // leitura do stdin
    Species temp_species;
    memset(&temp_species, '$', sizeof(temp_species));

    scanf("%d", &temp_species.species_id);
    readline(temp_species.name);
    readline(temp_species.scientific_name);
    scanf("%d", &temp_species.population);
    readline(temp_species.status);
    scanf("%f %f", &temp_species.location[0], &temp_species.location[1]);
    scanf("%d", &temp_species.human_impact);

    // verifica se o ID da espécie já foi registrado
    if (searchSpecies(filename, temp_species.species_id) == 1)
    {
        printf("Informação já inserida no arquivo\n");
        return;
    }

    // abre o arquivo para inserção
    FILE *file = fopen(filename, "ab");
    if (!file)
    {
        printf("Falha no processamento do arquivo\n");
        return;
    }

    // escreve no arquivo
    writeSpeciesFile(&temp_species, file);

    fclose(file);
}

 reportSpecies (COMANDO 2)
 *
 * Dada uma certa posição do ponteiro file, printa na tela todo
 * o registro da espécie

void reportSpecies(FILE *file)
{
    // leiura do registro no arquivo
    Species temp_species;
    readSpeciesFile(&temp_species, file);

    // mostra na tela
    printSpecies(temp_species);
};

 searchSpeciesRRN (COMANDO 3)
 *
 * Dado um RRN, procura o registro que ocupa o RRN passado.
 *
 * Caso o RRN seja invalido, o procedimento é encerrado.

void searchSpeciesRRN(FILE *file)
{
    Species temp_species;

    int rrn;
    scanf("%d", &rrn);

    long long int jump_size = sizeof(temp_species.species_id) + sizeof(temp_species.name) +
                              sizeof(temp_species.scientific_name) +
                              sizeof(temp_species.population) + sizeof(temp_species.status) +
                              sizeof(temp_species.location) + sizeof(temp_species.human_impact);

    fseek(file, 0, SEEK_END);
    long long int max_jump = ftell(file) / jump_size;
    fseek(file, 0, SEEK_SET);

    if (rrn > max_jump) // RRN inválido
    {
        printf("Espécie não encontrada");
        return;
    }

    if (fseek(file, rrn * jump_size, SEEK_SET) != 0)
    {
        printf("Espécie não encontrada");
        return;
    }

    // lê do arquivo
    readSpeciesFile(&temp_species, file);

    // mostra na tela
    printSpecies(temp_species);
};

 registerInfoSpecies (COMANDO 4)
 *
 *  Pede um ID, o número n de informações a serem modificadas.
 *  Para cada n, lê-se uma instrução e o dado referente

void registerInfoSpecies(FILE *file)
{
    Species temp_species;

    int jump_size = sizeof(temp_species.species_id) + sizeof(temp_species.name) +
                    sizeof(temp_species.scientific_name) + sizeof(temp_species.population) +
                    sizeof(temp_species.status) + sizeof(temp_species.location) +
                    sizeof(temp_species.human_impact);

    // leitura do ID do comando
    int target_id;
    if (DEBUG == 1)
        printf("TARGET_ID: ");
    scanf("%d", &target_id);

    // leitura do ID correspondente
    do
    {
        // lê do arquivo
        readSpeciesFile(&temp_species, file);
    } while (temp_species.species_id != target_id && !feof(file));

    if (DEBUG == 1)
        printf("TEMP_SPECIES_ID: %d", temp_species.species_id);

    if (temp_species.species_id != target_id)
    {
        printf("Espécie não encontrada\n");
        return;
    }

    // lê quantidade de informações
    int ttl_changes;
    if (DEBUG == 1)
        printf("\nTTL_CHANGES: ");
    scanf("%d", &ttl_changes);

    char instruction[20];
    int instruction_cmd;
    int hi = -1, population = -1;
    char status[STATUS_SIZE];
    memset(&status, '$', STATUS_SIZE);

    while (ttl_changes--)
    {
        if (DEBUG == 1)
            printf("INSTRUCTION: ");
        readline(instruction);
        if (strcmp(instruction, "STATUS") == 0)
        {
            instruction_cmd = 1;
        }
        if (strcmp(instruction, "HUMAN IMPACT") == 0)
        {
            instruction_cmd = 2;
        }
        if (strcmp(instruction, "POPULATION") == 0)
        {
            instruction_cmd = 3;
        }
        switch (instruction_cmd)
        {
        case (1): {
            if (strcmp(temp_species.status, "NULO") == 0)
            {
                readline(status);
                if (DEBUG == 1)
                {
                    printf("cur_status: %s\n", temp_species.status);
                    printf("%s", status);
                }
                strcpy(temp_species.status, status);
            }
            else
            {
                if (DEBUG == 1)
                    printf("cur_status: %s\n", temp_species.status);
                printf("Informação já inserida no arquivo\n");
            }
            break;
        }

        case (2): {
            if (DEBUG == 1)
                printf("hi: ");
            if (!temp_species.human_impact)
            {
                scanf("%d", &hi);
            }
            else
            {
                printf("Informação já inserida no arquivo\n");
            }
            break;
        }

        case (3): {
            if (DEBUG == 1)
                printf("population: ");
            if (!temp_species.population)
            {
                scanf("%d", &population);
            }
            else
            {
                printf("Informação já inserida no arquivo\n");
            }
            break;
        }
        }

        // escrita dos dados no arquivo
        int current_pos = ftell(file);
        fseek(file, current_pos - jump_size, SEEK_SET);

        fwrite(&temp_species.species_id, sizeof(int), 1, file);
        fwrite(&temp_species.name, NAME_SIZE * sizeof(char), 1, file);
        fwrite(&temp_species.scientific_name, SCIENTIFIC_SIZE * sizeof(char), 1, file);
        if (population != -1)
        {
            fwrite(&population, sizeof(int), 1, file);
        }
        else
        {
            fwrite(&temp_species.population, sizeof(int), 1, file);
        }
        fwrite(&temp_species.status, STATUS_SIZE * sizeof(char), 1, file);
        fwrite(&temp_species.location[0], sizeof(float), 1, file);
        fwrite(&temp_species.location[1], sizeof(float), 1, file);
        if (hi != -1)
        {
            fwrite(&hi, sizeof(int), 1, file);
        }
        else
        {
            fwrite(&temp_species.human_impact, sizeof(int), 1, file);
        }
    }
};*/
