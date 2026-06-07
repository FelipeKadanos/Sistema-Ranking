#include "merge_sort.h"

#include <stdio.h>

void merge_sort(Aluno *alunos,
                int quantidade,
                tipo_ordenacao criterio,
                metricas_ordenacao *metricas) {
    (void)alunos;
    (void)quantidade;
    (void)criterio;

    if (metricas != NULL) {
        resetar_metricas(metricas);
        iniciar_temporizacao(metricas);
        finalizar_temporizacao(metricas);
    }

    printf("Merge Sort ainda nao implementado.\n");
}
