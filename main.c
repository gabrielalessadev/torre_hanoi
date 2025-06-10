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

void rodar_partida(JogoHanoi* jogo, RegistroPartida** inicio_historico, const char* nome_jogador, int num_discos) {
    char linha_entrada[20];
    char char_origem, char_destino;
    int pino_origem, pino_destino;
    int pino_sugerido_origem, pino_sugerido_destino;

    while (!verificar_vitoria(jogo)) {
        exibir_jogo(jogo);
        
        encontrar_prox_movimento_otimo(jogo, &pino_sugerido_origem, &pino_sugerido_destino);
        printf("\nSugestao de jogada: %c -> %c\n", pino_para_char(pino_sugerido_origem), pino_para_char(pino_sugerido_destino));

        printf("Jogador: %s | Discos: %d\n", nome_jogador, num_discos);
        printf("Mover de [A,B,C] para [A,B,C] (ex: AB). 'R' para Reiniciar, 'S' para Sair: ");
        
        if (fgets(linha_entrada, sizeof(linha_entrada), stdin) == NULL) {
            continue;
        }

        char primeira_letra = tolower(linha_entrada[0]);

        if (primeira_letra == 'r') {
            printf("\n Reiniciando a partida!\n");
            iniciar_jogo(jogo, num_discos);
            continue;
        }

        
        if (primeira_letra == 's') {
            printf("\nVoltando para o menu principal...\n");
            return; 
        }
        
        if (sscanf(linha_entrada, " %c%c", &char_origem, &char_destino) == 2) {
            pino_origem = char_para_pino(char_origem);
            pino_destino = char_para_pino(char_destino);

            if (pino_origem == -1 || pino_destino == -1) {
                printf("Entrada invalida. Use as letras A, B ou C para os pinos.\n");
            } else {
                     fazer_movimento(jogo, pino_origem, pino_destino);
            }
        } else {
             printf("Formato invalido. Digite as duas letras juntas (ex: AC).\n");
        }
    }

    exibir_jogo(jogo);
    if (verificar_vitoria(jogo)) {
        printf("\nParabens, %s! Voce venceu em %d movimentos!\n", nome_jogador, jogo->movimentos);
        adicionar_registro(inicio_historico, jogo->movimentos, nome_jogador, num_discos);
        salvar_historico_em_arquivo(*inicio_historico);
    }
}

int main() {
    JogoHanoi jogo;
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
        if (scanf("%d", &escolha) != 1) {
            printf("Entrada invalida. Digite um numero.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (escolha) {
            case 1: {
                char nome_jogador[TAMANHO_MAX_NOME];
                printf("Digite seu nome: ");
                fgets(nome_jogador, sizeof(nome_jogador), stdin);
                nome_jogador[strcspn(nome_jogador, "\n")] = 0;

                for (;;) { 
                    int num_discos;
                    printf("\nDigite o numero de discos para esta partida (min. 1, max. 10): ");
                    if (scanf("%d", &num_discos) != 1) {
                        printf("Entrada invalida. Digite um numero.\n");
                        while ((c = getchar()) != '\n' && c != EOF);
                        continue; 
                    }
                    while ((c = getchar()) != '\n' && c != EOF);

                    if (num_discos < 1 || num_discos > 10) {
                        printf("Numero de discos invalido. Escolha entre 1 e 10.\n");
                        continue; 
                    }
                    
                    iniciar_jogo(&jogo, num_discos);
                    rodar_partida(&jogo, &inicio_historico, nome_jogador, num_discos);
                    
                    char jogar_novamente;
                    printf("\nDeseja jogar outra partida? (s/n): ");
                    scanf(" %c", &jogar_novamente);
                    while ((c = getchar()) != '\n' && c != EOF);

                    if (tolower(jogar_novamente) != 's') {
                        break; 
                    }
                }
                break;
            }
            case 2:
                exibir_historico(inicio_historico);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 3:
                buscar_historico(inicio_historico);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 4:
                printf("Saindo do jogo. Ate mais!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (escolha != 4);

    liberar_historico(&inicio_historico);
    return 0;
}