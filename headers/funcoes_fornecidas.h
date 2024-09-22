#ifndef __FUNCOES_FORNECIDAS__
#define __FUNCOES_FORNECIDAS__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void scan_quote_string(char *str);

/**
 * Use essa função para comparação no run.codes.
 * Lembre-se de ter fechado (fclose) o arquivo anteriormente.
 *
 * Ela vai abrir de novo para leitura e depois fechar
 * (você não vai perder pontos por isso se usar ela).
 */
void binarioNaTela(char *nomeArquivoBinario);

#endif // __FUNCOES_FORNECIDAS__
