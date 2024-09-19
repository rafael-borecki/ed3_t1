#ifndef __HEADER_ROUTINES__
#define __HEADER_ROUTINES__

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char status;
    int topo;
    int proxRRN;
    int nroRegRem;
    int nroPagDisco;
    int qttCompacta;
} Header;

int createHeader(Header *head, FILE *file);
int updateHeader(Header *head, FILE *file);

#endif
