#include "treeList.h"
#include "arvbin.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct cel Celula;

struct cel
{
    Arvbin* arvore;
    Celula* prox;
};

struct list{
    Celula* prim;
    Celula* ult;
};

List* inicLista(void){
    List* lista = malloc(sizeof(List));

    lista->prim = NULL;
    lista->ult = NULL;

    return lista;
}

//faz a inserção de forma ordenada(da menor frequencia para a maior frequencia)
void insereList(List* list, Arvbin* arvore){
    if(!list) return;

    Celula* nova = malloc(sizeof(Celula));
    nova->arvore = arvore;

    //caso lista vazia
    if(!list->prim && !list->ult){
        nova->prox = NULL;
        list->prim = nova;
        list->ult = nova;
        return;
    }
    //caso contrário
    else{
        Celula* atual, *ant;

        for(atual = list->prim; atual != NULL; atual= atual->prox){
            if(!returnFrequence(retornaCaractereArv(arvore)) > returnFrequence(retornaCaractereArv(atual->arvore))){
                break;
            }
            ant = atual;
        }
        //caso último da lista
        if(atual == NULL){
            ant->prox = nova;
            list->ult = nova;
            nova->prox = NULL;
        }
        //caso primeiro da lista
        else if(atual = list->ult){
            list->prim = nova;
            nova->prox = atual;
        }
        //caso comum
        else{
            ant->prox = nova;
            nova->prox = atual;
        }
    }

}

//faz a retirada da primeira árvore!
Arvbin* retiraLista(List* list,Caractere* ch){
    if(!list->prim && !list->ult) return NULL; //caso lista vazia!

    Arvbin* retorno = list->prim->arvore;
    Celula* aux = list->prim;
    list->prim = list->prim->prox;
    free(aux);
    return retorno;
}

void destroiList(List* list){
    if(!list) return;

    recursiveDestroy(list->prim);
    free(list);
}

void recursiveDestroy(Celula* celula){
    if(!celula) return;

    recursiveDestroy(celula->prox);
    free(celula);
}