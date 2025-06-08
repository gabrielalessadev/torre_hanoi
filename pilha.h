#ifndef PILHA_H
#define PILHA_H

typedef struct Disco {
    int tamanho;
    struct Disco* proximo;
} Disco;

typedef struct Pilha {
    Disco* topo;
} Pilha;

void iniciar_pilha(Pilha* p);
int esta_vazia(Pilha* p);
void empilhar(Pilha* p, int tamanho);
int desempilhar(Pilha* p);

#endif 