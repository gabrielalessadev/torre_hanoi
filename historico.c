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
    printf("-----------------------------\n");
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