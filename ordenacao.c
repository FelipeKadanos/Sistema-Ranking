#include <ctype.h>
#include <stdlib.h>

#include "base.c"

void resetar_metricas(MetricasOrdenacao *metricas);
void iniciar_metricas(MetricasOrdenacao *metricas);
void finalizar_metricas(MetricasOrdenacao *metricas);
void registrar_movimentacao(MetricasOrdenacao *metricas, long quantidade);

/**
 * Compara dois textos sem diferenciar letras maiusculas de minusculas.
 * @param texto_a Primeiro texto da comparacao.
 * @param texto_b Segundo texto da comparacao.
 * @return int Valor negativo, zero ou positivo conforme a ordem dos textos.
 */
static int comparar_texto(const char *texto_a, const char *texto_b) {
    while (*texto_a != '\0' && *texto_b != '\0') {
        int letra_a = tolower((unsigned char)*texto_a);
        int letra_b = tolower((unsigned char)*texto_b);

        if (letra_a < letra_b) {
            return -1;
        }

        if (letra_a > letra_b) {
            return 1;
        }

        texto_a++;
        texto_b++;
    }

    if (*texto_a == '\0' && *texto_b == '\0') {
        return 0;
    }

    if (*texto_a == '\0') {
        return -1;
    }

    return 1;
}

/**
 * Compara dois alunos usando o criterio escolhido pelo usuario.
 * @param a Primeiro aluno.
 * @param b Segundo aluno.
 * @param criterio Regra usada para decidir a ordem.
 * @param metricas Estrutura que conta as comparacoes realizadas.
 * @return int Valor negativo, zero ou positivo conforme a ordem dos alunos.
 */
static int comparar_alunos(const Aluno *a,
                           const Aluno *b,
                           TipoCriterio criterio,
                           MetricasOrdenacao *metricas) {
    if (metricas != NULL) {
        metricas->comparacoes++;
    }

    /* Cada bloco abaixo segue exatamente a regra de ordenacao escolhida no menu. */
    if (criterio == CRITERIO_NOTA_CRESCENTE) {
        if (a->nota < b->nota) {
            return -1;
        }
        if (a->nota > b->nota) {
            return 1;
        }
        return 0;
    }

    if (criterio == CRITERIO_NOTA_DECRESCENTE) {
        if (a->nota > b->nota) {
            return -1;
        }
        if (a->nota < b->nota) {
            return 1;
        }
        return 0;
    }

    if (criterio == CRITERIO_NOME) {
        return comparar_texto(a->nome, b->nome);
    }

    if (criterio == CRITERIO_FALTAS) {
        if (a->faltas < b->faltas) {
            return -1;
        }
        if (a->faltas > b->faltas) {
            return 1;
        }
        return 0;
    }

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
}

/**
 * Troca a posicao de dois alunos no vetor.
 * @param a Ponteiro para o primeiro aluno.
 * @param b Ponteiro para o segundo aluno.
 * @param metricas Estrutura usada para contar as movimentacoes.
 * @return Nao retorna valor.
 */
static void trocar_alunos(Aluno *a, Aluno *b, MetricasOrdenacao *metricas) {
    Aluno temporario;

    if (a == b) {
        return;
    }

    temporario = *a;
    *a = *b;
    *b = temporario;
    registrar_movimentacao(metricas, 3);
}

/**
 * Ordena o vetor usando Bubble Sort.
 * @param alunos Vetor que sera ordenado.
 * @param quantidade Quantidade de alunos no vetor.
 * @param criterio Regra usada para comparar os alunos.
 * @param metricas Estrutura que recebera as metricas da execucao.
 * @return Nao retorna valor.
 */
static void bubble_sort(Aluno *alunos,
                        int quantidade,
                        TipoCriterio criterio,
                        MetricasOrdenacao *metricas) {
    int i;
    int j;

    iniciar_metricas(metricas);

    for (i = 0; i < quantidade - 1; i++) {
        int trocou = 0;

        for (j = 0; j < quantidade - 1 - i; j++) {
            if (comparar_alunos(&alunos[j], &alunos[j + 1], criterio, metricas) > 0) {
                trocar_alunos(&alunos[j], &alunos[j + 1], metricas);
                trocou = 1;
            }
        }

        /* Se nenhuma troca aconteceu, o vetor ja esta ordenado. */
        if (trocou == 0) {
            break;
        }
    }

    finalizar_metricas(metricas);
}

/**
 * Ordena o vetor usando Selection Sort.
 * @param alunos Vetor que sera ordenado.
 * @param quantidade Quantidade de alunos no vetor.
 * @param criterio Regra usada para comparar os alunos.
 * @param metricas Estrutura que recebera as metricas da execucao.
 * @return Nao retorna valor.
 */
