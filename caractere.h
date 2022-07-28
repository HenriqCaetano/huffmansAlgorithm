#ifndef CARACTERE_H
#define CARACTERE_H

typedef struct caractere Caractere;

/*
    Inicializa um tipo caractere
    Pré-condição: nenhuma
    Pós-condição: caractere criado
*/
Caractere* generateCh(unsigned char symbol, int frequence);


/*
    Retorna a frequência de um caractere
    Pré-condição: O caractere existe
    Pós-condição: frequência retornada
*/
int returnFrequence(Caractere *c);

/*
    Retorna o símbolo de um caractere
    Pré-condição: O caractere existe
    Pós-condição: símbolo retornado
*/
unsigned char returnSymbol(Caractere *c);


/*
    Imprime o caractere na saída padrão
    Pré-condição: O caractere existe
    Pós-condição: nenhuma
*/
void printCharactere(Caractere *c);

#endif