#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvbin.h"
#include "treeList.h"

/*
    Pré-condição: a tabela existe
    Pós-condição: a tabela é impressa na saída padrão(função auxiliar)
*/
void printFrequenceTable(long int* table);

/*
    Pré-condição: a tabela existe
    Pós-condição: A partir da tabela de frequências, uma lista contendo uma única
    árvore é criada, esta árvore é a árvore de codificação
*/
List * generateTreeList(long int * table);

/*
    Pré-condição: os arquivos compactados e o novo arquivo original existem, a lista com a
    árvore de codificação existe
    Pós-condição: O arquivo original é montado novamente a partir da leitura do arquivo compactado
*/
void generateOriginalFile(FILE * compactedFile, List* treeList, FILE* file, unsigned long int qtdCaracteresArquivo);

/*
    Pré-condição: nenhuma
    Pós-condição: retorna true se o bit na posição i for 1
*/
unsigned int eh_bit_um(unsigned char byte, int i);

int main(int argc, char** argv){

    if(argc <= 1){
        printf("Argumentos insuficientes\n");
        exit(1);
    }

    char *compactedFileName = argv[1];

    FILE *compactedFile = fopen(compactedFileName, "rb");

    if(!compactedFile){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    int qtdCaracteres = 0;
    fread(&qtdCaracteres, sizeof(int), 1, compactedFile);


    char *fileName = (char*)malloc(sizeof(char) * (qtdCaracteres+1));
    fread(fileName, sizeof(char), qtdCaracteres, compactedFile);
    fileName[qtdCaracteres] = '\0';

    printf("Arquivo descompactado: %s\n", fileName); 

    FILE *originalFile = fopen(fileName, "w");
    if(originalFile == NULL){
        printf("Erro ao criar o arquivo\n");
        exit(1);
    }

    long int *freqTable = (long int*)malloc(sizeof(long int) * 256);
    //recupera a tabela de frequência a partir do cabeçalho
    fread(freqTable, sizeof(long int), 256, compactedFile);

    unsigned long int qtdCaracteresArquivo = 0;
    fread(&qtdCaracteresArquivo, sizeof(unsigned long int), 1, compactedFile);

    //a partir da tabela de frequência, monta a árvore novamente
    List* treeList = generateTreeList(freqTable);

    //gera o arquivo original
    generateOriginalFile(compactedFile, treeList, originalFile, qtdCaracteresArquivo);


    /*    liberação de memória    */
    fclose(compactedFile);
    fclose(originalFile);

    free(fileName);
    free(freqTable);
    destroiLista(treeList);

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

unsigned int eh_bit_um(unsigned char byte, int i){
    //deslocamento de bit
    unsigned char parcial = (1 << i);

    return byte & parcial;
}

void generateOriginalFile(FILE * compactedFile, List* treeList, FILE* originalFile, unsigned long int qtdCaracteresArquivo){
    Arvbin* arv = retiraLista(treeList);
    Arvbin* arvInicial = arv;
    unsigned long int i=0;//contador
    unsigned char c;
    int j=0, k=0;
    unsigned char byteChar;
    fread(&byteChar, sizeof(unsigned char), 1, compactedFile);


    while(i<qtdCaracteresArquivo){
        j=7;
        while (j >= 0)
        {   
            if(!eh_bit_um(byteChar,j)){
                arv = retornaArvEsquerda(arv);

                c = returnSymbol(retornaCaractereArv(arv));
                if(!retornaArvDireita(arv) && !retornaArvEsquerda(arv)){
                    fwrite(&c, sizeof(unsigned char), 1, originalFile);
                    arv = arvInicial;
                    i++;
                    if(i == qtdCaracteresArquivo) break;
                }
            }
            else{
                arv = retornaArvDireita(arv);
                c = returnSymbol(retornaCaractereArv(arv));
                if(!retornaArvDireita(arv) && !retornaArvEsquerda(arv)){
                    fwrite(&c, sizeof(char), 1, originalFile);
                    arv = arvInicial;
                    i++;
                    if(i == qtdCaracteresArquivo) break;
                }
            }
            j--;
        }
        fread(&byteChar, sizeof(unsigned char), 1, compactedFile);
    }
    Arvbin_libera(arvInicial);
}