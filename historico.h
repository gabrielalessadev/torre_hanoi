#ifndef HISTORICO_H
#define HISTORICO_H

#include <time.h>

#define TAMANHO_MAX_NOME 50
#define ARQUIVO_HISTORICO "historico_partidas.txt"

typedef struct RegistroPartida {
    int movimentos;
    char nome_jogador[TAMANHO_MAX_NOME];
    int num_discos;
    time_t data_fim;
    struct RegistroPartida* proximo;
} RegistroPartida;

void adicionar_registro(RegistroPartida** inicio_lista, int movimentos, const char* nome_jogador, int num_discos);
void salvar_historico_em_arquivo(RegistroPartida* inicio_lista);
void carregar_historico_do_arquivo(RegistroPartida** inicio_lista);
void exibir_historico(RegistroPartida* inicio_lista);
void liberar_historico(RegistroPartida** inicio_lista);
void buscar_historico(RegistroPartida* inicio_lista);

#endif 