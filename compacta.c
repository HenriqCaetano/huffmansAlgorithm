#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeList.h"

int * generateFrequenceTable(FILE* file);
void printFrequenceTable(int* table);
List * generateTreeList(int* table);

int main(int argc, char** argv) {
    if(argc<=1){
        printf("Argumentos insuficientes\n");
        exit(1);
    }
    char *fileName = argv[1];
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    
    char *compactedFileName = strcat(strtok(fileName, "."), ".comp");
    FILE *compactedFile = fopen(compactedFileName, "w");
    if(compactedFile == NULL){
        printf("Erro ao criar o arquivo\n");
        exit(1);
    }

    int* freqTable = generateFrequenceTable(file);    //gera a tabela de frequencia

    printFrequenceTable(freqTable);

    List* treeList = generateTreeList(freqTable);

    printList(treeList);    

    fclose(file);
    fclose(compactedFile);

    return 0;
}

int * generateFrequenceTable(FILE* file) {
    int* table = (int*)malloc(sizeof(int) * 256);
    memset(table, 0, sizeof(int) * 256);    //inicializa cada elemento da tabela com 0
    if (file == NULL) {
        printf("Erro ao abrir o arquivoooo\n");
        exit(1);
    }
    int c;
    printf("processando arquivo\n");
    while ((c = fgetc(file)) != EOF) {
        table[c]++;
    }
    return table;
}

void printFrequenceTable(int* table) {
    for (int i = 0; i < 256; i++) {
        printf("%d: %d\n", i, table[i]);
    }
}

List * generateTreeList(int * table){
    List* list = inicLista();
    int i=0;
    for(i = 0; i < 256; i++){
        if(table[i] != 0){
            Arvbin* arv = Arvbin_criavazia();
            arv = Arvbin_insere(arv, generateCh((char)i, table[i]));
            insereList(list, arv);
        }
    }
    return list;
}