static void selection_sort(Aluno *alunos,
                           int quantidade,
                           TipoCriterio criterio,
                           MetricasOrdenacao *metricas) {
    int i;
    int j;

    iniciar_metricas(metricas);

    for (i = 0; i < quantidade - 1; i++) {
        int menor = i;

        for (j = i + 1; j < quantidade; j++) {
            if (comparar_alunos(&alunos[j], &alunos[menor], criterio, metricas) < 0) {
                menor = j;
            }
        }

        trocar_alunos(&alunos[i], &alunos[menor], metricas);
    }

    finalizar_metricas(metricas);
}

/**
 * Ordena o vetor usando Insertion Sort.
 * @param alunos Vetor que sera ordenado.
 * @param quantidade Quantidade de alunos no vetor.
 * @param criterio Regra usada para comparar os alunos.
 * @param metricas Estrutura que recebera as metricas da execucao.
 * @return Nao retorna valor.
 */
static void insertion_sort(Aluno *alunos,
                           int quantidade,
                           TipoCriterio criterio,
                           MetricasOrdenacao *metricas) {
    int i;

    iniciar_metricas(metricas);

    for (i = 1; i < quantidade; i++) {
        Aluno chave = alunos[i];
        int j = i - 1;

        /* A chave guarda o item atual enquanto os maiores sao deslocados para a direita. */
        registrar_movimentacao(metricas, 1);

        while (j >= 0 && comparar_alunos(&alunos[j], &chave, criterio, metricas) > 0) {
            alunos[j + 1] = alunos[j];
            registrar_movimentacao(metricas, 1);
            j--;
        }

        alunos[j + 1] = chave;
        registrar_movimentacao(metricas, 1);
    }

    finalizar_metricas(metricas);
}

/**
 * Separa uma faixa do vetor em torno de um pivo para o Quick Sort.
 * @param alunos Vetor sendo ordenado.
 * @param inicio Inicio da faixa analisada.
 * @param fim Final da faixa analisada.
 * @param criterio Regra usada para comparar os alunos.
 * @param metricas Estrutura que recebe as metricas da execucao.
 * @return int Posicao final do pivo apos a particao.
 */
static int particionar(Aluno *alunos,
                       int inicio,
                       int fim,
                       TipoCriterio criterio,
                       MetricasOrdenacao *metricas) {
    Aluno pivo = alunos[fim];
    int i = inicio - 1;
    int j;

    registrar_movimentacao(metricas, 1);

    for (j = inicio; j < fim; j++) {
        if (comparar_alunos(&alunos[j], &pivo, criterio, metricas) <= 0) {
            i++;
            trocar_alunos(&alunos[i], &alunos[j], metricas);
        }
    }

    trocar_alunos(&alunos[i + 1], &alunos[fim], metricas);
    return i + 1;
}

/**
 * Ordena o vetor usando Quick Sort iterativo.
 * @param alunos Vetor que sera ordenado.
 * @param quantidade Quantidade de alunos no vetor.
 * @param criterio Regra usada para comparar os alunos.
 * @param metricas Estrutura que recebera as metricas da execucao.
 * @return int 1 se a ordenacao ocorrer ou 0 em caso de falha de memoria.
 */
static int quick_sort(Aluno *alunos,
                      int quantidade,
                      TipoCriterio criterio,
                      MetricasOrdenacao *metricas) {
    int *pilha_inicio;
    int *pilha_fim;
    int topo;

    iniciar_metricas(metricas);

    if (quantidade <= 1) {
        finalizar_metricas(metricas);
        return 1;
    }

    pilha_inicio = (int *)malloc((size_t)quantidade * sizeof(int));
    pilha_fim = (int *)malloc((size_t)quantidade * sizeof(int));

    if (pilha_inicio == NULL || pilha_fim == NULL) {
        free(pilha_inicio);
        free(pilha_fim);
        finalizar_metricas(metricas);
        return 0;
    }

    /* As duas pilhas guardam as faixas que ainda precisam ser particionadas. */
    topo = 0;
    pilha_inicio[topo] = 0;
    pilha_fim[topo] = quantidade - 1;

    while (topo >= 0) {
        int inicio = pilha_inicio[topo];
        int fim = pilha_fim[topo];
        int pivo;

        topo--;

        if (inicio >= fim) {
            continue;
        }

        pivo = particionar(alunos, inicio, fim, criterio, metricas);

        /* Cada nova faixa valida volta para a pilha para ser processada depois. */
        if (pivo - 1 > inicio) {
            topo++;
            pilha_inicio[topo] = inicio;
            pilha_fim[topo] = pivo - 1;
        }

        if (pivo + 1 < fim) {
            topo++;
            pilha_inicio[topo] = pivo + 1;
            pilha_fim[topo] = fim;
        }
    }

    free(pilha_inicio);
    free(pilha_fim);
    finalizar_metricas(metricas);
    return 1;
}

