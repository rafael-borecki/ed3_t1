/* Estrutura de Dados III - SCC0607
 * Prof. Anderson Canale
 *
<<<<<<< HEAD
 * Primeiro exercício prático
 *
 * Alunos:
 * Rafael Borecki Guimarães de Carvalho - 14604271
 * Renan Correia Monteiro Soares - 14605661
 */

#include "../headers/funcionalities.h"
#include "../headers/funcoesFornecidas.h"
#include "../headers/speciesRoutines.h"

int main()
{
    char inputstr[MAX_STR_LEN];
    char command, input1[MAX_STR_LEN], input2[MAX_STR_LEN];

    ReadInput(&command, input1, input2, inputstr);
    setbuf(stdin, NULL);

    switch (command)
    {
    case ('1'): {
        funcionality1(input1, input2);
        break;
    }
    /*
     * Para o caso 2, é aberto arquivo em modo de leitura binário, e é medido
     * o seu comprimento em bytes com ajuda do fseek e ftell. Isso é feito
     * para garantir que a funcao de leitura reportSpecies() não irá ser exe-
     * cutada com redundancia.
     */
    case (2): {
        /*FILE *file = fopen(filename, "rb");
        if (!file)
        {
            printf("Falha no processamento do arquivo");
            return 0;
        }

        fseek(file, 0, SEEK_END);
        long int file_end = ftell(file);
        fseek(file, 0, SEEK_SET);

        while (file_end - ftell(file) > 130) // enquanto houver registro a ser lido
        {
            reportSpecies(file);
        }
        fclose(file);
        break;
    */}
        /*
         * No caso 3, é aberto um arquivo em modo de leitura binária,
         * sobre o qual é realizada uma busca com base no RRN, com o
         * uso da função searchSpecies(), que faz o trabalho efetivo
         * de busca. Caso o RRN extrapole o tamanho do arquivo, a fun-
         * ção retorna um erro.
         */
        case (3): { /*
             FILE *file = fopen(filename, "rb");
             if (!file)
             {
                 printf("Falha no processamento do arquivo");
                 return EXIT_FAILURE;
             }

             searchSpeciesRRN(file);

             fclose(file);
             break;
         */
        }
            /*
             * Por fim, no caso 4, o arquivo binario é aberto em modo
             * de leitura e escrita simultânea.
             * Em seguida, através da função registerInfoSpecies(), o
             * programa registra o input do usuario sobre quais informa-
             * ções ele quer alterar, e verifica se atende as condições
             * estipuladas. Caso atenda, o programa sobrescreve no
             * arquivo os novos dados.
             * Em seguida, é realizado o checksum com a função forneci-
             * da sobre o binário produzido.
             */

        case (4): { /*
             FILE *file = fopen(filename, "rb+");
             if (!file)
             {
                 printf("Falha no processamento do arquivo");
                 return EXIT_FAILURE;
             }
             registerInfoSpecies(file);
             fclose(file);

             file = fopen(filename, "rb");
             if (!file)
             {
                 printf("Falha no processamento do arquivo");
                 return EXIT_FAILURE;
             }
             binarioNaTela(filename);
             fclose(file);
             break;
         */
        }

            return 0;
        }
        return 0;
}
/*
            =======
         * Primeiro Trabalho Prático
         *
         * Alunos:
         * Rafael Borecki Guimarães de Carvalho - 14604271
         * Renan Correia Monteiro Soares 	- 14605661
         *

#include "./funcoesFornecidas.h"
#include "speciesRoutines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

        int main()
        {
            char inputstr[MAX_STR_LEN];
            char command, input1[MAX_STR_LEN], input2[MAX_STR_LEN];

            ReadInput(&command, input1, input2, inputstr);
            setbuf(stdin, NULL);

            switch (command)
            {
            // FUNCIONALIDADE 1:
            // 1 - Realiza a leitura de varios registros a partir de um input .csv.
            // 2 - Os dados lidos são gravados em um arquivo binarío.
            // 3 - Por fim, realiza o checksum com a função fornecida.
            case (1): {
            }

            // FUNCIONALIDADE 2:
            // 1 - Recupera os dados dos registros armazenados em um arquivo de dados.
            // 2 - Exibe os dados na saída padrã́o conforme formatação.
            //	  Ignora registros marcados como logicamente removíveis.
            case (2): {
            }

            case (3): {
            }

            case (4): {
            }

            case (5): {
            }

            case (6): {
            }
            }
            return 0;
>>>>>>> 942a2373ec15be1f6b27e53ce84868d06efdba0e
        }
        */
