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

#define MAX_REGISTER_LEN 160

#define MAX_STR_LEN 300
#define AVR_STR_LEN 100
#define MIN_STR_LEN 20

#define MAX_CSV_LEN 160

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
    int population;    // não tem //nulo -1
    float length;      // tem
    char measure_unit; // não tem //nulo -1
    int velocity;      // não tem //nulo -1
    // tamanho variável
    char name[MAX_CSV_LEN];        // tem
    char specie_name[MAX_CSV_LEN]; // tem
    char habitat[AVR_STR_LEN];     // tem
    char type[AVR_STR_LEN];        // tem
    char diet[MIN_STR_LEN];        // tem
    char food[MIN_STR_LEN];        // não tem //preenche com $
} Dinosaur;

// definição das funções que serão utilizadas no arquivo main.c
void registerSpecies(char *filename);
void reportSpecies(FILE *file);
int searchSpecies(char *filename, int ID);
void searchSpeciesRRN(FILE *file);
void registerInfoSpecies(FILE *file);
int ReadInput(char *command, char string1[], char string2[], char raw_string[]);

int ReadFromCsv(Dinosaur *temp_dimo, FILE *file);
void printDino(Dinosaur temp_dino);
void ReadFromFile(Dinosaur *temp_dino, FILE *file);
void writeDinoFile(Dinosaur *temp_species, FILE *file);
#endif
