#include <stdio.h>

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

void resetar_metricas(metricas_ordenacao *metricas);
void iniciar_temporizacao(metricas_ordenacao *metricas);
void finalizar_temporizacao(metricas_ordenacao *metricas);

void insertion_sort(Aluno *alunos,
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

    printf("Insertion Sort ainda nao implementado.\n");
}
