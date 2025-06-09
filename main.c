#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hanoi.h"
#include "historico.h"

// gcc -o hanoi_game main.c hanoi.c pilha.c historico.c -Wall -Wextra
// .\hanoi_game.exe

void rodar_partida(RegistroPartida** inicio_historico, int num_discos) {
    JogoHanoi jogo;
    char nome_jogador[TAMANHO_MAX_NOME];

    printf("Digite seu nome: ");
    fgets(nome_jogador, sizeof(nome_jogador), stdin);
    nome_jogador[strcspn(nome_jogador, "\n")] = 0;

    iniciar_jogo(&jogo, num_discos);

    while (!verificar_vitoria(&jogo)) {
        exibir_jogo(&jogo);
        int origem, destino;
        printf("Mover do pino (0,1,2) para o pino (0,1,2): ");
        scanf("%d %d", &origem, &destino);
        while(getchar() != '\n');

        if (!fazer_movimento(&jogo, origem, destino)) {
            printf("!!! Movimento invalido. Pressione Enter para tentar novamente. !!!");
            getchar();
        }
    }
    exibir_jogo(&jogo);
    printf("\n*** Parabens, %s, voce venceu em %d movimentos! ***\n", nome_jogador, jogo.movimentos);
    adicionar_registro(inicio_historico, jogo.movimentos, nome_jogador, jogo.num_discos);
    salvar_historico_em_arquivo(*inicio_historico);
}

int main() {
    RegistroPartida* inicio_historico = NULL;
    carregar_historico_do_arquivo(&inicio_historico);

    int escolha;
    do {
        printf("\n Menu Torre de Hanoi\n");
        printf("1. Novo Jogo\n");
        printf("2. Ver Historico\n");
        printf("3. Buscar no Historico\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        while(getchar() != '\n');

        switch(escolha) {
            case 1: {
                int num_discos;
                printf("Digite o numero de discos: ");
                scanf("%d", &num_discos);
                while(getchar() != '\n');
                rodar_partida(&inicio_historico, num_discos);
                break;
            }
            case 2:
                exibir_historico(inicio_historico);
                break;
            case 3:
                buscar_historico(inicio_historico);
                break;
            case 4:
                printf("Ate mais!\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (escolha != 4);

    liberar_historico(&inicio_historico);
    return 0;
}