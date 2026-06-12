#include "base.c"

/**
 * Zera todas as metricas antes de uma nova ordenacao.
 * @param metricas Ponteiro para a estrutura de metricas que sera reiniciada.
 * @return Nao retorna valor.
 */
void resetar_metricas(MetricasOrdenacao *metricas) {
    if (metricas == NULL) {
        return;
    }

    metricas->comparacoes = 0;
    metricas->movimentacoes = 0;
    metricas->tempo_execucao_ms = 0.0;
    metricas->inicio = 0;
}

/**
 * Prepara as metricas e marca o instante inicial da ordenacao.
 * @param metricas Ponteiro para a estrutura de metricas da execucao atual.
 * @return Nao retorna valor.
 */
void iniciar_metricas(MetricasOrdenacao *metricas) {
    resetar_metricas(metricas);

    if (metricas != NULL) {
        metricas->inicio = clock();
    }
}

/**
 * Calcula o tempo total gasto desde o inicio da ordenacao.
 * @param metricas Ponteiro para a estrutura de metricas que recebera o tempo final.
 * @return Nao retorna valor.
 */
void finalizar_metricas(MetricasOrdenacao *metricas) {
    clock_t fim;

    if (metricas == NULL) {
        return;
    }

    fim = clock();
    metricas->tempo_execucao_ms =
        ((double)(fim - metricas->inicio) * 1000.0) / CLOCKS_PER_SEC;
}

/**
 * Soma a quantidade informada ao contador de movimentacoes.
 * @param metricas Ponteiro para a estrutura de metricas da ordenacao.
 * @param quantidade Valor que sera somado ao total de movimentacoes.
 * @return Nao retorna valor.
 */
void registrar_movimentacao(MetricasOrdenacao *metricas, long quantidade) {
    if (metricas != NULL) {
        metricas->movimentacoes += quantidade;
    }
}
