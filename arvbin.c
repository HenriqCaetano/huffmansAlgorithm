#include "arvbin.h"
#include <stdio.h>
#include <stdlib.h>

struct arvbin{
    Caractere* ch;
    Arvbin* esq;
    Arvbin* dir;
};


Arvbin* Arvbin_criavazia (void){
    return NULL;
}

Arvbin* Arvbin_insere(Arvbin* a, Caractere* ch){
    if(a==NULL){
        a = (Arvbin*)malloc(sizeof(Arvbin));
        a->ch = ch;
        a->esq = a->dir = NULL;
    }
    else if(returnFrequence(ch)>returnFrequence(a->ch)){
            a->dir = Arvbin_insere(a->dir, ch);
    }
    else
        a->esq = Arvbin_insere(a->esq, ch);

    return a;
}

Arvbin* Arvbin_insere_arvbin(Arvbin* a, Arvbin* b){
    if(a==NULL){
        a = (Arvbin*)malloc(sizeof(Arvbin));
        a->ch = b->ch;
        a->esq = a->dir = NULL;
    }
    else if(returnFrequence(b->ch)>returnFrequence(a->ch)){
            a->dir = Arvbin_insere_arvbin(a->dir, b);
    }
    else
        a->esq = Arvbin_insere_arvbin(a->esq, b);

    return a;
}

Arvbin* Arvbin_insere_esq(Arvbin* a, Caractere* ch){
    if(a==NULL){
        a = (Arvbin*)malloc(sizeof(Arvbin));
        a->ch = ch;
        a->esq = a->dir = NULL;
    }
    else{
        a->esq = Arvbin_insere_esq(a->esq, ch);
    }
    return a;
}

Arvbin* Arvbin_insere_dir(Arvbin* a, Caractere* ch){
    if(a==NULL){
        a = (Arvbin*)malloc(sizeof(Arvbin));
        a->ch = ch;
        a->esq = a->dir = NULL;
    }
    else{
        a->dir = Arvbin_insere_dir(a->dir, ch);
    }
    return a;
}

Arvbin* Arvbin_insere_arv_esq(Arvbin* a, Arvbin* b){
    if(a==NULL){
        a = (Arvbin*)malloc(sizeof(Arvbin));
        a->ch = b->ch;
        a->esq = a->dir = NULL;
    }
    else{
        a->esq = Arvbin_insere_arv_esq(a->esq, b);
    }
    return a;
}

Arvbin* Arvbin_insere_arv_dir(Arvbin* a, Arvbin* b){
    if(a==NULL){
        a = (Arvbin*)malloc(sizeof(Arvbin));
        a->ch = b->ch;
        a->esq = a->dir = NULL;
    }
    else{
        a->dir = Arvbin_insere_arv_dir(a->dir, b);
    }
    return a;
}

Arvbin* Arvbin_retira(Arvbin* a, Caractere* ch){
    if(a == NULL)
        return NULL;
    else if(returnFrequence(ch)>returnFrequence(a->ch)){
        a->dir=Arvbin_retira(a->dir, ch);
    }
    else if(returnFrequence(ch)<returnFrequence(a->ch)){
        a->esq=Arvbin_retira(a->esq, ch);
    }
    
    else{
        //caso nó folha
        if(a->esq == NULL && a->dir == NULL){
            free(a);
            a=NULL;
        }
        //caso exista elementos na direita
        else if(a->esq==NULL){
            Arvbin* aux = a;
            a=a->dir;
            free(aux);
        }
        //caso exista elementos na esquerda
        else if(a->dir==NULL){
            Arvbin* aux = a;
            a=a->esq;
            free(aux);
        }
        //caso existam elementos nas duas direções
        else{
            Arvbin* ant = a->esq;
            while(ant->dir!=NULL){
                ant=ant->dir;
            }
            Caractere* c = a->ch;
            a->ch=ant->ch;
            ant->ch=c;
            
            a->esq=Arvbin_retira(a->esq, ch);
        }
    }
    return a;
}
/*  Ainda nao pensei como fazer

Arvbin* Arvbin_busca(Arvbin* a, char* symbol){
    if(a == NULL) return NULL;
    if(retornaMatricula(a->aluno)>mat){
        return Arvbin_busca(a->esq, mat);
    }
    else if(retornaMatricula(a->aluno)<mat){
        return Arvbin_busca(a->dir, mat);
    }
    else{
        return a;
    }
}
*/

void Arvbin_imprime (Arvbin* a){
    printf("<");
    if(a!=NULL){
        printCharactere(a->ch);
        Arvbin_imprime(a->esq);
        Arvbin_imprime(a->dir);
    }
    printf(">");
}

Caractere* retornaCaractereArv(Arvbin* arvore){
    return arvore->ch;
}

Arvbin* Arvbin_libera (Arvbin* a){
    if(a!=NULL){
        Arvbin_libera(a->esq);
        Arvbin_libera(a->dir);
        free(a);
    }
    return NULL;
}