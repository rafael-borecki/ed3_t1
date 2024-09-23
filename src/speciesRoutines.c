#include "./../headers/speciesRoutines.h"
#include <stdio.h>
#include <sys/types.h>

#define DEBUG1 0
#define DEBUG2 0
#define DEBUG_CSV 0
#define DEBUG_PRINT 0

void DebugFile(char *filename, Header *head)
{
    FILE *fp;
    fp = fopen(filename, "rb");
    if (!fp)
        return;

    if (DEBUG1)
    {
        fseek(fp, 0, SEEK_END);
        int filelen = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char buffer;

        for (int i = 0; i < filelen; i++)
        {
            fread(&buffer, 1, 1, fp);
            printf("%d ", buffer);
        }
    }

    if (DEBUG2)
    {
        fseek(fp, 1600, SEEK_SET);
        Dinosaur temp;
        for (int i = 0; i < head->nroPagDisco; i++)
        {
            ReadFromFile(&temp, fp);
            printDino(temp);
        }
    }

    fclose(fp);
}

int ReadFromCsv(Dinosaur *temp_dino, FILE *file)
{
    char line[MAX_CSV_LEN + 1];
    if (fgets(line, MAX_CSV_LEN, file) != NULL)
    {
        if (DEBUG_CSV)
        {
            for (int a = 0; a < strlen(line); a++)
                printf("%d ", line[a]);
        }
        char *token;
        char *point = line;
        // nome
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            strcpy(temp_dino->name, "");
        else
            strcpy(temp_dino->name, token);

        // dieta
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            strcpy(temp_dino->diet, "");
        else
            strcpy(temp_dino->diet, token);

        // habitat
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            strcpy(temp_dino->habitat, "");
        else
            strcpy(temp_dino->habitat, token);

        // população
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            temp_dino->population = -1;
        else
            temp_dino->population = atoi(token);

        // tipo
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            strcpy(temp_dino->type, "");
        else
            strcpy(temp_dino->type, token);

        // velocidade
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            temp_dino->velocity = -1;
        else
            temp_dino->velocity = atoi(token);

        // unidade de medida
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            temp_dino->measure_unit = '$';
        else
            temp_dino->measure_unit = *token;

        // tamanho
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            temp_dino->length = -1;
        else
            temp_dino->length = atof(token);

        // espécie
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            strcpy(temp_dino->specie_name, "");
        else
            strcpy(temp_dino->specie_name, token);

        // comida
        token = strsep(&point, "\r");
        if (*token == '\0' || *token == '\n' || *token == 13)
            strcpy(temp_dino->food, "");
        else
            strcpy(temp_dino->food, token);

        // campos vazios
        temp_dino->removed = '0';
        temp_dino->chain = -1;
        return 1;
    }
    return 0;
}

void ReadFromFile(Dinosaur *temp_dino, FILE *file)
{

    // dados fixos
    int readed_bytes = 0;

    fread(&temp_dino->removed, sizeof(char), 1, file);
    if (temp_dino->removed == '1')
    {
        fseek(file, 159, SEEK_CUR);
        return;
    }

    fread(&temp_dino->chain, sizeof(int), 1, file);
    fread(&temp_dino->population, sizeof(int), 1, file);
    fread(&temp_dino->length, sizeof(float), 1, file);
    fread(&temp_dino->measure_unit, sizeof(char), 1, file);
    fread(&temp_dino->velocity, sizeof(int), 1, file);

    readed_bytes += 18;

    // dados variados
    char buffer[161];
    char *pointer_buffer = buffer;
    fread(buffer, sizeof(char), 142, file);

    // printf("%s %ld\n", buffer, strlen(buffer));
    // char temp_buffer[100];
    char *token;
    token = strsep(&pointer_buffer, "#");
    if (*token == '\0' || *token == '\n' || *token == 10)
        strcpy(temp_dino->name, "");
    else
        strcpy(temp_dino->name, token);

    token = strsep(&pointer_buffer, "#");
    if (*token == '\0' || *token == '\n' || *token == 10)
        strcpy(temp_dino->specie_name, "");
    else
        strcpy(temp_dino->specie_name, token);

    token = strsep(&pointer_buffer, "#");
    if (*token == '\0' || *token == '\n' || *token == 10)
        strcpy(temp_dino->habitat, "");
    else
        strcpy(temp_dino->habitat, token);

    token = strsep(&pointer_buffer, "#");
    if (*token == '\0' || *token == '\n' || *token == 10)
        strcpy(temp_dino->type, "");
    else
        strcpy(temp_dino->type, token);
    token = strsep(&pointer_buffer, "#");

    if (*token == '\0' || *token == '\n' || *token == 10)
        strcpy(temp_dino->diet, "");
    else
        strcpy(temp_dino->diet, token);

    token = strsep(&pointer_buffer, "#");
    if (*token == '\0' || *token == '\n' || *token == 10)
        strcpy(temp_dino->food, "");
    else
        strcpy(temp_dino->food, token);
}

