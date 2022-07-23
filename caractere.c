#include "caractere.h"

struct caractere
{
    char symbol;
    int frequence;
};

int returnFrequence(Caractere *c){
    return c->frequence;
}
char returnSymbol(Caractere *c){
    return c->symbol;
}
void printCharactere(Caractere *c){
    printf("(%c|%d)", c->symbol, c->frequence);
}
