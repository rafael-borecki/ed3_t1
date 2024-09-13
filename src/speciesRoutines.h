#ifndef __SPECIES_ROUTINES__
#define __SPECIES_ROUTINES__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializaçao dos macros para a execução do programa
#define DEBUG 1
#define NAME_SIZE 41
#define SCIENTIFIC_SIZE 61
#define STATUS_SIZE 9
#define FILLER '$'

#define MAX_STR_LEN 40

typedef struct
{
    char status;
    int topo;
    int proxRRN;
    int nroRegRem;
    int nroPagDisco;
    int qttCompacta;
} header;

// inicialização da struct Species
typedef struct
{
    // campos de controle
    char removed;
    int chain;
    // campos de tamanho fixo
    int population;
    float length;
    char measure_unit;
    int velocity;
    // tamanho variável
    char name[MAX_STR_LEN];
    char specie_name[MAX_STR_LEN];
    char habitat[MAX_STR_LEN];
    char type[MAX_STR_LEN];
    char diet[MAX_STR_LEN];
    char food[MAX_STR_LEN];
} Dinosaur;

// definição das funções que serão utilizadas no arquivo main.c
void registerSpecies(char *filename);
void reportSpecies(FILE *file);
int searchSpecies(char *filename, int ID);
void searchSpeciesRRN(FILE *file);
void registerInfoSpecies(FILE *file);
int ReadInput(char *command, char string1[], char string2[], char raw_string[]);

#endif
