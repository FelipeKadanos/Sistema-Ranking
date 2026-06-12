#include <stdio.h>
#include <string.h>

#include "base.c"

/**
 * Limpa os caracteres restantes da entrada apos o uso do scanf.
 * @return Nao retorna valor.
 */
static void limpar_buffer_entrada(void) {
    int caractere;

    caractere = getchar();
    while (caractere != '\n' && caractere != EOF) {
        caractere = getchar();
    }
}

/**
 * Remove a quebra de linha do final de um texto lido com fgets.
 * @param texto Vetor que sera ajustado.
 * @return Nao retorna valor.
 */
static void remover_quebra_linha(char *texto) {
    size_t tamanho;

    if (texto == NULL) {
        return;
    }

    tamanho = strlen(texto);
    while (tamanho > 0 &&
           (texto[tamanho - 1] == '\n' || texto[tamanho - 1] == '\r')) {
        texto[tamanho - 1] = '\0';
        tamanho--;
    }
}

/**
 * Traduz o enum do criterio para um texto amigavel ao usuario.
 * @param criterio Criterio escolhido no sistema.
 * @return const char* Texto que representa o criterio.
 */
static const char *nome_criterio(TipoCriterio criterio) {
    if (criterio == CRITERIO_NOTA_CRESCENTE) {
        return "Nota crescente";
    }
    if (criterio == CRITERIO_NOTA_DECRESCENTE) {
        return "Nota decrescente";
    }
    if (criterio == CRITERIO_NOME) {
        return "Nome";
    }
    if (criterio == CRITERIO_FALTAS) {
        return "Faltas";
    }
    return "Combinado";
}

/**
 * Traduz o enum do algoritmo para um texto amigavel ao usuario.
 * @param algoritmo Algoritmo escolhido no sistema.
 * @return const char* Texto que representa o algoritmo.
 */
static const char *nome_algoritmo(TipoAlgoritmo algoritmo) {
    if (algoritmo == ALGORITMO_BUBBLE) {
        return "Bubble Sort";
    }
    if (algoritmo == ALGORITMO_SELECTION) {
        return "Selection Sort";
    }
    if (algoritmo == ALGORITMO_INSERTION) {
        return "Insertion Sort";
    }
    if (algoritmo == ALGORITMO_QUICK) {
        return "Quick Sort";
    }
    return "Merge Sort";
}

/**
 * Exibe um aluno em formato de tabela.
 * @param aluno Ponteiro para o aluno que sera impresso.
 * @return Nao retorna valor.
 */
static void imprimir_aluno(const Aluno *aluno) {
    if (aluno == NULL) {
        return;
    }

    printf("%6d | %-30s | %4.1f | %2d\n",
           aluno->matricula,
           aluno->nome,
           aluno->nota,
           aluno->faltas);
}

/**
 * Le um numero inteiro do teclado com validacao simples.
 * @param mensagem Texto exibido antes da leitura.
 * @return int Valor digitado pelo usuario.
 */
int ui_ler_inteiro(const char *mensagem) {
    int valor;
    int leu = 0;

    while (leu == 0) {
        printf("%s", mensagem);

        if (scanf("%d", &valor) == 1) {
            limpar_buffer_entrada();
            leu = 1;
        } else {
            /* Se a leitura falhar, o restante da linha e descartado para a proxima tentativa. */
            printf("Entrada invalida. Digite um numero.\n");
            limpar_buffer_entrada();
        }
    }

    return valor;
}

/**
 * Le um texto do teclado e remove a quebra de linha final.
 * @param mensagem Texto exibido antes da leitura.
 * @param buffer Vetor que recebera o texto lido.
 * @param tamanho Tamanho maximo do vetor.
 * @return Nao retorna valor.
 */
