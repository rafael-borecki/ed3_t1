#include "./../headers/headerRoutines.h"
#include <stdio.h>

int createHeader(Header *head, FILE *file)
{
    fwrite(&head->status, sizeof(char), 1, file);
    fwrite(&head->topo, sizeof(int), 1, file);
    fwrite(&head->proxRRN, sizeof(int), 1, file);
    fwrite(&head->nroRegRem, sizeof(int), 1, file);
    fwrite(&head->nroPagDisco, sizeof(int), 1, file);
    fwrite(&head->qttCompacta, sizeof(int), 1, file);

    char aux = '$';
    for (int i = 0; i < 1600 - 21; i++)
        fwrite(&aux, sizeof(char), 1, file);
    return 1;
}

int updateHeader(Header *head, FILE *file)
{
    int entrada = ftell(file);

    fseek(file, 0, SEEK_SET);

    fwrite(&head->status, sizeof(char), 1, file);
    fwrite(&head->topo, sizeof(int), 1, file);
    fwrite(&head->proxRRN, sizeof(int), 1, file);
    fwrite(&head->nroRegRem, sizeof(int), 1, file);
    fwrite(&head->nroPagDisco, sizeof(int), 1, file);
    fwrite(&head->qttCompacta, sizeof(int), 1, file);

    fseek(file, entrada, SEEK_SET);
    return 1;
}

int readHeader(Header *head, FILE *file)
{
    fseek(file, 0, SEEK_SET);

    fread(&head->status, sizeof(char), 1, file);
    fread(&head->topo, sizeof(int), 1, file);
    fread(&head->proxRRN, sizeof(int), 1, file);
    fread(&head->nroRegRem, sizeof(int), 1, file);
    fread(&head->nroPagDisco, sizeof(int), 1, file);

    if (fread(&head->qttCompacta, sizeof(int), 1, file) != 1) // arquivo inexistente
        return 0;

    fseek(file, 1600 - 21, SEEK_CUR);

    return 1;
}