void writeDinoFile(Dinosaur *temp_species, FILE *file)
{
    int written_bytes = 0;

    // registros de tamanho fixo
    // tratamento para os casos onde o campo é nulo
    fwrite(&temp_species->removed, sizeof(char), 1, file);
    fwrite(&temp_species->chain, sizeof(int), 1, file);
    fwrite(&temp_species->population, sizeof(int), 1, file);
    fwrite(&temp_species->length, sizeof(float), 1, file);
    fwrite(&temp_species->measure_unit, sizeof(char), 1, file);
    fwrite(&temp_species->velocity, sizeof(int), 1, file);

    // 18 bytes escritos
    written_bytes += 18;

    // registros de tamanho variável
    // se é nulo -> apenas um hashtag
    int temp_length = 0;
    char delimiter = '#';

    /*
     * DA PRA TIRAR OS IF's E ELSES,
     */

    // nome
    temp_length = strlen(temp_species->name);
    if (temp_length == 0)
    {
        fwrite(&delimiter, sizeof(char), 1, file);
        written_bytes += 1;
    }
    else
    {
        fwrite(temp_species->name, sizeof(char), temp_length, file);
        fwrite(&delimiter, sizeof(char), 1, file);
        written_bytes += (temp_length + 1);
    }

    // specie_name
    temp_length = strlen(temp_species->specie_name);
    if (temp_species == 0)
    {
        fwrite(&delimiter, sizeof(char), 1, file);
        written_bytes += 1;
    }
    else
    {
        fwrite(&temp_species->specie_name, sizeof(char), temp_length, file);
        fwrite(&delimiter, sizeof(char), 1, file);
        written_bytes += (temp_length + 1);
    }

    // habitat
    temp_length = strlen(temp_species->habitat);
    if (temp_length == 0)
    {
        fwrite(&delimiter, sizeof(char), 1, file);
        written_bytes += 1;
    }
    else
    {
        fwrite(&temp_species->habitat, sizeof(char), temp_length, file);
        fwrite(&delimiter, sizeof(char), 1, file);
        written_bytes += (temp_length + 1);
    }
    // type
    temp_length = strlen(temp_species->type);
    if (temp_length == 0)
    {
        fwrite(&delimiter, sizeof(char), 1, file);
        written_bytes += 1;
    }
    else
    {
        fwrite(&temp_species->type, sizeof(char), temp_length, file);
        fwrite(&delimiter, sizeof(char), 1, file);
        written_bytes += (temp_length + 1);
    }
    // diet
    temp_length = strlen(temp_species->diet);
    if (temp_length == 0)
    {
        fwrite(&delimiter, sizeof(char), 1, file);
        written_bytes += 1;
    }
    else
    {
        fwrite(&temp_species->diet, sizeof(char), temp_length, file);
        fwrite(&delimiter, sizeof(char), 1, file);
        written_bytes += (temp_length + 1);
    }

    temp_length = strlen(temp_species->food);
    if (temp_length == 0)
    {
        fwrite(&delimiter, sizeof(char), 1, file);
        written_bytes += 1;
    }
    else
    {
        fwrite(&temp_species->food, sizeof(char), temp_length, file);
        fwrite(&delimiter, sizeof(char), 1, file);
        written_bytes += (temp_length + 1);
    }
    // encher com filler
    char filler = '$';
    for (int i = 0; i < MAX_REGISTER_LEN - written_bytes; i++)
        fwrite(&filler, sizeof(char), 1, file);
}

