#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvbin.h"
#include "treeList.h"

void printFrequenceTable(long int* table);
List * generateTreeList(long int * table);
void generateOriginalFile(FILE * compactedFile, List* treeList, FILE* file, unsigned long int qtdCaracteresArquivo);

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

    printf("Arquivo descompactado: %s\n", fileName);

    FILE *file = fopen(fileName, "w");
    if(file == NULL){
        printf("Erro ao criar o arquivo\n");
        exit(1);
    }

    long int *freqTable = (long int*)malloc(sizeof(long int) * 256);
    fread(freqTable, sizeof(long int), 256, compactedFile);

    unsigned long int qtdCaracteresArquivo = 0;
    fread(&qtdCaracteresArquivo, sizeof(unsigned long int), 1, compactedFile);
    //printf("Qtd de caracteres no arquivo: %lu\n", qtdCaracteresArquivo);

    List* treeList = generateTreeList(freqTable);

    generateOriginalFile(compactedFile, treeList, file, qtdCaracteresArquivo);


    return 0;
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

void generateOriginalFile(FILE * compactedFile, List* treeList, FILE* file, unsigned long int qtdCaracteresArquivo){
    Arvbin* arv = retiraLista(treeList);
    Arvbin* arvInicial = arv;
    unsigned long int i=0;
    unsigned char c;
    int j=0, k=0;
    bitmap* byte = bitmapInit(8);
    fread(bitmapGetContents(byte), sizeof(unsigned char), 8, compactedFile);
    printf("%c 1\n", bitmapGetContents(byte)[0]);
    printf("%c 2\n", bitmapGetContents(byte)[1]);
    printf("%c 3\n", bitmapGetContents(byte)[2]);
    printf("%c 4\n", bitmapGetContents(byte)[3]);

    /*
    while(i<qtdCaracteresArquivo){
        j=0, k=0;
        while (j<8)
        {   
            int bit = bitmapGetBit(byte, j);
            if(bit == 0){
                arv = retornaArvEsquerda(arv);
                c = returnSymbol(retornaCaractereArv(arv));
                if(c != '\0'){
                    fwrite(&c, sizeof(char), 1, file);
                    arv = arvInicial;
                    i++;
                }
            }
            else{
                arv = retornaArvDireita(arv);
                c = returnSymbol(retornaCaractereArv(arv));
                if(c != '\0'){
                    fwrite(&c, sizeof(char), 1, file);
                    arv = arvInicial;
                    i++;
                }
            }
            j++;
        }
        //fread(bytechar, sizeof(int), 1, compactedFile);
        while (k<8) {
            bitmapAppendLeastSignificantBit(byte, byteInt[k]);
            k++;
        }
    }
    */
}