#ifndef LIST_H
#define LIST_H

#include "arvbin.h"


typedef struct list List;


/*
    Inicializa uma lista vazia
    Pré-condição: nenhuma
    Pós-condição: lista criada, vazia
*/
List* inicLista(void);

/*
    Insere uma árvore na lista, ordenada de acordo com 
    a frequência: quanto maior a frequência, mais para o final da lista.
    Pré-condição: a lista e a árvore existem
    Pós-condição: árvore inserida com sucesso, de acordo com a ordenação proposta.
*/
List* insereList(List* list, Arvbin* arvore);

/*
    Retira a primeira árvore da lista
    Pré-condição: a lista existe e não é vazia
    Pós-condição: primeiro elemento retirado e recuperado com sucesso
*/
Arvbin* retiraLista(List* lista);

/*
    Obtém a primeira árvore da lista, mas a retirada não é feita
    Pré-condição: a lista existe e não é vazia
    Pós-condição: árvore obtida com sucesso
*/
Arvbin* retornaArvLista(List* lista);

/*
    Imprime a lista na saída padrão
    Pré-condição: a lista existe
    Pós-condição: nenhuma
*/
void printList(List* lista);

/*
    TBD
*/
int percorreLista(List* lista, int(*cb)(void*, void*), void* dado);

/*
    Destroi a lista
    Pré-condição: a lista existe
    Pós-condição: toda a memória liberada
*/
void destroiLista(List* lista);

#endif