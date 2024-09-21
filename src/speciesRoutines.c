#include "./../headers/speciesRoutines.h"
#include <stdio.h>
#include <string.h>

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
/*
searchSpecies **Procura no arquivo "filename" algum registro com o mesmo ID passado no argumento da
    função **Se achar um registro com ID igual,
    retorna 1 * Se não, retorna 0;

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
}*/

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

    if (second_input_flag)
    {
        for (int i = position1 + 1; i < position2; i++)
            string2[i - position1 - 1] = raw_string[i];
        string2[position2 - position1 - 1] = '\0';
    }

    if (DEBUG1)
        printf("%d %d %c %d %s %s %ld %ld\n", position1, position2, *command, second_input_flag,
               string1, string2, strlen(string1), strlen(string2));

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
                              sizeof(temp_species.population) + sizeof(temp_species.status)
+ sizeof(temp_species.location) + sizeof(temp_species.human_impact);

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
