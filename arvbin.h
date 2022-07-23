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
Pré-condição: a árvore existe
Pós-condição: Caractere inserido apropriadamente na árvore
*/
Arvbin* Arvbin_insere(Arvbin* a, Caractere* ch);

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

Caractere* retornaCaractereArv(Arvbin* arvore);

/*
Pré-condição: A árvore existe
Pós-condição: libera a memória alocada
*/
Arvbin* Arvbin_libera (Arvbin* a);



#endif