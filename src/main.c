#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data/csv_reader.h"
#include "generators/dataset_generator.h"
#include "metrics/metricas_ordenacao.h"
#include "models/aluno.h"
#include "sorting/gerenciador_ordenacao.h"
#include "ui/menu.h"

static void limpar_buffer_entrada(void) {
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

static int ler_inteiro(void) {
    int valor;

    while (scanf("%d", &valor) != 1) {
        printf("Entrada invalida. Tente novamente: ");
        limpar_buffer_entrada();
    }

    limpar_buffer_entrada();
    return valor;
}

static void ler_texto(char *buffer, size_t tamanho) {
    if (fgets(buffer, (int)tamanho, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    buffer[strcspn(buffer, "\r\n")] = '\0';
}

static void carregar_csv_interativo(Aluno **alunos, int *quantidade) {
    char caminho[260];
    Aluno *novos_alunos = NULL;
    int nova_quantidade = 0;

    printf("Informe o caminho do arquivo CSV: ");
    ler_texto(caminho, sizeof(caminho));

    if (carregar_alunos_csv(caminho, &novos_alunos, &nova_quantidade)) {
        free(*alunos);
        *alunos = novos_alunos;
        *quantidade = nova_quantidade;
        printf("Arquivo carregado com sucesso. %d registros encontrados.\n", *quantidade);
    } else {
        printf("Nao foi possivel carregar o arquivo informado.\n");
    }
}

static tipo_ordenacao escolher_criterio(tipo_ordenacao criterio_atual) {
    int opcao;

    exibir_criterios();
    opcao = ler_inteiro();

    if (opcao < NOTA_CRESCENTE || opcao > COMBINADO) {
        printf("Criterio invalido. Mantendo: %s\n", obter_nome_criterio(criterio_atual));
        return criterio_atual;
    }

    printf("Criterio selecionado: %s\n", obter_nome_criterio((tipo_ordenacao)opcao));
    return (tipo_ordenacao)opcao;
}

static algoritmo_ordenacao escolher_algoritmo(algoritmo_ordenacao algoritmo_atual) {
    int opcao;

    exibir_algoritmos();
    opcao = ler_inteiro();

    if (opcao < QUICK_SORT || opcao > MERGE_SORT) {
        printf("Algoritmo invalido. Mantendo: %s\n", obter_nome_algoritmo(algoritmo_atual));
        return algoritmo_atual;
    }

    printf("Algoritmo selecionado: %s\n", obter_nome_algoritmo((algoritmo_ordenacao)opcao));
    return (algoritmo_ordenacao)opcao;
}

static void executar_fluxo_ordenacao(Aluno *alunos,
                                     int quantidade,
                                     tipo_ordenacao criterio,
                                     algoritmo_ordenacao algoritmo,
                                     metricas_ordenacao *metricas) {
    if (alunos == NULL || quantidade == 0) {
        printf("Carregue um CSV antes de executar a ordenacao.\n");
        return;
    }

    executar_ordenacao(algoritmo, alunos, quantidade, criterio, metricas);
    printf("Ordenacao finalizada com %s usando criterio %s.\n",
           obter_nome_algoritmo(algoritmo),
           obter_nome_criterio(criterio));
}

static int processar_argumentos(int argc, char **argv) {
    int quantidade;

    if (argc == 2 && strcmp(argv[1], "--gerar-padrao") == 0) {
        gerar_datasets_padrao();
        printf("Datasets padrao gerados em datasets/.\n");
        return 1;
    }

    if (argc == 4 && strcmp(argv[1], "--gerar") == 0) {
        quantidade = atoi(argv[3]);
        if (quantidade <= 0) {
            printf("Quantidade invalida para geracao de dataset.\n");
            return 1;
        }
        gerar_dataset_csv(argv[2], quantidade);
        printf("Dataset gerado em %s com %d registros.\n", argv[2], quantidade);
        return 1;
    }

    return 0;
}

int main(int argc, char **argv) {
    Aluno *alunos = NULL;
    int quantidade = 0;
    int opcao = -1;
    tipo_ordenacao criterio_atual = COMBINADO;
    algoritmo_ordenacao algoritmo_atual = QUICK_SORT;
    metricas_ordenacao metricas;

    resetar_metricas(&metricas);

    if (processar_argumentos(argc, argv)) {
        return 0;
    }

    gerar_datasets_padrao();

    while (opcao != 0) {
        printf("\nCriterio atual : %s\n", obter_nome_criterio(criterio_atual));
        printf("Algoritmo atual: %s\n", obter_nome_algoritmo(algoritmo_atual));
        exibir_menu();
        opcao = ler_inteiro();

        switch (opcao) {
            case 1:
                carregar_csv_interativo(&alunos, &quantidade);
                break;
            case 2:
                criterio_atual = escolher_criterio(criterio_atual);
                break;
            case 3:
                algoritmo_atual = escolher_algoritmo(algoritmo_atual);
                break;
            case 4:
                executar_fluxo_ordenacao(alunos,
                                         quantidade,
                                         criterio_atual,
                                         algoritmo_atual,
                                         &metricas);
                break;
            case 5:
                exibir_top_alunos(alunos, quantidade, 10);
                break;
            case 6:
                exibir_metricas(&metricas);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }

    free(alunos);
    return 0;
}
