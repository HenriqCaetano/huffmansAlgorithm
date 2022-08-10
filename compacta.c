#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#include "treeList.h"

long int * generateFrequenceTable(FILE* file);
void printFrequenceTable(long int* table);
List * generateTreeList(long int* table);    
void generateHeader(long int * freqTable, char * fileName, FILE * file, unsigned long int qtdCaracteresArquivo);
void generateCompactedFile(FILE* file, bitmap ** tabelaCodificacao, FILE * compactedFile);
unsigned long int retornaQtdCaracteresArquivo(long int* freqTable);
void liberaTabelaCodificacao(bitmap** tabelaCodificacao);

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

    char *saveFileName  = strdup(fileName);// Salva o nome do arquivo original, que vai ser passado no cabeçalho
    char *compactedFileName = strcat(strtok(fileName, "."), ".comp");

    FILE *compactedFile = fopen(compactedFileName, "wb");

    if(!compactedFile){
        printf("Erro ao criar o arquivo\n");
        exit(1);
    }

    long int* freqTable = generateFrequenceTable(file);//gera a tabela de frequencia

    List* treeList = generateTreeList(freqTable);

    bitmap** tabelaCodificacao = geraTabelaCodificacao(retornaArvLista(treeList));

    int alturaArv = Arvbin_Altura(retornaArvLista(treeList));

    preencheTabelaCodificacao(tabelaCodificacao,retornaArvLista(treeList),NULL,alturaArv, 0);
    //imprimeTabelaCodificacao(tabelaCodificacao);

    unsigned long int qtdCaracteresArquivo = retornaQtdCaracteresArquivo(freqTable);

    generateHeader(freqTable, saveFileName, compactedFile, qtdCaracteresArquivo);

    fclose(file);

    FILE* newfile = fopen(saveFileName, "r");      // começando o arquivo do zero

    if(newfile == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    generateCompactedFile(newfile, tabelaCodificacao, compactedFile);

    fclose(newfile);
    fclose(compactedFile);

    free(freqTable);
    liberaTabelaCodificacao(tabelaCodificacao);
    free(saveFileName);

    Arvbin_libera(retornaArvLista(treeList));  //libera também as variaveis do tipo Caractere
    destroiLista(treeList);

    return 0;
}

long int * generateFrequenceTable(FILE* file) {
    long int* table = (long int*)malloc(sizeof(long int) * 256);
    memset(table, 0, sizeof(long int) * 256);    //inicializa cada elemento da tabela com 0
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    unsigned char c;
    //printf("processando arquivo\n");
    while(fread(&c, 1, 1, file)){
        table[c]++;
    }
    return table;
}

void printFrequenceTable(long int* table) {
    for (int i = 0; i < 256; i++) {
        printf("%d: %ld\n", i, table[i]);
    }
}

List * generateTreeList(long int * table){
    List* list = inicLista();
    int i=0, caracteresDiferentes=0;
    for(i = 0; i < 256; i++){
        if(table[i] != 0){
            caracteresDiferentes++;
            Arvbin* arv = Arvbin_criavazia();
            Caractere* ch = generateCh((unsigned char)i, table[i]);
            arv = Arvbin_insere(arv, ch);
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

void generateHeader(long int* freqTable, char* fileName, FILE* compactedFile, unsigned long int qtdCaracteresArquivo) {
    int qtdCaracteres = strlen(fileName);
    fwrite(&qtdCaracteres, sizeof(int), 1, compactedFile);
    fwrite(fileName, sizeof(char), qtdCaracteres, compactedFile);
    fwrite(freqTable, sizeof(long int), 256, compactedFile); //escreve a tabela de frequencia no arquivo compactado
    fwrite(&qtdCaracteresArquivo, sizeof(unsigned long int), 1, compactedFile);
}

void generateCompactedFile(FILE* file, bitmap ** tabelaCodificacao, FILE * compactedFile){
    int c, i,k;
    int qtdBits=0;
    bitmap* byte = bitmapInit(8);
    while ((c = fgetc(file)) != EOF) {
        bitmap* bitmap = tabelaCodificacao[c];
        for(i=0;i<bitmapGetLength(bitmap);i++){
            if(qtdBits<8){
                bitmapAppendLeastSignificantBit(byte, bitmapGetBit(bitmap, i));
                qtdBits++;
            }
            else{
                fwrite(bitmapGetContents(byte), sizeof(unsigned char), 1, compactedFile);

                //reset
                bitmapLibera(byte);
                qtdBits=0;
                byte = bitmapInit(8);

                bitmapAppendLeastSignificantBit(byte, bitmapGetBit(bitmap, i));
                qtdBits++;
            }	
        }
    }
    if(qtdBits>0){//ultimo byte nao completo
        fwrite(bitmapGetContents(byte), sizeof(unsigned char), 1, compactedFile);
    }
    bitmapLibera(byte);
}
unsigned long int retornaQtdCaracteresArquivo(long int* freqTable){
    unsigned long int qtdCaracteresArquivo = 0;
    for(int i=0;i<256;i++){
        qtdCaracteresArquivo += freqTable[i];
    }
    return qtdCaracteresArquivo;
}

void liberaTabelaCodificacao(bitmap** tabelaCodificacao){
    for(int i=0;i<256;i++){
        bitmapLibera(tabelaCodificacao[i]);
    }
    free(tabelaCodificacao);
}