/**
 * Junta duas metades ja ordenadas durante o Merge Sort.
 * @param alunos Vetor principal com os alunos.
 * @param auxiliar Vetor auxiliar usado durante a juncao.
 * @param inicio Inicio da faixa.
 * @param meio Fim da metade esquerda.
 * @param fim Fim da metade direita.
 * @param criterio Regra usada para comparar os alunos.
 * @param metricas Estrutura que recebe as metricas da execucao.
 * @return Nao retorna valor.
 */
static void intercalar(Aluno *alunos,
                       Aluno *auxiliar,
                       int inicio,
                       int meio,
                       int fim,
                       TipoCriterio criterio,
                       MetricasOrdenacao *metricas) {
    int i = inicio;
    int j = meio + 1;
    int k = inicio;

    while (i <= meio && j <= fim) {
        if (comparar_alunos(&alunos[i], &alunos[j], criterio, metricas) <= 0) {
            auxiliar[k] = alunos[i];
            i++;
        } else {
            auxiliar[k] = alunos[j];
            j++;
        }

        registrar_movimentacao(metricas, 1);
        k++;
    }

    while (i <= meio) {
        auxiliar[k] = alunos[i];
        registrar_movimentacao(metricas, 1);
        i++;
        k++;
    }

    while (j <= fim) {
        auxiliar[k] = alunos[j];
        registrar_movimentacao(metricas, 1);
        j++;
        k++;
    }

    /* Depois de intercalar no vetor auxiliar, os valores voltam para o vetor principal. */
    for (k = inicio; k <= fim; k++) {
        alunos[k] = auxiliar[k];
        registrar_movimentacao(metricas, 1);
    }
}

/**
 * Ordena o vetor usando Merge Sort iterativo.
 * @param alunos Vetor que sera ordenado.
 * @param quantidade Quantidade de alunos no vetor.
 * @param criterio Regra usada para comparar os alunos.
 * @param metricas Estrutura que recebera as metricas da execucao.
 * @return int 1 se a ordenacao ocorrer ou 0 em caso de falha de memoria.
 */
static int merge_sort(Aluno *alunos,
                      int quantidade,
                      TipoCriterio criterio,
                      MetricasOrdenacao *metricas) {
    Aluno *auxiliar;
    int tamanho_bloco;

    iniciar_metricas(metricas);

    if (quantidade <= 1) {
        finalizar_metricas(metricas);
        return 1;
    }

    auxiliar = (Aluno *)malloc((size_t)quantidade * sizeof(Aluno));
    if (auxiliar == NULL) {
        finalizar_metricas(metricas);
        return 0;
    }

    tamanho_bloco = 1;

    /* O tamanho do bloco dobra a cada passada para juntar partes cada vez maiores. */
    while (tamanho_bloco < quantidade) {
        int inicio = 0;

        while (inicio < quantidade - tamanho_bloco) {
            int meio = inicio + tamanho_bloco - 1;
            int fim = inicio + (2 * tamanho_bloco) - 1;

            if (fim >= quantidade) {
                fim = quantidade - 1;
            }

            intercalar(alunos, auxiliar, inicio, meio, fim, criterio, metricas);
            inicio = inicio + (2 * tamanho_bloco);
        }

        tamanho_bloco = tamanho_bloco * 2;
    }

    free(auxiliar);
    finalizar_metricas(metricas);
    return 1;
}

/**
 * Escolhe o algoritmo pedido pelo usuario e executa a ordenacao correspondente.
 * @param algoritmo Algoritmo selecionado no menu.
 * @param alunos Vetor que sera ordenado.
 * @param quantidade Quantidade de alunos no vetor.
 * @param criterio Regra usada para comparar os alunos.
 * @param metricas Estrutura que recebera as metricas da execucao.
 * @return int 1 se a ordenacao ocorrer ou 0 em caso de erro.
 */
int executar_ordenacao(TipoAlgoritmo algoritmo,
                       Aluno *alunos,
                       int quantidade,
                       TipoCriterio criterio,
                       MetricasOrdenacao *metricas) {
    if (alunos == NULL || quantidade <= 0 || metricas == NULL) {
        return 0;
    }

    if (algoritmo == ALGORITMO_BUBBLE) {
        bubble_sort(alunos, quantidade, criterio, metricas);
        return 1;
    }

    if (algoritmo == ALGORITMO_SELECTION) {
        selection_sort(alunos, quantidade, criterio, metricas);
        return 1;
    }

    if (algoritmo == ALGORITMO_INSERTION) {
        insertion_sort(alunos, quantidade, criterio, metricas);
        return 1;
    }

    if (algoritmo == ALGORITMO_QUICK) {
        return quick_sort(alunos, quantidade, criterio, metricas);
    }

    if (algoritmo == ALGORITMO_MERGE) {
        return merge_sort(alunos, quantidade, criterio, metricas);
    }

    resetar_metricas(metricas);
    return 0;
}
