#ifndef CARACTERE_H
#define CARACTERE_H

typedef struct caractere Caractere;

Caractere* generateCh(char symbol, int frequence);

int returnFrequence(Caractere *c);

char returnSymbol(Caractere *c);

void printCharactere(Caractere *c);

#endif // CARACTERE_H