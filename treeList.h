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


void destroiLista(List* lista);


#endif