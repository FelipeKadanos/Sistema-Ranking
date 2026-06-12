#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "base.c"

void resetar_metricas(MetricasOrdenacao *metricas);

int ui_ler_inteiro(const char *mensagem);
void ui_ler_texto(const char *mensagem, char *buffer, size_t tamanho);
void ui_mostrar_menu(int quantidade,
                     int tamanho_atual,
                     TipoCriterio criterio_atual,
                     TipoAlgoritmo algoritmo_atual,
                     int ordenado);
void ui_mostrar_tamanhos_geracao(void);
void ui_mostrar_criterios(void);
void ui_mostrar_algoritmos(void);
void ui_mostrar_top_alunos(const Aluno *alunos, int quantidade);
void ui_mostrar_metricas(const MetricasOrdenacao *metricas);
void ui_mostrar_mensagem(const char *mensagem);
void ui_mostrar_erro(const char *mensagem);
void ui_mostrar_dados_gerados(int quantidade);
void ui_mostrar_tamanho_escolhido(int quantidade);
void ui_mostrar_arquivo_salvo(const char *caminho);
void ui_mostrar_criterio_escolhido(TipoCriterio criterio);
void ui_mostrar_algoritmo_escolhido(TipoAlgoritmo algoritmo);
void ui_mostrar_ordenacao_concluida(TipoAlgoritmo algoritmo, TipoCriterio criterio);
void ui_mostrar_titulo_comparacao(TipoCriterio criterio);
void ui_mostrar_nome_algoritmo(TipoAlgoritmo algoritmo);

Aluno *gerar_alunos_automaticamente(int quantidade);
int salvar_alunos_csv(const char *caminho, const Aluno *alunos, int quantidade);
Aluno *copiar_alunos(const Aluno *origem, int quantidade);
void liberar_alunos(Aluno **alunos, int *quantidade);

int executar_ordenacao(TipoAlgoritmo algoritmo,
                       Aluno *alunos,
                       int quantidade,
                       TipoCriterio criterio,
                       MetricasOrdenacao *metricas);

/**
 * Permite ao usuario escolher um dos tres tamanhos aceitos no projeto.
 * @param quantidade_atual Ponteiro para a quantidade configurada no sistema.
 * @return Nao retorna valor.
 */
static void escolher_quantidade_interativa(int *quantidade_atual) {
    int opcao;

    ui_mostrar_tamanhos_geracao();
    opcao = ui_ler_inteiro("Opcao: ");

    if (opcao == 1) {
        *quantidade_atual = 100;
    } else if (opcao == 2) {
        *quantidade_atual = 1000;
    } else if (opcao == 3) {
        *quantidade_atual = 10000;
    } else {
        ui_mostrar_erro("Opcao invalida.");
        return;
    }

    /* A quantidade fica limitada aos tres tamanhos do escopo para manter o sistema simples. */
    ui_mostrar_tamanho_escolhido(*quantidade_atual);
}

/**
 * Gera automaticamente os alunos e coloca o novo vetor em memoria.
 * @param alunos Ponteiro para o vetor atual de alunos.
 * @param quantidade Ponteiro para a quantidade atual de alunos carregados.
 * @param quantidade_geracao Quantidade configurada para a geracao automatica.
 * @param ordenado Ponteiro para o estado de ordenacao atual.
 * @param ultima_metrica Ponteiro para as metricas da ultima ordenacao.
 * @return Nao retorna valor.
 */
static void gerar_dados_interativo(Aluno **alunos,
                                   int *quantidade,
                                   int quantidade_geracao,
                                   int *ordenado,
                                   MetricasOrdenacao *ultima_metrica) {
    Aluno *novos_alunos;

    novos_alunos = gerar_alunos_automaticamente(quantidade_geracao);
    if (novos_alunos == NULL) {
        ui_mostrar_erro("Nao foi possivel gerar os dados.");
        return;
    }

    /* A geracao automatica ja entrega os alunos em memoria para o usuario seguir direto no menu. */
    liberar_alunos(alunos, quantidade);
    *alunos = novos_alunos;
    *quantidade = quantidade_geracao;
    *ordenado = 0;
    resetar_metricas(ultima_metrica);
    ui_mostrar_dados_gerados(*quantidade);
}

/**
 * Le do usuario o criterio de ordenacao desejado.
 * @param criterio_atual Ponteiro para o criterio atual do sistema.
 * @param ordenado Ponteiro para o estado de ordenacao atual.
 * @return Nao retorna valor.
 */
