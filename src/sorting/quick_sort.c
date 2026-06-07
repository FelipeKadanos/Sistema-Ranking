#include "quick_sort.h"

#include "comparador.h"

static void trocar_alunos(Aluno *a, Aluno *b, metricas_ordenacao *metricas) {
    Aluno temporario;

    if (a == b) {
        return;
    }

    temporario = *a;
    *a = *b;
    *b = temporario;

    if (metricas != NULL) {
        metricas->movimentacoes += 3;
    }
}

static int particionar(Aluno *alunos,
                       int inicio,
                       int fim,
                       tipo_ordenacao criterio,
                       metricas_ordenacao *metricas) {
    Aluno pivo = alunos[fim];
    int i = inicio - 1;
    int j;

    for (j = inicio; j < fim; j++) {
        if (comparar_alunos(&alunos[j], &pivo, criterio, metricas) <= 0) {
            i++;
            trocar_alunos(&alunos[i], &alunos[j], metricas);
        }
    }

    trocar_alunos(&alunos[i + 1], &alunos[fim], metricas);
    return i + 1;
}

static void quick_sort_recursivo(Aluno *alunos,
                                 int inicio,
                                 int fim,
                                 tipo_ordenacao criterio,
                                 metricas_ordenacao *metricas) {
    int indice_pivo;

    if (inicio >= fim) {
        return;
    }

    indice_pivo = particionar(alunos, inicio, fim, criterio, metricas);
    quick_sort_recursivo(alunos, inicio, indice_pivo - 1, criterio, metricas);
    quick_sort_recursivo(alunos, indice_pivo + 1, fim, criterio, metricas);
}

void quick_sort(Aluno *alunos,
                int quantidade,
                tipo_ordenacao criterio,
                metricas_ordenacao *metricas) {
    if (metricas == NULL) {
        return;
    }

    resetar_metricas(metricas);
    iniciar_temporizacao(metricas);

    if (alunos != NULL && quantidade > 1) {
        quick_sort_recursivo(alunos, 0, quantidade - 1, criterio, metricas);
    }

    finalizar_temporizacao(metricas);
}
