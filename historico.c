#include "historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void adicionar_registro(RegistroPartida** inicio_lista, int movimentos, const char* nome_jogador, int num_discos) {
    RegistroPartida* novo_registro = (RegistroPartida*)malloc(sizeof(RegistroPartida));
    if (novo_registro == NULL) {
        perror("Erro ao alocar registro de historico");
        exit(EXIT_FAILURE);
    }
    novo_registro->movimentos = movimentos;
    strncpy(novo_registro->nome_jogador, nome_jogador, TAMANHO_MAX_NOME - 1);
    novo_registro->nome_jogador[TAMANHO_MAX_NOME - 1] = '\0';
    novo_registro->num_discos = num_discos;
    novo_registro->data_fim = time(NULL);

    novo_registro->proximo = *inicio_lista;
    *inicio_lista = novo_registro;
}

void salvar_historico_em_arquivo(RegistroPartida* inicio_lista) {
    FILE* arquivo = fopen(ARQUIVO_HISTORICO, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de historico para escrita");
        return;
    }
    RegistroPartida* atual = inicio_lista;
    while (atual != NULL) {
        fprintf(arquivo, "%d;%s;%d;%ld\n", atual->movimentos, atual->nome_jogador, atual->num_discos, (long)atual->data_fim);
        atual = atual->proximo;
    }
    fclose(arquivo);
}
void carregar_historico_do_arquivo(RegistroPartida** inicio_lista) {
    FILE* arquivo = fopen(ARQUIVO_HISTORICO, "r");
    if (arquivo == NULL) { return; }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int movimentos, num_discos;
        char nome_jogador[TAMANHO_MAX_NOME];
        long data_fim_long;
        
        if (sscanf(linha, "%d;%49[^;];%d;%ld", &movimentos, nome_jogador, &num_discos, &data_fim_long) == 4) {
            adicionar_registro(inicio_lista, movimentos, nome_jogador, num_discos);
            if (*inicio_lista != NULL) {
                (*inicio_lista)->data_fim = (time_t)data_fim_long;
            }
        }
    }
    fclose(arquivo);
}

void exibir_historico(RegistroPartida* inicio_lista) {
    if (inicio_lista == NULL) {
        printf("Nenhum historico de partida encontrado.\n");
        return;
    }
    printf("\n Historico de Partidas \n");
    RegistroPartida* atual = inicio_lista;
    while (atual != NULL) {
        char data_str[64];
        strftime(data_str, sizeof(data_str), "%d/%m/%Y %H:%M:%S", localtime(&atual->data_fim));
        printf("Jogador: %s, Discos: %d, Movimentos: %d, Data: %s\n",
               atual->nome_jogador, atual->num_discos, atual->movimentos, data_str);
        atual = atual->proximo;
    }
}

void liberar_historico(RegistroPartida** inicio_lista) {
    RegistroPartida* atual = *inicio_lista;
    RegistroPartida* proximo_registro;
    while (atual != NULL) {
        proximo_registro = atual->proximo;
        free(atual);
        atual = proximo_registro;
    }
    *inicio_lista = NULL;
}

void buscar_historico(RegistroPartida* inicio_lista) {
    if (inicio_lista == NULL) {
        printf("Nenhum historico para buscar.\n");
        return;
    }

    int escolha;
    printf("\nBuscar historico por:\n");
    printf("1. Nome do jogador\n");
    printf("2. Data (formato DD/MM/AAAA)\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &escolha) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Opcao invalida.\n");
        return;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    char termo_busca[TAMANHO_MAX_NOME];
    RegistroPartida* atual = inicio_lista;
    int encontrado = 0;

    switch (escolha) {
        case 1:
            printf("Digite o nome do jogador: ");
            fgets(termo_busca, sizeof(termo_busca), stdin);
            termo_busca[strcspn(termo_busca, "\n")] = 0;
            printf("\n Resultados da Busca por Nome: '%s'\n", termo_busca);
            while (atual != NULL) {
                if (strstr(atual->nome_jogador, termo_busca) != NULL) {
                    char data_str[64];
                    strftime(data_str, sizeof(data_str), "%d/%m/%Y %H:%M:%S", localtime(&atual->data_fim));
                    printf("Jogador: %s, Discos: %d, Movimentos: %d, Data/Hora: %s\n",
                           atual->nome_jogador, atual->num_discos, atual->movimentos, data_str);
                    encontrado = 1;
                }
                atual = atual->proximo;
            }
            break;

        case 2:
            printf("Digite a data (DD/MM/AAAA): ");
            fgets(termo_busca, sizeof(termo_busca), stdin);
            termo_busca[strcspn(termo_busca, "\n")] = 0;

            printf("\n Resultados da Busca por Data: '%s'\n", termo_busca);
            while (atual != NULL) {
                char data_registro[11];
                strftime(data_registro, sizeof(data_registro), "%d/%m/%Y", localtime(&atual->data_fim));
                
                if (strcmp(data_registro, termo_busca) == 0) {
                    char data_str_completa[64];
                    strftime(data_str_completa, sizeof(data_str_completa), "%d/%m/%Y %H:%M:%S", localtime(&atual->data_fim));
                    printf("Jogador: %s, Discos: %d, Movimentos: %d, Data/Hora: %s\n",
                           atual->nome_jogador, atual->num_discos, atual->movimentos, data_str_completa);
                    encontrado = 1;
                }
                atual = atual->proximo;
            }
            break;

        default:
            printf("Opcao invalida.\n");
            break;
    }

    if (!encontrado) {
        printf("Nenhum registro encontrado para a busca.\n");
    }
}