#include "./../headers/headerRoutines.h"
#include <stdio.h>
/* createHeader
 *
 * -> Receive a Header struct (which information will be put on the file) and a FILE pointer (the
 * buffer that it will write on)

 * -> write the information in *head in the file in the following order: "status", "topo",
 * "proxRRN", "nroRegRem", "nroPagDisco", "qttCompacta"

 * ->this function must be called only when you
 * create the output file in the end.

 * ->it will point to the first byte after the disk page
 *
 */
int createHeader(Header *head, FILE *file)
{
    fwrite(&head->status, sizeof(char), 1, file);
    fwrite(&head->top, sizeof(int), 1, file);
    fwrite(&head->nextRRN, sizeof(int), 1, file);
    fwrite(&head->remRegNum, sizeof(int), 1, file);
    fwrite(&head->diskPageNum, sizeof(int), 1, file);
    fwrite(&head->compactNum, sizeof(int), 1, file);

    char aux = '$';
    for (int i = 0; i < 1600 - 21; i++)
        fwrite(&aux, sizeof(char), 1, file);
    return 1;
}
/* updateHeader
 *
 * -> Receive a Header struct (which information will be put on the file) and a FILE pointer (the
 * buffer that it will write on)

 * -> write the information in *head in the file in the following order: "status", "topo",
 * "proxRRN", "nroRegRem", "nroPagDisco", "qttCompacta"

 * ->return the file pointer in the same position where it was when the file was called
 *
 */
int updateHeader(Header *head, FILE *file)
{
    int save = ftell(file);

    fseek(file, 0, SEEK_SET);

    fwrite(&head->status, sizeof(char), 1, file);
    fwrite(&head->top, sizeof(int), 1, file);
    fwrite(&head->nextRRN, sizeof(int), 1, file);
    fwrite(&head->remRegNum, sizeof(int), 1, file);
    fwrite(&head->diskPageNum, sizeof(int), 1, file);
    // non-existing file
    if (fwrite(&head->compactNum, sizeof(int), 1, file) != 1)
        return 0;

    fseek(file, save, SEEK_SET);
    return 1;
}
/* readHeader
 *
 * -> Receive a Header struct (which information will be readed from the file) and a FILE pointer
 * (the buffer that will be readed)

 * -> write the information from the file  in *head following the order: "status", "topo",
 * "proxRRN", "nroRegRem", "nroPagDisco", "qttCompacta"

 * ->return the file pointer in the next byte after the first
 * disk page
 */
int readHeader(Header *head, FILE *file)
{
    fseek(file, 0, SEEK_SET);

    fread(&head->status, sizeof(char), 1, file);
    fread(&head->top, sizeof(int), 1, file);
    fread(&head->nextRRN, sizeof(int), 1, file);
    fread(&head->remRegNum, sizeof(int), 1, file);
    fread(&head->diskPageNum, sizeof(int), 1, file);

    // non existing file
    if (fread(&head->compactNum, sizeof(int), 1, file) != 1)
        return 0;

    fseek(file, 1600 - 21, SEEK_CUR);

    return 1;
}
