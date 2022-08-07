#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvbin.h"
#include "treeList.h"

void printFrequenceTable(long int* table);
List * generateTreeList(long int * table);
void generateOriginalFile(FILE * compactedFile, List* treeList, FILE* file, unsigned long int qtdCaracteresArquivo);
void swap(char *x, char *y);
char* reverse(char *buffer, int i, int j);
unsigned int eh_bit_um(unsigned char byte, int i);

char* itoa(int value, char* buffer, int base);

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

    printf("Arquivo descompactado: %s\n", fileName); // esse printf dá erro por algum motivo

    FILE *originalFile = fopen(fileName, "w");
    if(originalFile == NULL){
        printf("Erro ao criar o arquivo\n");
        exit(1);
    }

    long int *freqTable = (long int*)malloc(sizeof(long int) * 256);
    fread(freqTable, sizeof(long int), 256, compactedFile);//a tabela de frequencia foi recuperada

    unsigned long int qtdCaracteresArquivo = 0;
    fread(&qtdCaracteresArquivo, sizeof(unsigned long int), 1, compactedFile);
    //printf("Qtd de caracteres no arquivo: %lu\n", qtdCaracteresArquivo);

    List* treeList = generateTreeList(freqTable);

    generateOriginalFile(compactedFile, treeList, originalFile, qtdCaracteresArquivo);

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
    unsigned char mascara = (1 << i);
    return byte & mascara;
}

void generateOriginalFile(FILE * compactedFile, List* treeList, FILE* originalFile, unsigned long int qtdCaracteresArquivo){
    Arvbin* arv = retiraLista(treeList);
    Arvbin* arvInicial = arv;
    unsigned long int i=0;//contador
    unsigned char c;
    int j=7, k=0;

    unsigned char byteChar;  

    fread(&byteChar, sizeof(unsigned char), 1, compactedFile);

    while(i < qtdCaracteresArquivo){
        j=7;
        while (j >= 0)
        {   
            if(eh_bit_um(byteChar,j) == 0){
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
}

char* itoa(int value, char* buffer, int base)
{
    // entrada inválida
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // considera o valor absoluto do número
    int n = abs(value);
 
    int i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // se o número for 0
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // Se a base for 10 e o valor for negativo, a string resultante
    // é precedido por um sinal de menos (-)
    // Com qualquer outra base, o valor é sempre considerado sem sinal
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
    //ALTERAÇÕES HENRIQUE E VINICIUS
    while(i<8){
        buffer[i] = '0';
        i++;
    }

    buffer[i] = '\0'; // string de terminação nula
 
    // inverte a string e retorna
    return reverse(buffer, 0, i - 1);
}

// Função para trocar dois números
void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
 
// Função para reverter `buffer[i…j]`
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}