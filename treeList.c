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

void recursiveDestroy(Celula* celula);


List* inicLista(void){
    List* lista = malloc(sizeof(List));

    lista->prim = NULL;
    lista->ult = NULL;

    return lista;
}

//faz a inserção de forma ordenada(da menor frequencia para a maior frequencia)
List* insereList(List* list, Arvbin* arvore){
    if(!list) return NULL;

    Celula* nova = malloc(sizeof(Celula));
    nova->arvore = arvore;

    //caso lista vazia
    if(!list->prim && !list->ult){
        nova->prox = NULL;
        list->prim = nova;
        list->ult = nova;
        return list;
    }
    //caso contrário
    else{
        Celula* atual, *ant;

        for(atual = list->prim; atual != NULL; atual = atual->prox){
            if(!(returnFrequence(retornaCaractereArv(arvore)) > returnFrequence(retornaCaractereArv(atual->arvore)))){
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
        else if(atual == list->prim){
            list->prim = nova;
            nova->prox = atual;
        }
        //caso comum
        else{
            ant->prox = nova;
            nova->prox = atual;
        }
    }
    return list;
}

Arvbin* retiraLista(List* list){
    if(!list->prim && !list->ult) return NULL; //caso lista vazia!

    Arvbin* retorno = list->prim->arvore;
    Celula* aux = list->prim;
    if(list->prim == list->ult){
        list->prim = NULL;
        list->ult = NULL;
    }
    else{
        list->prim = list->prim->prox;
    }
    free(aux);
    return retorno;
}

Arvbin* retornaArvLista(List* lista){
    if(!lista->prim) return NULL;
    return lista->prim->arvore;
}

int percorreArv(Arvbin* arv, int(*cb)(void*, void*), void* dado){
    //
}

void destroiLista(List* list){
    if(!list) return;

    recursiveDestroy(list->prim);
    free(list);
}

void printList(List* lista){
    if(!lista) return;

    Celula* atual;
    for(atual = lista->prim; atual != NULL; atual = atual->prox){
        Arvbin_imprime(atual->arvore);
        printf("\n");
    }
}

//utilizado para destruir a lista recursivamente
void recursiveDestroy(Celula* celula){
    if(!celula) return;

    recursiveDestroy(celula->prox);
    free(celula);
}