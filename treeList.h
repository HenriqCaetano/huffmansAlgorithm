#ifndef LIST_H
#define LIST_H

#include "arvbin.h"


typedef struct list List;

List* inicLista(void);

List* insereList(List* list, Arvbin* arvore);

Arvbin* retiraLista(List* lista);

Arvbin* retornaArvLista(List* lista);

void organizaLista(List* lista);

void printList(List* lista);

int percorreLista(List* lista, int(*cb)(void*, void*), void* dado);

void destroiLista(List* lista);


#endif