// searchSpecies **Procura no arquivo "filename" algum registro com o mesmo ID passado no argumento
// da
//    função **Se achar um registro com ID igual,
//    retorna 1 * Se não, retorna 0;

int compareDino(char *field, char *value, Dinosaur *temp_dino)
{
    if (!strcmp("populacao", field))
        return (temp_dino->population == atoi(value)) ? 1 : 0;
    if (!strcmp("tamanho", field))
        return (temp_dino->length == atof(value)) ? 1 : 0;
    if (!strcmp("unidadeMedida", field))
        return (temp_dino->measure_unit == value[0]) ? 1 : 0;
    if (!strcmp("velocidade", field))
        return (temp_dino->velocity == atoi(value)) ? 1 : 0;

    // tamanho variável
    if (!strcmp("nome", field))
        return (!strcmp(temp_dino->name, value)) ? 1 : 0;
    if (!strcmp("especie", field))
        return (!strcmp(temp_dino->specie_name, value)) ? 1 : 0;
    if (!strcmp("habitat", field))
        return (!strcmp(temp_dino->habitat, value)) ? 1 : 0;
    if (!strcmp("tipo", field))
        return (!strcmp(temp_dino->type, value)) ? 1 : 0;
    if (!strcmp("dieta", field))
        return (!strcmp(temp_dino->diet, value)) ? 1 : 0;
    if (!strcmp("alimento", field))
        return (!strcmp(temp_dino->food, value)) ? 1 : 0;
    return 0;
}

// FAZER TRATAMENTO PARA CAMPOS NULOS

void printDino(Dinosaur temp_dino)
{
    if (DEBUG_PRINT)
    {
        printf("removed: %c\n", temp_dino.removed);
        printf("chain: %d\n", temp_dino.chain);
    }
    if (strcmp(temp_dino.name, ""))
        printf("Nome: %s\n", temp_dino.name);
    if (strcmp(temp_dino.specie_name, ""))
        printf("Especie: %s\n", temp_dino.specie_name);
    if (strcmp(temp_dino.type, ""))
        printf("Tipo: %s\n", temp_dino.type);
    if (strcmp(temp_dino.diet, ""))
        printf("Dieta: %s\n", temp_dino.diet);
    if (strcmp(temp_dino.habitat, ""))
        printf("Lugar que habitava: %s\n", temp_dino.habitat);
    if (temp_dino.length != -1)
        printf("Tamanho: %.1f m\n", temp_dino.length);
    if (temp_dino.velocity != -1)
        printf("Velocidade: %d %cm/h\n", temp_dino.velocity, temp_dino.measure_unit);
    printf("\n");
    if (DEBUG_PRINT)
    {
        printf("population: %d\n", temp_dino.population);

        printf("food: %s\n\n", temp_dino.food);
    }
}

