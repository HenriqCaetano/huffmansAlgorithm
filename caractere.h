#ifndef CARACTERE_H
#define CARACTERE_H

typedef struct caractere Caractere;

Caractere* generateCh(unsigned char symbol, int frequence);

int returnFrequence(Caractere *c);

unsigned char returnSymbol(Caractere *c);

void printCharactere(Caractere *c);

#endif // CARACTERE_H