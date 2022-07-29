#include <stdlib.h>
#include <stdio.h>
#include "arvbin.h"
#include <string.h>

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
        a = b;
    }
    else{
        a->esq = Arvbin_insere_arv_esq(a->esq, b);
    }
    return a;
}

Arvbin* Arvbin_insere_arv_dir(Arvbin* a, Arvbin* b){
    if(a==NULL){
        a = (Arvbin*)malloc(sizeof(Arvbin));
        a=b;
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

void Arvbin_imprime (Arvbin* a){
    printf("<");
    if(a!=NULL){
        printCharactere(a->ch);
        Arvbin_imprime(a->esq);
        Arvbin_imprime(a->dir);
    }
    printf(">");
}

int Arvbin_tamanho(Arvbin* a){
    if(a==NULL) return 0;
    return 1+Arvbin_tamanho(a->esq)+Arvbin_tamanho(a->dir);
}

int Arvbin_qtd_folhas(Arvbin* a){
    if(a==NULL) return 0;
    if(a->esq==NULL && a->dir==NULL) return 1;
    return Arvbin_qtd_folhas(a->esq)+Arvbin_qtd_folhas(a->dir);
}

int Arvbin_Altura(Arvbin* a){
    int tamEsq = 0, tamDir =0;
    if(a == NULL) return 1;
    else{

        tamEsq = Arvbin_Altura(a->esq) +1;
        tamDir = Arvbin_Altura(a->dir) +1;

        if(tamDir > tamEsq) return tamDir;
        else return tamEsq;
    }
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

bitmap** geraTabelaCodificacao(Arvbin* arvore){
	bitmap** tabela = malloc(256 * sizeof(bitmap*));//para caber toda a tabela ascii(deveria ser 256?)
	int i;
	for(i=0; i<256; i++){
        //o tamanho passado será suficiente?
		tabela[i] = bitmapInit(Arvbin_Altura(arvore));
	}
    return tabela;
}


void preencheTabelaCodificacao(bitmap** tabela, Arvbin* arvore, bitmap* caminho,int alturaMax, int alturaAtual){
    if(!tabela || !arvore) return;

    int i;

    if(arvore->esq == NULL && arvore->dir == NULL){
        printCharactere(retornaCaractereArv(arvore));
        printf("\n");
        //printf("max size %d\n", bitmapGetLength(caminho));
        for(i=0; i<alturaAtual; i++){
            bitmapAppendLeastSignificantBit(tabela[(int)returnSymbol(retornaCaractereArv(arvore))], bitmapGetBit(caminho,i));
            
            printf("%d", bitmapGetBit(caminho, i));
        }
        printf("\n");
    
    }
    else{
        bitmap* caminhoDir=bitmapInit(alturaMax);
        bitmap* caminhoEsq=bitmapInit(alturaMax);
        for(i=0; i<alturaAtual; i++){
            bitmapAppendLeastSignificantBit(caminhoEsq, bitmapGetBit(caminho,i));
            bitmapAppendLeastSignificantBit(caminhoDir, bitmapGetBit(caminho,i));
        }
        alturaAtual++;
        bitmapAppendLeastSignificantBit(caminhoEsq, 0);
        bitmapAppendLeastSignificantBit(caminhoDir, 1);
        preencheTabelaCodificacao(tabela, arvore->esq, caminhoEsq,alturaMax, alturaAtual);
        preencheTabelaCodificacao(tabela, arvore->dir, caminhoDir,alturaMax, alturaAtual);
        bitmapLibera(caminhoEsq);
        bitmapLibera(caminhoDir);
    }
}


void imprimeTabelaCodificacao(bitmap** tabela){
    int i;

    for(i=0;i<255;i++){
        printf("%c: %s\n", i,bitmapGetContents(tabela[i]));
    }
}

