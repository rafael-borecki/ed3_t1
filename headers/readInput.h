#ifndef __READ_INPUT__
#define __READ_INPUT__

#include "speciesRoutines.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REGISTER_LEN 160
#define MAX_STR_LEN 300
#define AVR_STR_LEN 100
#define MIN_STR_LEN 20
#define MAX_CSV_LEN 160

int ReadInput(char *command, char string1[], char string2[], char string3[], char raw_string[]);

#endif
