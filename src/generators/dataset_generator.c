#include "dataset_generator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define MKDIR(path) mkdir(path, 0777)
#endif

static const char *nomes[] = {
    "Joao", "Maria", "Ana", "Pedro", "Lucas", "Julia", "Gabriel", "Beatriz",
    "Rafael", "Larissa", "Bruno", "Camila", "Felipe", "Mariana", "Thiago",
    "Fernanda", "Gustavo", "Aline", "Daniel", "Patricia"
};

static const char *sobrenomes[] = {
    "Silva", "Souza", "Oliveira", "Santos", "Lima", "Costa", "Pereira",
    "Almeida", "Ferreira", "Rodrigues", "Gomes", "Ribeiro", "Martins",
    "Carvalho", "Araujo", "Barbosa", "Rocha", "Dias", "Teixeira", "Melo"
};

static int gerador_inicializado = 0;

static void inicializar_gerador(void) {
    if (!gerador_inicializado) {
        srand((unsigned int)time(NULL));
        gerador_inicializado = 1;
    }
}

static void garantir_pasta_datasets(void) {
    MKDIR("datasets");
}

static int valor_aleatorio(int minimo, int maximo) {
    return minimo + (rand() % (maximo - minimo + 1));
}

static float nota_aleatoria(void) {
    return (float)valor_aleatorio(0, 100) / 10.0f;
}

static void gerar_nome_aleatorio(char *destino, size_t tamanho) {
    const char *nome = nomes[valor_aleatorio(0, (int)(sizeof(nomes) / sizeof(nomes[0])) - 1)];
    const char *sobrenome =
        sobrenomes[valor_aleatorio(0, (int)(sizeof(sobrenomes) / sizeof(sobrenomes[0])) - 1)];
    snprintf(destino, tamanho, "%s %s", nome, sobrenome);
}

void gerar_dataset_csv(const char *nome_arquivo, int quantidade_registros) {
    FILE *arquivo;
    int indice;

    if (nome_arquivo == NULL || quantidade_registros <= 0) {
        return;
    }

    inicializar_gerador();
    garantir_pasta_datasets();

    arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        return;
    }

    for (indice = 0; indice < quantidade_registros; indice++) {
        char nome_completo[64];
        int matricula = 100000 + indice;
        float nota = nota_aleatoria();
        int faltas = valor_aleatorio(0, 30);

        gerar_nome_aleatorio(nome_completo, sizeof(nome_completo));
        fprintf(arquivo, "%d;%s;%.1f;%d\n", matricula, nome_completo, nota, faltas);
    }

    fclose(arquivo);
}

void gerar_datasets_padrao(void) {
    FILE *arquivo_100;
    FILE *arquivo_1000;

    garantir_pasta_datasets();

    arquivo_100 = fopen("datasets/alunos_100.csv", "r");
    if (arquivo_100 == NULL) {
        gerar_dataset_csv("datasets/alunos_100.csv", 100);
    } else {
        fclose(arquivo_100);
    }

    arquivo_1000 = fopen("datasets/alunos_1000.csv", "r");
    if (arquivo_1000 == NULL) {
        gerar_dataset_csv("datasets/alunos_1000.csv", 1000);
    } else {
        fclose(arquivo_1000);
    }
}
