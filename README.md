# Trabalho 1 - ED3

## Tasklist
[] Descricao geral do trabalho \
[] Estruturacao das funcoes principais \
[] Funcionalidade 1 \
[] Funcionalidade 2 \
[] Funcionalidade 3 \
[] Funcionalidade 4 \
[] Funcionalidade 5 \
[] Funcionalidade 6 \
[] Documentacao do codigo \
[] Gravacao do video final 

## Objetivo

**Descrição Geral** Implementar um programa em C que lê, gera e manipula dados em arquivos binários, simulando um SQL.

### Funcionalidades

1 - Permita a leitura de vários registros obtidos a partir de um arquivo de entrada em CSV e a gravação desses registros em um binário de saída. Por fim, fazer o checksum do binário para verificar a resposta.
    EX: 1 source.csv output.bin

2 - Leitura de um arquivo binário, em caso de sucesso imprime o conteúdo completo do arquivo. Caso não exista imprime que não existe. Caso foi logicamente removido, imprime que não existe. Caso deu erro, imprime erro.
    EX: 2 entrada.bin

3 - Leitura de um arquivo binário com n filtros, em caso de sucesso imprime a query realizada. 
    EX: 3 entrada.bin <query> <n>
        <CampoFiltro1> <NomeFiltro1> ... <CampoFiltroN> <NomeFiltroN>

4 - Remoção lógica de um registro. No final faz o checksum do binário.
    EX: 4 entrada.bin <n>
        <CampoFiltro1> <NomeFiltro1> ... <CampoFiltroN> <NomeFiltroN>
5 - Inserção de novos registros. No final faz o checksum do binário.
    EX: 5 entrada.bin <n>
        <campo_1>, <campo_2> .. <campo_m> // linha 1
        ...
        <campo_1>, <campo_2> .. <campo_m> // linha n

6 - Remocao dos arquivos logicamente removidos do binário. No final, checksum do binário.
    EX: 6 entrada.bin

## Dataset
[Jurassic-park kaggle](./dataset/data.csv)

1. Name - the name of the dinosaur
2. Diet - the diet of the dinosaur (herbivorous, carnivorous, or omnivorous)
3. Period - the period in which the dinosaur existed (name of the period and years ago)
4. Lived_in - the area which the dinosaur lived in
5. Type - the type of the dinosaur
6. Length - the length of the dinosaur
7. Taxonomy - the taxonomy of the dinosaur
8. Named_by - the people who named this dinosaur
9. Species - the species the dinosaur belongs to
10. Link - the website containing the information of the dinosaur

## Descrição de páginas de disco

No trabalho será usado o conceito de páginas de disco. Cada página de disco tem o tamanho fixo de 1600 bytes. O tamanho da página de disco adotado neste trabalho é lógico, sendo adaptado de acordo com os registros de dados do trabalho.

## Descrição do Arquivo de Dados cadeiaAlimentar
