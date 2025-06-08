#ifndef HANOI_H
#define HANOI_H

#include "pilha.h"

#define NUM_PINOS 3

typedef struct {
    Pilha pinos[NUM_PINOS];
    int num_discos;
    int movimentos;
} JogoHanoi;

void iniciar_jogo(JogoHanoi* jogo, int num_discos);
int fazer_movimento(JogoHanoi* jogo, int origem, int destino);
void exibir_jogo(JogoHanoi* jogo);

int verificar_vitoria(JogoHanoi* jogo);
#endif 