static void escolher_criterio_interativo(TipoCriterio *criterio_atual, int *ordenado) {
    int opcao;

    ui_mostrar_criterios();
    opcao = ui_ler_inteiro("Opcao: ");

    if (opcao < CRITERIO_NOTA_CRESCENTE || opcao > CRITERIO_COMBINADO) {
        ui_mostrar_erro("Criterio invalido.");
        return;
    }

    *criterio_atual = (TipoCriterio)opcao;
    *ordenado = 0;
    ui_mostrar_criterio_escolhido(*criterio_atual);
}

/**
 * Le do usuario o algoritmo de ordenacao desejado.
 * @param algoritmo_atual Ponteiro para o algoritmo atual do sistema.
 * @return Nao retorna valor.
 */
static void escolher_algoritmo_interativo(TipoAlgoritmo *algoritmo_atual) {
    int opcao;

    ui_mostrar_algoritmos();
    opcao = ui_ler_inteiro("Opcao: ");

    if (opcao < ALGORITMO_BUBBLE || opcao > ALGORITMO_MERGE) {
        ui_mostrar_erro("Algoritmo invalido.");
        return;
    }

    *algoritmo_atual = (TipoAlgoritmo)opcao;
    ui_mostrar_algoritmo_escolhido(*algoritmo_atual);
}

/**
 * Executa a ordenacao principal do sistema com o algoritmo e criterio atuais.
 * @param alunos Vetor de alunos carregado em memoria.
 * @param quantidade Quantidade atual de alunos.
 * @param criterio_atual Criterio escolhido pelo usuario.
 * @param algoritmo_atual Algoritmo escolhido pelo usuario.
 * @param ordenado Ponteiro para o estado de ordenacao atual.
 * @param ultima_metrica Ponteiro para as metricas da execucao.
 * @return Nao retorna valor.
 */
static void ordenar_dados_interativo(Aluno *alunos,
                                     int quantidade,
                                     TipoCriterio criterio_atual,
                                     TipoAlgoritmo algoritmo_atual,
                                     int *ordenado,
                                     MetricasOrdenacao *ultima_metrica) {
    int sucesso;

    if (alunos == NULL || quantidade == 0) {
        ui_mostrar_erro("Gere dados antes de ordenar.");
        return;
    }

    sucesso = executar_ordenacao(algoritmo_atual,
                                 alunos,
                                 quantidade,
                                 criterio_atual,
                                 ultima_metrica);
    if (sucesso == 0) {
        ui_mostrar_erro("Nao foi possivel executar a ordenacao.");
        return;
    }

    *ordenado = 1;
    ui_mostrar_ordenacao_concluida(algoritmo_atual, criterio_atual);
    ui_mostrar_metricas(ultima_metrica);
}

/**
 * Salva em CSV o vetor de alunos que esta atualmente na memoria.
 * @param alunos Vetor de alunos carregado.
 * @param quantidade Quantidade atual de alunos.
 * @param ordenado Indica se os dados ja foram ordenados.
 * @return Nao retorna valor.
 */
static void salvar_resultado_interativo(const Aluno *alunos, int quantidade, int ordenado) {
    char caminho[CAMINHO_TAMANHO];

    if (alunos == NULL || quantidade == 0) {
        ui_mostrar_erro("Nao ha dados para salvar.");
        return;
    }

    if (ordenado == 0) {
        ui_mostrar_mensagem("Aviso: os dados ainda nao foram ordenados com o criterio atual.");
    }

    ui_ler_texto("Arquivo de saida: ", caminho, sizeof(caminho));
    if (caminho[0] == '\0') {
        ui_mostrar_erro("Caminho invalido.");
        return;
    }

    if (salvar_alunos_csv(caminho, alunos, quantidade) == 0) {
        ui_mostrar_erro("Nao foi possivel salvar o arquivo.");
        return;
    }

    ui_mostrar_arquivo_salvo(caminho);
}

/**
 * Executa todos os algoritmos usando uma copia do mesmo vetor de alunos.
 * @param alunos Vetor original de alunos.
 * @param quantidade Quantidade atual de alunos.
 * @param criterio Criterio que sera usado em todas as comparacoes.
 * @return Nao retorna valor.
 */
