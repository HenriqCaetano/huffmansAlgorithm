#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("oi\n");
    for (int i = 0; i < 256; i++) {
        printf("%d: %d\n", i, table[i]);
    }
}


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

    fclose(file);
    fclose(compactedFile);

    return 0;
}