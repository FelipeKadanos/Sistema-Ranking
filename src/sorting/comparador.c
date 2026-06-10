#include <string.h>

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

static int comparar_texto(const char *texto_a, const char *texto_b) {
    int resultado = strcmp(texto_a, texto_b);

    if (resultado < 0) {
        return -1;
    }

    if (resultado > 0) {
        return 1;
    }

    return 0;
}

int comparar_alunos(const Aluno *a,
                    const Aluno *b,
                    tipo_ordenacao criterio,
                    metricas_ordenacao *metricas) {
    if (metricas != NULL) {
        metricas->comparacoes++;
    }

    switch (criterio) {
        case NOTA_CRESCENTE:
            if (a->nota < b->nota) {
                return -1;
            }
            if (a->nota > b->nota) {
                return 1;
            }
            return 0;
        case NOTA_DECRESCENTE:
            if (a->nota > b->nota) {
                return -1;
            }
            if (a->nota < b->nota) {
                return 1;
            }
            return 0;
        case NOME:
            return comparar_texto(a->nome, b->nome);
        case FALTAS:
            if (a->faltas < b->faltas) {
                return -1;
            }
            if (a->faltas > b->faltas) {
                return 1;
            }
            return 0;
        case COMBINADO:
            if (a->nota > b->nota) {
                return -1;
            }
            if (a->nota < b->nota) {
                return 1;
            }
            if (a->faltas < b->faltas) {
                return -1;
            }
            if (a->faltas > b->faltas) {
                return 1;
            }
            return comparar_texto(a->nome, b->nome);
        default:
            return 0;
    }
}
