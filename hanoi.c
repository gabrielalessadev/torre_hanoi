#include "hanoi.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

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

    int altura_maxima = 0;
    for (int i = 0; i < NUM_PINOS; i++) {
        int altura_atual = 0;
        Disco* atual = jogo->pinos[i].topo;
        while (atual != NULL) {
            altura_atual++;
            atual = atual->proximo;
        }
        if (altura_atual > altura_maxima) {
            altura_maxima = altura_atual;
        }
    }

    int largura_pino = (jogo->num_discos * 2) + 3;

    for (int h = altura_maxima; h >= 1; h--) {
        for (int p = 0; p < NUM_PINOS; p++) {
            int altura_pino_atual = 0;
            Disco* temp = jogo->pinos[p].topo;
            while(temp != NULL) {
                altura_pino_atual++;
                temp = temp->proximo;
            }

            Disco* disco_na_altura_h = NULL;
            if (h <= altura_pino_atual) {
                disco_na_altura_h = jogo->pinos[p].topo;
                for (int i = 0; i < altura_pino_atual - h; ++i) {
                    if (disco_na_altura_h) {
                         disco_na_altura_h = disco_na_altura_h->proximo;
                    }
                }
            }

            if (disco_na_altura_h != NULL) {
                int tamanho_disco = disco_na_altura_h->tamanho;
                int largura_desenho_disco = (tamanho_disco * 2) + 3;
                int preenchimento = (largura_pino - largura_desenho_disco) / 2;

                for(int i = 0; i < preenchimento; i++) printf(" ");
                printf("(");
                for(int i = 0; i < tamanho_disco; i++) printf("=");
                printf("%d", tamanho_disco);
                for(int i = 0; i < tamanho_disco; i++) printf("=");
                printf(")");
                for(int i = 0; i < preenchimento; i++) printf(" ");
            } else {
                int preenchimento_haste = (largura_pino - 1) / 2;
                for(int i = 0; i < preenchimento_haste; i++) printf(" ");
                printf("|");
                for(int i = 0; i < preenchimento_haste; i++) printf(" ");
            }
            printf("  ");
        }
        printf("\n");
    }

    for (int p = 0; p < NUM_PINOS; p++) {
        for (int i = 0; i < largura_pino; i++) printf("-");
        printf("  ");
    }
    printf("\n");

    for (int p = 0; p < NUM_PINOS; p++) {
        int preenchimento_letra = (largura_pino - 1) / 2;
        for (int i = 0; i < preenchimento_letra; i++) printf(" ");
        printf("%c", 'A' + p);
        for (int i = 0; i < preenchimento_letra; i++) printf(" ");
        printf("  ");
    }
    printf("\n");
}
int verificar_vitoria(JogoHanoi* jogo) {
    
    if (!esta_vazia(&jogo->pinos[0])) {
        return 0; 
    }
    if (esta_vazia(&jogo->pinos[1])) {
        int contador = 0;
        Disco* atual = jogo->pinos[2].topo; 
        while (atual != NULL) {
            contador++;
            atual = atual->proximo;
        }
        if (contador == jogo->num_discos) {
            return 1; 
        }
    }

    if (esta_vazia(&jogo->pinos[2])) {
        int contador = 0;
        Disco* atual = jogo->pinos[1].topo; 
        while (atual != NULL) {
            contador++;
            atual = atual->proximo;
        }
        if (contador == jogo->num_discos) {
            return 1; 
        }
    }
    return 0;
}

void encontrar_prox_movimento_otimo(JogoHanoi* jogo, int* origem, int* destino) {
    int pares_par[3][2] = {{0, 1}, {0, 2}, {1, 2}};
    int pares_impar[3][2] = {{0, 2}, {0, 1}, {1, 2}};
    int (*pares)[2] = (jogo->num_discos % 2 == 0) ? pares_par : pares_impar;

    int p1 = pares[jogo->movimentos % 3][0];
    int p2 = pares[jogo->movimentos % 3][1];
    
    int t1 = esta_vazia(&jogo->pinos[p1]) ? INT_MAX : jogo->pinos[p1].topo->tamanho;
    int t2 = esta_vazia(&jogo->pinos[p2]) ? INT_MAX : jogo->pinos[p2].topo->tamanho;
    if (t1 < t2) { *origem = p1; *destino = p2; } else { *origem = p2; *destino = p1; }
}