static void comparar_todos_algoritmos(const Aluno *alunos, int quantidade, TipoCriterio criterio) {
    TipoAlgoritmo algoritmos[5];
    int i;

    if (alunos == NULL || quantidade == 0) {
        ui_mostrar_erro("Gere dados antes de comparar algoritmos.");
        return;
    }

    algoritmos[0] = ALGORITMO_BUBBLE;
    algoritmos[1] = ALGORITMO_SELECTION;
    algoritmos[2] = ALGORITMO_INSERTION;
    algoritmos[3] = ALGORITMO_QUICK;
    algoritmos[4] = ALGORITMO_MERGE;

    ui_mostrar_titulo_comparacao(criterio);

    for (i = 0; i < 5; i++) {
        Aluno *copia = copiar_alunos(alunos, quantidade);
        MetricasOrdenacao metricas;
        int sucesso;

        if (copia == NULL) {
            ui_mostrar_erro("Memoria insuficiente para comparar algoritmos.");
            return;
        }

        /* Cada algoritmo recebe a mesma base de dados para a comparacao ficar justa. */
        sucesso = executar_ordenacao(algoritmos[i], copia, quantidade, criterio, &metricas);
        if (sucesso == 0) {
            free(copia);
            ui_mostrar_erro("Falha ao executar um dos algoritmos.");
            return;
        }

        ui_mostrar_nome_algoritmo(algoritmos[i]);
        ui_mostrar_metricas(&metricas);
        free(copia);
    }
}

/**
 * Controla o menu principal e decide qual acao executar a cada opcao.
 * @param alunos Ponteiro para o vetor atual de alunos.
 * @param quantidade Ponteiro para a quantidade atual de alunos.
 * @param quantidade_geracao Ponteiro para a quantidade configurada para gerar dados.
 * @param criterio_atual Ponteiro para o criterio selecionado.
 * @param algoritmo_atual Ponteiro para o algoritmo selecionado.
 * @param ultima_metrica Ponteiro para as metricas da ultima ordenacao.
 * @param ordenado Ponteiro para o estado de ordenacao atual.
 * @return Nao retorna valor.
 */
static void processar_menu(Aluno **alunos,
                           int *quantidade,
                           int *quantidade_geracao,
                           TipoCriterio *criterio_atual,
                           TipoAlgoritmo *algoritmo_atual,
                           MetricasOrdenacao *ultima_metrica,
                           int *ordenado) {
    int opcao = -1;

    while (opcao != 0) {
        ui_mostrar_menu(*quantidade,
                        *quantidade_geracao,
                        *criterio_atual,
                        *algoritmo_atual,
                        *ordenado);
        opcao = ui_ler_inteiro("Opcao: ");

        /* Cada bloco trata uma opcao do menu e mantem o fluxo principal facil de seguir. */
        if (opcao == 1) {
            gerar_dados_interativo(alunos,
                                   quantidade,
                                   *quantidade_geracao,
                                   ordenado,
                                   ultima_metrica);
        } else if (opcao == 2) {
            escolher_quantidade_interativa(quantidade_geracao);
        } else if (opcao == 3) {
            escolher_criterio_interativo(criterio_atual, ordenado);
        } else if (opcao == 4) {
            escolher_algoritmo_interativo(algoritmo_atual);
            ordenar_dados_interativo(*alunos,
                                     *quantidade,
                                     *criterio_atual,
                                     *algoritmo_atual,
                                     ordenado,
                                     ultima_metrica);
        } else if (opcao == 5) {
            comparar_todos_algoritmos(*alunos, *quantidade, *criterio_atual);
        } else if (opcao == 6) {
            ui_mostrar_top_alunos(*alunos, *quantidade);
        } else if (opcao == 7) {
            salvar_resultado_interativo(*alunos, *quantidade, *ordenado);
        } else if (opcao != 0) {
            ui_mostrar_erro("Opcao invalida.");
        }
    }
}

/**
 * Inicializa o sistema e executa o menu principal.
 * @return int Codigo de encerramento do programa.
 */
int main(void) {
    Aluno *alunos = NULL;
    int quantidade = 0;
    int quantidade_geracao = 100;
    TipoCriterio criterio_atual = CRITERIO_COMBINADO;
    TipoAlgoritmo algoritmo_atual = ALGORITMO_QUICK;
    MetricasOrdenacao ultima_metrica;
    int ordenado = 0;

    srand((unsigned int)time(NULL));
    resetar_metricas(&ultima_metrica);

    processar_menu(&alunos,
                   &quantidade,
                   &quantidade_geracao,
                   &criterio_atual,
                   &algoritmo_atual,
                   &ultima_metrica,
                   &ordenado);
    liberar_alunos(&alunos, &quantidade);
    return 0;
}
