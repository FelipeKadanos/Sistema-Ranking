#include <time.h>

/* Quantidade maxima de caracteres armazenados no nome do aluno. */
#define NOME_TAMANHO 50

/* Tamanho maximo usado para caminhos de arquivos digitados pelo usuario. */
#define CAMINHO_TAMANHO 260

/**
 * Representa um aluno com os campos exigidos pelo trabalho.
 * matricula identifica o aluno, nome armazena o texto do nome,
 * nota guarda o desempenho e faltas registra a quantidade de ausencias.
 */
typedef struct {
    int matricula;
    char nome[NOME_TAMANHO];
    float nota;
    int faltas;
} Aluno;

/**
 * Guarda as metricas geradas por um algoritmo de ordenacao.
 * comparacoes e movimentacoes contam operacoes e inicio
 * ajuda a calcular o tempo total da execucao.
 */
typedef struct {
    long comparacoes;
    long movimentacoes;
    double tempo_execucao_ms;
    clock_t inicio;
} MetricasOrdenacao;

/**
 * Define os criterios de ordenacao aceitos pelo sistema.
 */
typedef enum {
    CRITERIO_NOTA_CRESCENTE = 1,
    CRITERIO_NOTA_DECRESCENTE,
    CRITERIO_NOME,
    CRITERIO_FALTAS,
    CRITERIO_COMBINADO
} TipoCriterio;

/**
 * Define os algoritmos de ordenacao disponiveis no menu.
 */
typedef enum {
    ALGORITMO_BUBBLE = 1,
    ALGORITMO_SELECTION,
    ALGORITMO_INSERTION,
    ALGORITMO_QUICK,
    ALGORITMO_MERGE
} TipoAlgoritmo;
