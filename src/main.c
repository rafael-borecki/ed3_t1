/* Estrutura de Dados III - SCC0607
 * Prof. Anderson Canale
 *
 * Primeiro trabalho prático
 *
 * Alunos:
 * Rafael Borecki Guimarães de Carvalho - 14604271
 * Renan Correia Monteiro Soares - 14605661
 *
 * Porcentagem
 *
 */

#include "../headers/func_1.h"
#include "../headers/func_2.h"
#include "../headers/func_3.h"
#include "../headers/func_4.h"
#include "../headers/func_5.h"
#include "../headers/func_6.h"
#include "../headers/messages.h"
#include "../headers/readInput.h"

int main()
{
    /*
     * input1 = string that has 'command' + \0
     * input2 = second string separated by ' ' or '\n'
     * input3 = third string separated by ' ' or '\n'
     */
    char input1[MAX_STR_LEN], input2[MAX_STR_LEN], input3[MAX_STR_LEN];

    ReadInput(input1, input2, input3);

    switch (input1[0])
    {
    case ('1'):
        // CREATE TABLE funcionality
        funcionality1(input2, input3);
        break;

    case ('2'):
        // SELECT FROM funcionality
        funcionality2(input2);
        break;

    case ('3'):
        // SELECT WHERE funcionality
        funcionality3(input2, input3);
        break;

    case ('4'):
        // REMOVE funcionality
        funcionality4(input2, input3);
        break;

    case ('5'):
        // INSERT INTO funcionality
        funcionality5(input2, input3);
        break;

    case ('6'):
        // COMPACT funcionality
        funcionality6(input3);
        break;

    default:
        msg_non_existent_command();
        break;
    }
    return 0;
}
