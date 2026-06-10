#include <time.h>

#define ALUNO_NOME_TAMANHO 50

typedef struct {
    int matricula;
    char nome[ALUNO_NOME_TAMANHO];
    float nota;
    int faltas;
} Aluno;

typedef struct {
    long comparacoes;
    long movimentacoes;
    double tempo_execucao_ms;
    clock_t inicio_clock;
} metricas_ordenacao;

typedef enum {
    NOTA_CRESCENTE = 1,
    NOTA_DECRESCENTE,
    NOME,
    FALTAS,
    COMBINADO
} tipo_ordenacao;

int comparar_alunos(const Aluno *a,
                    const Aluno *b,
                    tipo_ordenacao criterio,
                    metricas_ordenacao *metricas);
void resetar_metricas(metricas_ordenacao *metricas);
void iniciar_temporizacao(metricas_ordenacao *metricas);
void finalizar_temporizacao(metricas_ordenacao *metricas);

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
