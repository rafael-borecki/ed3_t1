/* Estrutura de Dados III - SCC0607
 * Prof. Anderson Canale
 *
 * Primeiro Trabalho Prático
 *
 * Alunos:
 * Rafael Borecki Guimarães de Carvalho - 14604271
 * Renan Correia Monteiro Soares 	- 14605661
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "speciesRoutines.h"
#include "./funcoesFornecidas.h"

int main() {
  char inputstr[MAX_STR_LEN];
  char command, input1[MAX_STR_LEN], input2[MAX_STR_LEN];

  ReadInput(&command, input1, input2, inputstr);
  setbuf(stdin, NULL);

  switch (command) {
    //FUNCIONALIDADE 1: 
    //1 - Realiza a leitura de varios registros a partir de um input .csv.
    //2 - Os dados lidos são gravados em um arquivo binarío. 
    //3 - Por fim, realiza o checksum com a função fornecida.
    case (1): {

	      }

    //FUNCIONALIDADE 2: 
    //1 - Recupera os dados dos registros armazenados em um arquivo de dados.
    //2 - Exibe os dados na saída padrã́o conforme formatação.
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
}
