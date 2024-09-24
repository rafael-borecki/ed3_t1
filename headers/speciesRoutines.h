#ifndef __SPECIES_ROUTINES__
#define __SPECIES_ROUTINES__

#include "funcoes_fornecidas.h"
#include "headerRoutines.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTER_LEN 160

#define MAX_CSV_LINE_LEN 200

#define MAX_STR_LEN 100
#define MAX_VALUE_LEN 100
#define MAX_FIELD_LEN 100

#define SMALL_VALUE_LEN 20

typedef struct
{
    // control fields
    char removed;
    int chain;
    // fixed size fields
    int population;
    float length;
    char measure_unit;
    int velocity;
    // variable size fieds
    char name[MAX_VALUE_LEN];
    char specie_name[MAX_VALUE_LEN];
    char habitat[MAX_VALUE_LEN];
    char type[MAX_VALUE_LEN];
    char diet[MAX_VALUE_LEN];
    char food[MAX_VALUE_LEN];
} Dinosaur;

int ReadFromCsv(Dinosaur *temp_dimo, FILE *file);
void printDino(Dinosaur temp_dino);
void ReadFromFile(Dinosaur *temp_dino, FILE *file);
void writeDinoFile(Dinosaur *temp_species, FILE *file);
int compareDino(char *field, char *value, Dinosaur *temp_dino);
int removeDinoRRN(int RRN, FILE *file, Header *head);
void readFromInput(Dinosaur *temp_dino);
void writeDinoRRN(int RRN, FILE *file, Dinosaur *temp_dino);
int searchNextChain(int RRN, FILE *file);
int isDinoRemovedRRN(int RRN, FILE *file);
int swapDinoRRN(int RRN_1, int RRN_2, FILE *file);
#endif
