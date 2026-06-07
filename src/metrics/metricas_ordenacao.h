#ifndef METRICAS_ORDENACAO_H
#define METRICAS_ORDENACAO_H

#include <time.h>

typedef struct {
    long comparacoes;
    long movimentacoes;
    double tempo_execucao_ms;
    clock_t inicio_clock;
} metricas_ordenacao;

void resetar_metricas(metricas_ordenacao *metricas);
void iniciar_temporizacao(metricas_ordenacao *metricas);
void finalizar_temporizacao(metricas_ordenacao *metricas);

#endif
