#include "caractere.h"
#include <stdlib.h>
#include <stdio.h>

struct caractere
{
    unsigned char symbol;
    long int frequence;
};

Caractere* generateCh(unsigned char symbol, long int frequence){
    Caractere* ch = (Caractere*)malloc(sizeof(Caractere));
    ch->symbol = symbol;
    ch->frequence = frequence;
    return ch;
}

long int returnFrequence(Caractere *c){
    return c->frequence;
}
unsigned char returnSymbol(Caractere *c){
    return c->symbol;
}
void printCharactere(Caractere *c){
    printf("(%c|%ld)", c->symbol, c->frequence);
}

