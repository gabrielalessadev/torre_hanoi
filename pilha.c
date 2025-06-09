#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

void iniciar_pilha(Pilha* p) {
    p->topo = NULL;
}

int esta_vazia(Pilha* p) {
    return p->topo == NULL;
}

void empilhar(Pilha* p, int tamanho) {
    Disco* novo_disco = (Disco*)malloc(sizeof(Disco));
    novo_disco->tamanho = tamanho;
    novo_disco->proximo = p->topo;
    p->topo = novo_disco;
}

int desempilhar(Pilha* p) {
    if (esta_vazia(p)) { 
        return -1; 
    }
    Disco* temporario = p->topo;
    int tamanho = temporario->tamanho;
    p->topo = p->topo->proximo;
    free(temporario);
    return tamanho;
}