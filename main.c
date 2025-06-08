#include <stdio.h>
#include "hanoi.h"

void rodar_partida(int num_discos) {
    JogoHanoi jogo;
    iniciar_jogo(&jogo, num_discos);

    while (!verificar_vitoria(&jogo)) {
        exibir_jogo(&jogo);
        int origem, destino;
        printf("Mover do pino (0,1,2) para o pino (0,1,2): ");
        scanf("%d %d", &origem, &destino);

        if (!fazer_movimento(&jogo, origem, destino)) {
            printf("Movimento invalido. Tente novamente.\n");
        }
    }
    exibir_jogo(&jogo);
    printf("\n*** Parabens, voce venceu ***\n");
}

int main() {
    int escolha;
    printf("\n Menu Torre de Hanoi\n");
    printf("1. Novo Jogo\n");
    printf("2. Sair\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    if (escolha == 1) {
        rodar_partida(3); 
    }
    return 0;
}