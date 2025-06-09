#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hanoi.h"
#include "historico.h"
#include <ctype.h> 

// gcc -o hanoi_game main.c hanoi.c pilha.c historico.c -Wall -Wextra
// .\hanoi_game.exe

int char_para_pino(char c) {
    c = tolower(c);
    if (c == 'a') return 0;
    if (c == 'b') return 1;
    if (c == 'c') return 2;
    return -1;
}

char pino_para_char(int p) {
    if (p == 0) return 'A'; 
    if (p == 1) return 'B'; 
    if (p == 2) return 'C';
    return '?';
}

void rodar_partida(RegistroPartida** inicio_historico, int num_discos, const char* nome_jogador) {
    JogoHanoi jogo;
    iniciar_jogo(&jogo, num_discos);

    char linha_entrada[20];
    int pino_sugerido_origem, pino_sugerido_destino;

    while (!verificar_vitoria(&jogo)) {
        exibir_jogo(&jogo);

        encontrar_prox_movimento_otimo(&jogo, &pino_sugerido_origem, &pino_sugerido_destino);
        printf("\nSugestao de jogada: %c -> %c\n", pino_para_char(pino_sugerido_origem),
        pino_para_char(pino_sugerido_destino));

        printf("Jogador: %s | Mover de [A,B,C] para [A,B,C] (ex: AB) | 'R' para reiniciar: ", nome_jogador);

        if (fgets(linha_entrada, sizeof(linha_entrada), stdin) == NULL) continue;

        if (tolower(linha_entrada[0]) == 'r') {
            printf("\n Reiniciando a partida!\n");
            iniciar_jogo(&jogo, num_discos);
            continue;
        }

        char o, d;
        if (sscanf(linha_entrada, " %c%c", &o, &d) == 2) {
            int pino_o = char_para_pino(o);
            int pino_d = char_para_pino(d);
            if (pino_o == -1 || pino_d == -1) {
                 printf("Entrada invalida. Use as letras A, B ou C.\n");
            } else if (!fazer_movimento(&jogo, pino_o, pino_d)) {
                printf("!!! Movimento invalido. Pressione Enter para continuar. !!!");
                getchar();
            }
        } else {
            printf("Formato invalido. Digite as duas letras juntas (ex: AC).\n");
        }
    }

    exibir_jogo(&jogo);
    printf("\n*** Parabens, %s, voce venceu em %d movimentos! ***\n", nome_jogador, jogo.movimentos);
    adicionar_registro(inicio_historico, jogo.movimentos, nome_jogador, num_discos);
    salvar_historico_em_arquivo(*inicio_historico);
}

int main() {
    RegistroPartida* inicio_historico = NULL;
    carregar_historico_do_arquivo(&inicio_historico);

    int escolha;
    do {
        printf("\n Menu Torre de Hanoi \n");
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
                char nome_jogador[TAMANHO_MAX_NOME];
                char jogar_novamente;

                printf("Digite seu nome: ");
                fgets(nome_jogador, sizeof(nome_jogador), stdin);
                nome_jogador[strcspn(nome_jogador, "\n")] = 0;

                printf("Digite o numero de discos: ");
                scanf("%d", &num_discos);
                while(getchar() != '\n');

                do {
                    rodar_partida(&inicio_historico, num_discos, nome_jogador);
                    printf("\nJogar novamente com %d discos? (s/n): ", num_discos);
                    scanf(" %c", &jogar_novamente);
                    while(getchar() != '\n');
                } while (tolower(jogar_novamente) == 's');
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