// baseado no RRN, faz a remoção lógica do registro
int removeDinoRRN(int i, FILE *file, Header *head)
{
    int save = ftell(file);
    fseek(file, 1600, SEEK_SET);
    fseek(file, i * 160, SEEK_CUR);

    // alteração do arquivo binário
    char removed = '1';
    char thrash[155];
    memset(thrash, '$', 155 * sizeof(char));
    fwrite(&removed, sizeof(char), 1, file);
    fwrite(&head->topo, sizeof(int), 1, file);
    fwrite(thrash, sizeof(unsigned char), 155, file);

    // aleteração do header
    head->topo = i;
    head->nroRegRem += 1;

    fseek(file, save, SEEK_SET);
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
*/
void readFromInput(Dinosaur *temp_dino)
{
    char name[MAX_CSV_LEN], diet[MAX_CSV_LEN], habitat[MAX_CSV_LEN], type[MAX_CSV_LEN],
        speciesName[MAX_CSV_LEN], food[MAX_CSV_LEN], velocityMeasure[MIN_STR_LEN],
        population[MIN_STR_LEN], velocity[MIN_STR_LEN], length[MIN_STR_LEN];
    scan_quote_string(name);
    scan_quote_string(diet);
    scan_quote_string(habitat);
    scan_quote_string(population);
    scan_quote_string(type);
    scan_quote_string(velocity);
    scan_quote_string(velocityMeasure);
    scan_quote_string(length);
    scan_quote_string(speciesName);
    scan_quote_string(food);

    temp_dino->removed = '0';
    temp_dino->chain = -1;
    if (!strcmp(population, ""))
        temp_dino->population = -1;
    else
        temp_dino->population = atoi(population);

    if (!strcmp(length, ""))
        temp_dino->length = -1;
    else
        temp_dino->length = atof(length);

    if (!strcmp(velocity, ""))
        temp_dino->velocity = -1;
    else
        temp_dino->velocity = atoi(velocity);

    if (!strcmp(velocityMeasure, ""))
        temp_dino->measure_unit = '$';
    else
        temp_dino->measure_unit = velocityMeasure[0];

    if (!strcmp(name, ""))
        strcpy(temp_dino->name, "");
    else
        strcpy(temp_dino->name, name);

    if (!strcmp(speciesName, ""))
        strcpy(temp_dino->specie_name, "");
    else
        strcpy(temp_dino->specie_name, speciesName);

    if (!strcmp(habitat, ""))
        strcpy(temp_dino->habitat, "");
    else
        strcpy(temp_dino->habitat, habitat);

    if (!strcmp(diet, ""))
        strcpy(temp_dino->diet, "");
    else
        strcpy(temp_dino->diet, diet);

    if (!strcmp(type, ""))
        strcpy(temp_dino->type, "");
    else
        strcpy(temp_dino->type, type);

    if (!strcmp(food, ""))
        strcpy(temp_dino->food, "");
    else
        strcpy(temp_dino->food, food);
}
/*
 reportSpecies (COMANDO 2)
 *
 * Dada uma certa posição do ponteiro file, printa na tela todo
 * o registro da espécie
*/
void writeDinoRRN(int RRN, FILE *file, Dinosaur *temp_dino)
{
    int save = ftell(file);
    fseek(file, 1600 + (RRN * 160), SEEK_SET);
    writeDinoFile(temp_dino, file);

    fseek(file, save, SEEK_SET);
};

int searchNextChain(int RRN, FILE *file, Dinosaur *temp_dino)
{
    int save = ftell(file);
    fseek(file, 1600 + (RRN * 160), SEEK_SET);
    char thrash;
    int proxRRN;
    fread(&thrash, sizeof(char), 1, file);
    fread(&proxRRN, sizeof(int), 1, file);
    fseek(file, save, SEEK_SET);
    return proxRRN;
}

int isDinoRemovedRRN(int RRN, FILE *file)
{
    int save = ftell(file);
    fseek(file, 0, SEEK_END);
    int max = ftell(file);

    if ((1600 + (160 * RRN)) > max)
        return 0;

    fseek(file, 1600 + (160 * RRN), SEEK_SET);
    char thrash;
    fread(&thrash, sizeof(char), 1, file);
    fseek(file, save, SEEK_SET);
    return (thrash == '1') ? 1 : 0;
}

int copyDinoRRN(int i, int j, FILE *file)
{
    int save = ftell(file);
    // ler o j

    fseek(file, 1600 + (160 * j), SEEK_SET);
    char buffer1[161];
    fread(&buffer1, sizeof(char), 160, file);

    char buffer2[161];
    fseek(file, 1600 + (160 * i), SEEK_SET);
    fread(&buffer2, sizeof(char), 160, file);

    fseek(file, 1600 + (160 * j), SEEK_SET);
    fwrite(&buffer2, sizeof(char), 160, file);

    fseek(file, 1600 + (160 * i), SEEK_SET);
    fwrite(&buffer1, sizeof(char), 160, file);

    fseek(file, save, SEEK_SET);
    return 1;
}
