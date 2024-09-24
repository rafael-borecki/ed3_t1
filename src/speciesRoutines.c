#include "./../headers/speciesRoutines.h"

#define DEBUG_CSV 0
#define DEBUG_PRINT 0

/* ReadFomCsv
 * read one file from a .csv file and put its content into a struct Dinosaur passed by reference
 *
 * Makes NULL exception threatment when necessary
 *
 */
int ReadFromCsv(Dinosaur *temp_dino, FILE *file)
{
    char line[MAX_CSV_LINE_LEN + 1];
    if (fgets(line, MAX_CSV_LINE_LEN, file) != NULL)
    {
        if (DEBUG_CSV)
        {
            for (int a = 0; a < strlen(line); a++)
                printf("%d ", line[a]);
        }
        char *token;
        char *point = line;

        // name
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            strcpy(temp_dino->name, "");
        else
            strcpy(temp_dino->name, token);

        // diet
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

        // population
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            temp_dino->population = -1;
        else
            temp_dino->population = atoi(token);

        // type
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            strcpy(temp_dino->type, "");
        else
            strcpy(temp_dino->type, token);

        // velocity
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            temp_dino->velocity = -1;
        else
            temp_dino->velocity = atoi(token);

        // measure unit
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            temp_dino->measure_unit = '$';
        else
            temp_dino->measure_unit = *token;

        // length
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            temp_dino->length = -1;
        else
            temp_dino->length = atof(token);

        // species_name
        token = strsep(&point, ",");
        if (*token == '\0' || *token == '\n' || *token == 10)
            strcpy(temp_dino->specie_name, "");
        else
            strcpy(temp_dino->specie_name, token);

        // food
        token = strsep(&point, "\r");
        if (*token == '\0' || *token == '\n' || *token == 13)
            strcpy(temp_dino->food, "");
        else
            strcpy(temp_dino->food, token);

        // control fields initialization
        temp_dino->removed = '0';
        temp_dino->chain = -1;
        return 1;
    }
    // cannot read new lines
    return 0;
}
/* ReadFromFile
 *
 * Read the next 160 bytes from where the file is appointed and put its information inside the
 * struct Dinosaur passed by reference
 */
void ReadFromFile(Dinosaur *temp_dino, FILE *file)
{
    // count the amount of readed bytes
    int readed_bytes = 0;

    // reading fixed length fields
    fread(&temp_dino->removed, sizeof(char), 1, file);

    // if the register is removed, there is no need to continue reading the register
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

    // reading variable length fields
    char buffer[161]; // temporary buffer
    fread(buffer, sizeof(char), 142, file);

    char *pointer_buffer = buffer; // temporary variables
    char *token;                   // to use strsep()

    // name
    token = strsep(&pointer_buffer, "#");
    if (*token == '\0' || *token == '\n' || *token == 10)
        strcpy(temp_dino->name, "");
    else
        strcpy(temp_dino->name, token);

    // specie_name
    token = strsep(&pointer_buffer, "#");
    if (*token == '\0' || *token == '\n' || *token == 10)
        strcpy(temp_dino->specie_name, "");
    else
        strcpy(temp_dino->specie_name, token);

    // habitat
    token = strsep(&pointer_buffer, "#");
    if (*token == '\0' || *token == '\n' || *token == 10)
        strcpy(temp_dino->habitat, "");
    else
        strcpy(temp_dino->habitat, token);

    // type
    token = strsep(&pointer_buffer, "#");
    if (*token == '\0' || *token == '\n' || *token == 10)
        strcpy(temp_dino->type, "");
    else
        strcpy(temp_dino->type, token);
    token = strsep(&pointer_buffer, "#");

    // diet
    if (*token == '\0' || *token == '\n' || *token == 10)
        strcpy(temp_dino->diet, "");
    else
        strcpy(temp_dino->diet, token);

    // food
    token = strsep(&pointer_buffer, "#");
    if (*token == '\0' || *token == '\n' || *token == 10)
        strcpy(temp_dino->food, "");
    else
        strcpy(temp_dino->food, token);
}

/* WriteDinoFile
 *
 * write the information inside a struct Dinosar into the binary file following the instructions
 * passed
 *
 * Write exactly one register (160 bytes)
 */

void writeDinoFile(Dinosaur *temp_species, FILE *file)
{
    int written_bytes = 0;

    // writing fixed length fields
    fwrite(&temp_species->removed, sizeof(char), 1, file);
    fwrite(&temp_species->chain, sizeof(int), 1, file);
    fwrite(&temp_species->population, sizeof(int), 1, file);
    fwrite(&temp_species->length, sizeof(float), 1, file);
    fwrite(&temp_species->measure_unit, sizeof(char), 1, file);
    fwrite(&temp_species->velocity, sizeof(int), 1, file);

    written_bytes += 18;

    // writing fixed length fields
    int temp_length = 0;
    char delimiter = '#';

    // name
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

    // species_name
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

    // food
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

    // fill with the "filler character"
    char filler = '$';
    for (int i = 0; i < REGISTER_LEN - written_bytes; i++)
        fwrite(&filler, sizeof(char), 1, file);
}
/* compareDino
 *
 * receive two strings and one struct Dinosaur
 *
 * compare the field's value passed by strings with the field's value passed by struct
 *
 * if they are equal, return 1
 * if not, return 0
 *
 */
