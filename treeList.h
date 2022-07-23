#ifndef LIST_H
#define LIST_H

#include "arvbin.h"


typedef struct list List;

List* inicLista(void);

void insereList(List* list, Arvbin* arvore);

Arvbin* retiraLista(List* lista,Caractere* ch);

void organizaLista(List* lista);

void destroiLista(List* lista);


#endif