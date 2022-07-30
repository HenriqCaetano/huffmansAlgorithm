#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvbin.h"
#include "treeList.h"

void printFrequenceTable(int* table);
List * generateTreeList(int * table);
void generateOriginalFile(FILE * compactedFile, List* treeList, FILE* file);

int main(int argc, char** argv){
    if(argc<=1){
        printf("Argumentos insuficientes\n");
        exit(1);
    }

    char *compactedFileName = argv[1];
    FILE *compactedFile = fopen(compactedFileName, "r");
    if(compactedFile == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    int qtdCaracteres = 0;
    fread(&qtdCaracteres, sizeof(int), 1, compactedFile);

    char *fileName = (char*)malloc(sizeof(char) * qtdCaracteres);
    fread(fileName, sizeof(char), qtdCaracteres, compactedFile);


    FILE *file = fopen(fileName, "w");
    if(file == NULL){
        printf("Erro ao criar o arquivo\n");
        exit(1);
    }

    int *freqTable = (int*)malloc(sizeof(int) * 256);
    fread(freqTable, sizeof(int), 256, compactedFile);


    List* treeList = generateTreeList(freqTable);

    generateOriginalFile(compactedFile, treeList, file);


    return 0;
}

void printFrequenceTable(int* table) {
    for (int i = 0; i < 256; i++) {
        printf("%d: %d\n", i, table[i]);
    }
}
List * generateTreeList(int * table){
    List* list = inicLista();
    int i=0, caracteresDiferentes=0;
    for(i = 0; i < 256; i++){
        if(table[i] != 0){
            caracteresDiferentes++;
            Arvbin* arv = Arvbin_criavazia();
            arv = Arvbin_insere(arv, generateCh((unsigned char)i, table[i]));
            insereList(list, arv);
        }
    }
    for(i=0;i<caracteresDiferentes-1;i++){
        Arvbin* arv = Arvbin_criavazia();
        Arvbin* arv1 = retiraLista(list);
        Arvbin* arv2 = retiraLista(list);
        Caractere* c1 = retornaCaractereArv(arv1);
        Caractere* c2 = retornaCaractereArv(arv2);
        arv = Arvbin_insere(arv, generateCh('\0', returnFrequence(c1) + returnFrequence(c2)));
        arv = Arvbin_insere_arv_esq(arv, arv1);
        arv = Arvbin_insere_arv_dir(arv, arv2);
        list = insereList(list, arv);
    }

    return list;
}

void generateOriginalFile(FILE * compactedFile, List* treeList, FILE* file){
    Arvbin* arv = retiraLista(treeList);

    bitmap* byte = bitmapInit(8);
    while (fread(byte, sizeof(unsigned char), 1, compactedFile) == 1) {
       // to do
    }
    
}