int compareDino(char *field, char *value, Dinosaur *temp_dino)
{
    // first compare the fields
    // then, compare the values

    if (!strcmp("populacao", field))
        return (temp_dino->population == atoi(value)) ? 1 : 0;
    if (!strcmp("tamanho", field))
        return (temp_dino->length == atof(value)) ? 1 : 0;
    if (!strcmp("unidadeMedida", field))
        return (temp_dino->measure_unit == value[0]) ? 1 : 0;
    if (!strcmp("velocidade", field))
        return (temp_dino->velocity == atoi(value)) ? 1 : 0;

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
/* printDino
 *
 * print the informations passed on a struct Dinosaur
 *
 * Has NULL exception threatment
 *
 */
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
/* remove DinoRRN
 *
 * remove logically the register in the RRN passed on the function, it includes changing its control
 * filds: "removed" and "chain" following the instructions passed
 *
 * Update the header
 *
 * Before finishing the function, returns the pointer to the point it was before the modifications
 *
 */
int removeDinoRRN(int RRN, FILE *file, Header *head)
{
    // save position
    int save = ftell(file);

    fseek(file, 1600 + (RRN * 160), SEEK_SET);

    // modify the register
    head->status = '0';
    char removed = '1';
    char thrash[155];
    memset(thrash, '$', 155 * sizeof(char));
    fwrite(&removed, sizeof(char), 1, file);
    fwrite(&head->top, sizeof(int), 1, file);
    fwrite(thrash, sizeof(unsigned char), 155, file);

    // modify the header information
    head->status = '1';
    head->top = RRN;
    head->remRegNum += 1;

    // return to the position it was at the beginning
    fseek(file, save, SEEK_SET);
    return 1;
}
/* ReadFromInput
 *
 * Read informations passed on input by the user and register it on a struct passed by reference
 *
 */
void readFromInput(Dinosaur *temp_dino)
{
    // reading information
    char name[MAX_VALUE_LEN], diet[MAX_VALUE_LEN], habitat[MAX_VALUE_LEN], type[MAX_VALUE_LEN],
        speciesName[MAX_VALUE_LEN], food[MAX_VALUE_LEN], velocityMeasure[SMALL_VALUE_LEN],
        population[SMALL_VALUE_LEN], velocity[SMALL_VALUE_LEN], length[SMALL_VALUE_LEN];
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

    // initializing control fields
    temp_dino->removed = '0';
    temp_dino->chain = -1;

    // NULL threatment
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
/* writeDinoRRN
 *
 * write a register (160 bytes) containing the informations passed by the Dinosaur struct
 *
 * after the operation, the file pointer "comes back" to the position it was before the operation
 *
 */
void writeDinoRRN(int RRN, FILE *file, Dinosaur *temp_dino)
{
    // save position
    int save = ftell(file);

    fseek(file, 1600 + (RRN * 160), SEEK_SET);
    writeDinoFile(temp_dino, file);

    fseek(file, save, SEEK_SET);
};
/* searchNextChain
 *
 * Return the field "field" from a register at the RRN passed
 *
 * Dont change the position of the FILE pointer passed
 *
 */
int searchNextChain(int RRN, FILE *file)
{
    // save position
    int save = ftell(file);
    fseek(file, 1600 + (RRN * 160), SEEK_SET);

    // read informations
    char thrash;
    int proxRRN;
    fread(&thrash, sizeof(char), 1, file);
    fread(&proxRRN, sizeof(int), 1, file);

    // return the position
    fseek(file, save, SEEK_SET);
    return proxRRN;
}

/* isDinoRemovedRRN
 *
 * based on RRN, checks if the register at this RRN is removed or not
 *
 * if removed, return 1
 * else, return 0
 */
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
/* swapDinoRRN
 *
 * swap the bytes of 2 registers passed based on their RRN
 *
 * Dont change the FILE pointer position after the funcion is ended
 *
 */
int swapDinoRRN(int RRN_1, int RRN_2, FILE *file)
{
    // save position
    int save = ftell(file);

    // changing bytes
    char buffer1[161];
    fseek(file, 1600 + (160 * RRN_1), SEEK_SET);
    fread(&buffer1, sizeof(char), 160, file);

    char buffer2[161];
    fseek(file, 1600 + (160 * RRN_2), SEEK_SET);
    fread(&buffer2, sizeof(char), 160, file);

    fseek(file, 1600 + (160 * RRN_2), SEEK_SET);
    fwrite(&buffer2, sizeof(char), 160, file);

    fseek(file, 1600 + (160 * RRN_1), SEEK_SET);
    fwrite(&buffer1, sizeof(char), 160, file);

    // return position
    fseek(file, save, SEEK_SET);
    return 1;
}
