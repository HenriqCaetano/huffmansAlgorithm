#include "caractere.h"
#include <stdlib.h>
#include <stdio.h>

struct caractere
{
    unsigned char symbol;
    int frequence;
};

Caractere* generateCh(unsigned char symbol, int frequence){
    Caractere* ch = (Caractere*)malloc(sizeof(Caractere));
    ch->symbol = symbol;
    ch->frequence = frequence;
    return ch;
}

int returnFrequence(Caractere *c){
    return c->frequence;
}
unsigned char returnSymbol(Caractere *c){
    return c->symbol;
}
void printCharactere(Caractere *c){
    printf("(%c|%d)", c->symbol, c->frequence);
}

