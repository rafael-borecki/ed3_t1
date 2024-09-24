#include "./../headers/readInput.h"

/* ReadInput
 * Read more inputs depending on the command passed on string1
 *
 * read one more string
 * cases 2 and 6
 * read two more strings
 * cases 1, 3, 4 and 5
 */
void ReadInput(char string1[], char string2[], char string3[])
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
}
