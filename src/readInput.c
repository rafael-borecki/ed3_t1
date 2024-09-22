#include "./../headers/readInput.h"

#define DEBUG 0

int ReadInput(char *command, char string1[], char string2[], char string3[], char raw_string[])
{
    scanf("%s", string1);
    switch (string1[0])
    {
    case '1':
        scanf("%s", string2);
        scanf("%s", string3);
        break;
    case '2':
        scanf("%s", string2);
        break;
    case '3':
        scanf("%s", string2);
        scanf("%s", string3);
        break;
    case '4':
        scanf("%s", string2);
        scanf("%s", string3);
        break;
    case '5':
        scanf("%s", string2);
        scanf("%s", string3);
        break;
    case '6':
        scanf("%s", string2);
        break;
    }
    return 1;
}
