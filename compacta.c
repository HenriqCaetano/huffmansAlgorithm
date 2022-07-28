#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeList.h"

int * generateFrequenceTable(FILE* file);
void printFrequenceTable(int* table);
List * generateTreeList(int* table);
int acumula(void* arv, void* dado);
void generateHeader(int * freqTable, char * fileName, FILE * file);

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

    char *saveFileName  = (char*)malloc(sizeof(char) * strlen(fileName));  // Salva o nome do arquivo original, que vai ser passado no cabeçalho
    strcpy(saveFileName, fileName);                                        // o ponteiro 'fileName' vai ser modificado no strtok, então é necessário salvar o nome original em outra variável
    
    char *compactedFileName = strcat(strtok(fileName, "."), ".comp");
    FILE *compactedFile = fopen(compactedFileName, "w");
    if(compactedFile == NULL){
        printf("Erro ao criar o arquivo\n");
        exit(1);
    }

    int* freqTable = generateFrequenceTable(file);    //gera a tabela de frequencia

    List* treeList = generateTreeList(freqTable);

    printList(treeList);

    //unsigned int bitmapMaxSize = Arvbin_tamanho(retornaArvLista(treeList)) + 8*Arvbin_qtd_folhas(retornaArvLista(treeList));
    //printf("Tamanho do bitmap: %d\n", bitmapMaxSize);

    generateHeader(freqTable, saveFileName, compactedFile);
    

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
    //printf("processando arquivo\n");
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

void generateHeader(int * freqTable, char * fileName, FILE * compactedFile){
    int qtdCaracteres = strlen(fileName);
    fwrite(&qtdCaracteres, sizeof(int), 1, compactedFile);
    fwrite(fileName, sizeof(char), qtdCaracteres, compactedFile);
    fwrite(freqTable, sizeof(int), 256, compactedFile); //escreve a tabela de frequencia no arquivo compactado
}


