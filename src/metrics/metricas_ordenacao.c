#include "metricas_ordenacao.h"

void resetar_metricas(metricas_ordenacao *metricas) {
    if (metricas == NULL) {
        return;
    }

    metricas->comparacoes = 0;
    metricas->movimentacoes = 0;
    metricas->tempo_execucao_ms = 0.0;
    metricas->inicio_clock = 0;
}

void iniciar_temporizacao(metricas_ordenacao *metricas) {
    if (metricas == NULL) {
        return;
    }

    metricas->inicio_clock = clock();
}

void finalizar_temporizacao(metricas_ordenacao *metricas) {
    clock_t fim_clock;

    if (metricas == NULL) {
        return;
    }

    fim_clock = clock();
    metricas->tempo_execucao_ms =
        ((double)(fim_clock - metricas->inicio_clock) * 1000.0) / CLOCKS_PER_SEC;
}
