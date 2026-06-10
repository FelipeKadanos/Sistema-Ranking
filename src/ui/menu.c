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

void imprimir_aluno(const Aluno *aluno);

void exibir_menu(void) {
    printf("\n===== Sistema de Ranking de Desempenho Academico =====\n");
    printf("1 - Carregar CSV\n");
    printf("2 - Escolher criterio de ordenacao\n");
    printf("3 - Escolher algoritmo\n");
    printf("4 - Executar ordenacao\n");
    printf("5 - Mostrar Top 10 alunos\n");
    printf("6 - Mostrar metricas\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

void exibir_criterios(void) {
    printf("\nCriterios disponiveis:\n");
    printf("1 - Nota crescente\n");
    printf("2 - Nota decrescente\n");
    printf("3 - Nome\n");
    printf("4 - Faltas\n");
    printf("5 - Combinado\n");
    printf("Opcao: ");
}

void exibir_algoritmos(void) {
    printf("\nAlgoritmos disponiveis:\n");
    printf("1 - Quick Sort\n");
    printf("2 - Bubble Sort\n");
    printf("3 - Insertion Sort\n");
    printf("4 - Selection Sort\n");
    printf("5 - Merge Sort\n");
    printf("Opcao: ");
}

void exibir_top_alunos(const Aluno *alunos, int quantidade, int limite) {
    int indice;
    int quantidade_exibida = quantidade < limite ? quantidade : limite;

    if (alunos == NULL || quantidade <= 0) {
        printf("Nenhum aluno carregado.\n");
        return;
    }

    printf("\nMatric | Nome                           | Nota | Ft\n");
    printf("----------------------------------------------------\n");
    for (indice = 0; indice < quantidade_exibida; indice++) {
        imprimir_aluno(&alunos[indice]);
    }
}

void exibir_metricas(const metricas_ordenacao *metricas) {
    if (metricas == NULL) {
        printf("Metricas indisponiveis.\n");
        return;
    }

    printf("\nMetricas da ultima ordenacao:\n");
    printf("Comparacoes   : %ld\n", metricas->comparacoes);
    printf("Movimentacoes : %ld\n", metricas->movimentacoes);
    printf("Tempo (ms)    : %.3f\n", metricas->tempo_execucao_ms);
}
