#ifndef __HEADER_ROUTINES__
#define __HEADER_ROUTINES__

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char status;
    int top;
    int nextRRN;
    int remRegNum;
    int diskPageNum;
    int compactNum;
} Header;

int createHeader(Header *head, FILE *file);
int updateHeader(Header *head, FILE *file);
int readHeader(Header *head, FILE *file);

#endif