void ui_ler_texto(const char *mensagem, char *buffer, size_t tamanho) {
    printf("%s", mensagem);

    if (fgets(buffer, (int)tamanho, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    remover_quebra_linha(buffer);
}

/**
 * Exibe o menu principal do sistema.
 * @param quantidade Quantidade atual de alunos carregados.
 * @param tamanho_atual Quantidade de alunos configurada para a geracao.
 * @param criterio_atual Criterio de ordenacao atualmente selecionado.
 * @param algoritmo_atual Algoritmo de ordenacao atualmente selecionado.
 * @param ordenado Indica se os dados ja foram ordenados.
 * @return Nao retorna valor.
 */
void ui_mostrar_menu(int quantidade,
                     int tamanho_atual,
                     TipoCriterio criterio_atual,
                     TipoAlgoritmo algoritmo_atual,
                     int ordenado) {
    printf("\n===== Sistema de Ranking =====\n");
    printf("Alunos carregados  : %d\n", quantidade);
    printf("Tamanho configurado: %d\n", tamanho_atual);
    printf("Criterio atual     : %s\n", nome_criterio(criterio_atual));
    printf("Algoritmo atual    : %s\n", nome_algoritmo(algoritmo_atual));
    printf("Status             : %s\n", ordenado ? "ordenado" : "nao ordenado");
    printf("1 - Gerar dados automaticos\n");
    printf("2 - Escolher quantidade de dados\n");
    printf("3 - Escolher criterio de ordenacao\n");
    printf("4 - Executar algoritmo especifico\n");
    printf("5 - Comparar todos os algoritmos\n");
    printf("6 - Mostrar Top 10 alunos\n");
    printf("7 - Salvar resultados em arquivo\n");
    printf("0 - Sair\n");
}

/**
 * Mostra a lista de tamanhos permitidos para a geracao automatica.
 * @return Nao retorna valor.
 */
void ui_mostrar_tamanhos_geracao(void) {
    printf("\n1 - Gerar 100 alunos\n");
    printf("2 - Gerar 1000 alunos\n");
    printf("3 - Gerar 10000 alunos\n");
}

/**
 * Mostra a lista de criterios disponiveis no menu.
 * @return Nao retorna valor.
 */
void ui_mostrar_criterios(void) {
    printf("\n1 - Nota crescente\n");
    printf("2 - Nota decrescente\n");
    printf("3 - Nome\n");
    printf("4 - Faltas\n");
    printf("5 - Combinado\n");
}

/**
 * Mostra a lista de algoritmos disponiveis no menu.
 * @return Nao retorna valor.
 */
void ui_mostrar_algoritmos(void) {
    printf("\n1 - Bubble Sort\n");
    printf("2 - Selection Sort\n");
    printf("3 - Insertion Sort\n");
    printf("4 - Quick Sort\n");
    printf("5 - Merge Sort\n");
}

/**
 * Exibe apenas uma parte do vetor de alunos para formar o Top 10.
 * @param alunos Vetor com os alunos.
 * @param quantidade Quantidade total de alunos no vetor.
 * @return Nao retorna valor.
 */
void ui_mostrar_top_alunos(const Aluno *alunos, int quantidade) {
    int i;
    int limite = 10;

    if (alunos == NULL || quantidade == 0) {
        printf("Nenhum aluno carregado.\n");
        return;
    }

    if (quantidade < limite) {
        limite = quantidade;
    }

    printf("\nMatric | Nome                           | Nota | Ft\n");
    printf("----------------------------------------------------\n");
    for (i = 0; i < limite; i++) {
        imprimir_aluno(&alunos[i]);
    }
}

/**
 * Exibe as metricas da ultima ordenacao executada.
 * @param metricas Ponteiro para a estrutura de metricas.
 * @return Nao retorna valor.
 */
void ui_mostrar_metricas(const MetricasOrdenacao *metricas) {
    if (metricas == NULL) {
        return;
    }

    printf("\nComparacoes   : %ld\n", metricas->comparacoes);
    printf("Movimentacoes : %ld\n", metricas->movimentacoes);
    printf("Tempo (ms)    : %.3f\n", metricas->tempo_execucao_ms);
}

/**
 * Exibe uma mensagem simples na tela.
 * @param mensagem Texto que sera exibido.
 * @return Nao retorna valor.
 */
void ui_mostrar_mensagem(const char *mensagem) {
    printf("%s\n", mensagem);
}

/**
 * Exibe uma mensagem de erro na tela.
 * @param mensagem Texto que sera exibido.
 * @return Nao retorna valor.
 */
void ui_mostrar_erro(const char *mensagem) {
    printf("%s\n", mensagem);
}

/**
 * Informa quantos alunos foram gerados e carregados em memoria.
 * @param quantidade Quantidade total de alunos gerados.
 * @return Nao retorna valor.
 */
void ui_mostrar_dados_gerados(int quantidade) {
    printf("Dados gerados com %d alunos.\n", quantidade);
}

/**
 * Informa qual tamanho de geracao foi escolhido no sistema.
 * @param quantidade Quantidade escolhida para a proxima geracao.
 * @return Nao retorna valor.
 */
void ui_mostrar_tamanho_escolhido(int quantidade) {
    printf("Quantidade escolhida: %d alunos.\n", quantidade);
}

/**
 * Informa o caminho do arquivo salvo com o resultado da ordenacao.
 * @param caminho Caminho do arquivo salvo.
 * @return Nao retorna valor.
 */
void ui_mostrar_arquivo_salvo(const char *caminho) {
    printf("Resultado salvo em %s.\n", caminho);
}

/**
 * Mostra ao usuario qual criterio acabou de ser escolhido.
 * @param criterio Criterio selecionado no menu.
 * @return Nao retorna valor.
 */
void ui_mostrar_criterio_escolhido(TipoCriterio criterio) {
    printf("Criterio escolhido: %s\n", nome_criterio(criterio));
}

/**
 * Mostra ao usuario qual algoritmo acabou de ser escolhido.
 * @param algoritmo Algoritmo selecionado no menu.
 * @return Nao retorna valor.
 */
void ui_mostrar_algoritmo_escolhido(TipoAlgoritmo algoritmo) {
    printf("Algoritmo escolhido: %s\n", nome_algoritmo(algoritmo));
}

/**
 * Informa que a ordenacao terminou e mostra a combinacao usada.
 * @param algoritmo Algoritmo executado.
 * @param criterio Criterio usado na comparacao.
 * @return Nao retorna valor.
 */
void ui_mostrar_ordenacao_concluida(TipoAlgoritmo algoritmo, TipoCriterio criterio) {
    printf("Ordenacao concluida com %s usando %s.\n",
           nome_algoritmo(algoritmo),
           nome_criterio(criterio));
}

/**
 * Exibe o titulo da tela de comparacao entre algoritmos.
 * @param criterio Criterio usado na comparacao.
 * @return Nao retorna valor.
 */
void ui_mostrar_titulo_comparacao(TipoCriterio criterio) {
    printf("\nComparacao usando criterio %s:\n", nome_criterio(criterio));
}

/**
 * Exibe o nome de um algoritmo antes das metricas correspondentes.
 * @param algoritmo Algoritmo que sera identificado na tela.
 * @return Nao retorna valor.
 */
void ui_mostrar_nome_algoritmo(TipoAlgoritmo algoritmo) {
    printf("\n%s\n", nome_algoritmo(algoritmo));
}
