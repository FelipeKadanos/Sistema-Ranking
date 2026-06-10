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

typedef enum {
    QUICK_SORT = 1,
    BUBBLE_SORT,
    INSERTION_SORT,
    SELECTION_SORT,
    MERGE_SORT
} algoritmo_ordenacao;

void resetar_metricas(metricas_ordenacao *metricas);
void quick_sort(Aluno *alunos,
                int quantidade,
                tipo_ordenacao criterio,
                metricas_ordenacao *metricas);
void bubble_sort(Aluno *alunos,
                 int quantidade,
                 tipo_ordenacao criterio,
                 metricas_ordenacao *metricas);
void insertion_sort(Aluno *alunos,
                    int quantidade,
                    tipo_ordenacao criterio,
                    metricas_ordenacao *metricas);
void selection_sort(Aluno *alunos,
                    int quantidade,
                    tipo_ordenacao criterio,
                    metricas_ordenacao *metricas);
void merge_sort(Aluno *alunos,
                int quantidade,
                tipo_ordenacao criterio,
                metricas_ordenacao *metricas);

const char *obter_nome_criterio(tipo_ordenacao criterio) {
    switch (criterio) {
        case NOTA_CRESCENTE:
            return "Nota crescente";
        case NOTA_DECRESCENTE:
            return "Nota decrescente";
        case NOME:
            return "Nome";
        case FALTAS:
            return "Faltas";
        case COMBINADO:
            return "Combinado";
        default:
            return "Desconhecido";
    }
}

const char *obter_nome_algoritmo(algoritmo_ordenacao algoritmo) {
    switch (algoritmo) {
        case QUICK_SORT:
            return "Quick Sort";
        case BUBBLE_SORT:
            return "Bubble Sort";
        case INSERTION_SORT:
            return "Insertion Sort";
        case SELECTION_SORT:
            return "Selection Sort";
        case MERGE_SORT:
            return "Merge Sort";
        default:
            return "Desconhecido";
    }
}

void executar_ordenacao(algoritmo_ordenacao algoritmo,
                        Aluno *alunos,
                        int quantidade,
                        tipo_ordenacao criterio,
                        metricas_ordenacao *metricas) {
    switch (algoritmo) {
        case QUICK_SORT:
            quick_sort(alunos, quantidade, criterio, metricas);
            break;
        case BUBBLE_SORT:
            bubble_sort(alunos, quantidade, criterio, metricas);
            break;
        case INSERTION_SORT:
            insertion_sort(alunos, quantidade, criterio, metricas);
            break;
        case SELECTION_SORT:
            selection_sort(alunos, quantidade, criterio, metricas);
            break;
        case MERGE_SORT:
            merge_sort(alunos, quantidade, criterio, metricas);
            break;
        default:
            if (metricas != NULL) {
                resetar_metricas(metricas);
            }
            break;
    }
}
