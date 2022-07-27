#ifndef ARVBIN_H
#define ARVBIN_H

typedef struct arvbin Arvbin;

#include "caractere.h"

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

Arvbin* Arvbin_insere_arv_esq(Arvbin* a, Arvbin* b);

Arvbin* Arvbin_insere_arv_dir(Arvbin* a, Arvbin* b);

/*
Pré-condição: A arvore existe
Pós-condição: Caractere retirado respeitando a estrutura da árvore
*/
Arvbin* Arvbin_retira(Arvbin* a, Caractere* ch);

/*
Pré-condição: A árvore existe
Pós-condição: Obtém o nó com o símbolo procurado
*/
Arvbin* Arvbin_busca(Arvbin* a, char* symbol);

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
Pós-condição: libera a memória alocada
*/
Arvbin* Arvbin_libera (Arvbin* a);




#endif