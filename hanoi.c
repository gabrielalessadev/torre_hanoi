#include "hanoi.h"
#include <stdio.h>

void iniciar_jogo(JogoHanoi* jogo, int num_discos) {
    jogo->num_discos = num_discos;
    jogo->movimentos = 0;
    for (int i = 0; i < NUM_PINOS; i++) {
        iniciar_pilha(&jogo->pinos[i]);
    }
    for (int i = num_discos; i >= 1; i--) {
        empilhar(&jogo->pinos[0], i);
    }
}

int fazer_movimento(JogoHanoi* jogo, int pino_origem, int pino_destino) {
    if (esta_vazia(&jogo->pinos[pino_origem])) {
        return 0; 
    }
    int disco_a_mover = desempilhar(&jogo->pinos[pino_origem]);
    if (!esta_vazia(&jogo->pinos[pino_destino]) && jogo->pinos[pino_destino].topo->tamanho < disco_a_mover) {
        empilhar(&jogo->pinos[pino_origem], disco_a_mover); 
        return 0; 
    }
    empilhar(&jogo->pinos[pino_destino], disco_a_mover);
    jogo->movimentos++;
    return 1; 
}

void exibir_jogo(JogoHanoi* jogo) {
    system("cls");
    printf("\n Torre de Hanoi \n");
    printf("Movimentos: %d\n\n", jogo->movimentos);
    for (int i = 0; i < NUM_PINOS; i++) {
        printf("Pino %c: ", 'A' + i);
        Pilha pino_temp = jogo->pinos[i];
        Disco* atual = pino_temp.topo;
        while(atual != NULL) {
            printf("%d ", atual->tamanho);
            atual = atual->proximo;
        }
        printf("\n");
    }
    printf("---------------------\n");
}
int verificar_vitoria(JogoHanoi* jogo) {
    return esta_vazia(&jogo->pinos[0]) && esta_vazia(&jogo->pinos[1]);
}