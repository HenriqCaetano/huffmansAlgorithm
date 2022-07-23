#ifndef ARVBIN_H
#define ARVBIN_H

typedef struct arvbin Arvbin;

#include "caractere.h"

Arvbin* Arvbin_criavazia (void);

Arvbin* Arvbin_insere(Arvbin* a, Caractere* ch);

Arvbin* Arvbin_retira(Arvbin* a, Caractere* ch);

Arvbin* Arvbin_busca(Arvbin* a, char* symbol);

void Arvbin_imprime (Arvbin* a);

Arvbin* Arvbin_libera (Arvbin* a);





#endif