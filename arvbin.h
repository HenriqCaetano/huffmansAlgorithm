#ifndef ARVBIN_H
#define ARVBIN_H

typedef struct arvbin Arvbin;

#include "caractere.h"
#include "bitmap.h"

/*
Pré-condição: nenhuma
Pós-condição: árvore criada, vazia
*/
Arvbin* Arvbin_criavazia (void);

/*
Pré-condição: o caractere existe
Pós-condição: Caractere inserido apropriadamente na árvore
*/
Arvbin* Arvbin_insere(Arvbin* a, Caractere* ch);

/*
Dadas duas árvores, a árvore b será alocada na esquerda ou na direita
dependendo do numero de frequencia do seu caractere
Pré-condição: a árvore b existe
Pós-condição: união das duas árvores
*/
Arvbin* Arvbin_insere_arvbin(Arvbin* a, Arvbin* b);

/*
Pré-condição: o caractere existe
Pós-condição: Caractere inserido no ramo da esquerda da árvore
*/
Arvbin* Arvbin_insere_esq(Arvbin* a, Caractere* ch);

/*
Pré-condição: o caractere existe
Pós-condição: Caractere inserido no ramo da direita da árvore
*/
Arvbin* Arvbin_insere_dir(Arvbin* a, Caractere* ch);

/*
Insere a árvore b na esquerda da árvore a
Pré-condição: as duas árvores existem
Pós-condição: árvore b inserida no ramo da esquerda da árvore a
*/
Arvbin* Arvbin_insere_arv_esq(Arvbin* a, Arvbin* b);

/*
Insere a árvore b na direita da árvore a
Pré-condição: as duas árvores existem
Pós-condição: árvore b inserida no ramo da direita da árvore a
*/
Arvbin* Arvbin_insere_arv_dir(Arvbin* a, Arvbin* b);

/*
Pré-condição: a arvore existe
Pós-condição: Caractere retirado respeitando a estrutura da árvore
*/
Arvbin* Arvbin_retira(Arvbin* a, Caractere* ch);

/*
Pré-condição: A árvore existe
Pós-condição: Obtém o nó com o símbolo procurado
*/
bitmap* Arvbin_busca(Arvbin* a, char* symbol);

/*
Pré-condição: A árvore existe
Pós-condição: Imprime os dados da árvore
*/
void Arvbin_imprime (Arvbin* a);

/*
Pré-condição: A árvore existe
Pós-condição: Imprime a quantidade de nós da árvore
*/
int Arvbin_tamanho(Arvbin* a);

/*
Pré-condição: A árvore existe
Pós-condição: retorna a altura da árvore
*/
int Arvbin_Altura(Arvbin* a);

/*
Pré-condição: A árvore existe
Pós-condição: Imprime a quantidade de folhas da árvore
*/
int Arvbin_qtd_folhas(Arvbin* a);

/*
Pré-condição: A árvore existe
Pós-condição: retorna o caractere da raiz
*/
Caractere* retornaCaractereArv(Arvbin* arvore);

/*
Pré-condição: A árvore existe
Pós-condição: retorna todo o ramo da esquerda da árvore
*/
Arvbin* retornaArvEsquerda(Arvbin* arvore);

/*
Pré-condição: A árvore existe
Pós-condição: retorna todo o ramo da direita da árvore
*/
Arvbin* retornaArvDireita(Arvbin* arvore);

/*
Pré-condição: A árvore existe
Pós-condição: libera a memória alocada
*/
Arvbin* Arvbin_libera (Arvbin* a);

/*
Pré-condição: A árvore existe
Pós-condição: a partir da árvore, gera uma tabela de codificacao que sera utilizada
para gerar um arquivo binario com menos bits que o original 
*/
bitmap** geraTabelaCodificacao(Arvbin* arvore);

/*
Pré-condição: a árvore e a tabela existem
Pós-condição: com as informações da árvore e a tabela, ocorre o 
preenchimento desta com os códigos otimizados
*/
void preencheTabelaCodificacao(bitmap** tabela, Arvbin* arvore, bitmap* caminho, int alturaMax, int alturaAtual);

/*
Pré-condição: a tabela existe
Pós-condição: imprime as informações da tabela na saída padrão. Função auxiliar.
*/
void imprimeTabelaCodificacao(bitmap** tabela);

#endif