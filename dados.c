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

#include "base.c"

static const char *NOMES[] = {
    "Joao", "Maria", "Ana", "Pedro", "Lucas", "Julia", "Gabriel", "Beatriz",
    "Rafael", "Larissa", "Bruno", "Camila", "Felipe", "Mariana", "Thiago",
    "Fernanda", "Gustavo", "Aline", "Daniel", "Patricia"
};

static const char *SOBRENOMES[] = {
    "Silva", "Souza", "Oliveira", "Santos", "Lima", "Costa", "Pereira",
    "Almeida", "Ferreira", "Rodrigues", "Gomes", "Ribeiro", "Martins",
    "Carvalho", "Araujo", "Barbosa", "Rocha", "Dias", "Teixeira", "Melo"
};

/**
 * Garante que a pasta de datasets exista antes de salvar arquivos nela.
 * @return Nao retorna valor.
 */
static void garantir_pasta_datasets(void) {
    MKDIR("datasets");
}

/**
 * Gera um numero aleatorio dentro do intervalo informado.
 * @param minimo Menor valor possivel.
 * @param maximo Maior valor possivel.
 * @return int Numero sorteado dentro do intervalo.
 */
static int numero_aleatorio(int minimo, int maximo) {
    return minimo + (rand() % (maximo - minimo + 1));
}

/**
 * Gera uma nota aleatoria entre 0.0 e 10.0.
 * @return float Nota gerada para um aluno ficticio.
 */
static float nota_aleatoria(void) {
    return (float)numero_aleatorio(0, 100) / 10.0f;
}

/**
 * Monta um nome completo aleatorio usando um nome e um sobrenome da lista.
 * @param destino Vetor que recebera o nome final.
 * @param tamanho Tamanho maximo do vetor de destino.
 * @return Nao retorna valor.
 */
static void gerar_nome_aleatorio(char *destino, size_t tamanho) {
    int indice_nome;
    int indice_sobrenome;

    indice_nome = numero_aleatorio(0, (int)(sizeof(NOMES) / sizeof(NOMES[0])) - 1);
    indice_sobrenome =
        numero_aleatorio(0, (int)(sizeof(SOBRENOMES) / sizeof(SOBRENOMES[0])) - 1);

    snprintf(destino, tamanho, "%s %s", NOMES[indice_nome], SOBRENOMES[indice_sobrenome]);
}

/**
 * Gera um vetor de alunos diretamente na memoria.
 * @param quantidade Quantidade de alunos que sera gerada.
 * @return Aluno* Ponteiro para o vetor alocado ou NULL em caso de erro.
 */
Aluno *gerar_alunos_automaticamente(int quantidade) {
    Aluno *alunos;
    int i;

    if (quantidade <= 0) {
        return NULL;
    }

    alunos = (Aluno *)malloc((size_t)quantidade * sizeof(Aluno));
    if (alunos == NULL) {
        return NULL;
    }

    for (i = 0; i < quantidade; i++) {
        alunos[i].matricula = 100000 + i;
        alunos[i].nota = nota_aleatoria();
        alunos[i].faltas = numero_aleatorio(0, 30);

        /* O nome e gerado junto com os demais dados para ja deixar o vetor pronto para uso. */
        gerar_nome_aleatorio(alunos[i].nome, sizeof(alunos[i].nome));
    }

    return alunos;
}

/**
 * Salva em CSV os alunos que ja estao carregados na memoria.
 * @param caminho Caminho do arquivo que sera criado.
 * @param alunos Vetor com os alunos que serao gravados.
 * @param quantidade Quantidade de alunos no vetor.
 * @return int 1 se o arquivo for criado com sucesso ou 0 em caso de erro.
 */
int salvar_alunos_csv(const char *caminho, const Aluno *alunos, int quantidade) {
    FILE *arquivo;
    int i;

    if (caminho == NULL || alunos == NULL || quantidade <= 0) {
        return 0;
    }

    /* A pasta de datasets e garantida para facilitar salvar resultados sem preparo manual. */
    garantir_pasta_datasets();
    arquivo = fopen(caminho, "w");
    if (arquivo == NULL) {
        return 0;
    }

    for (i = 0; i < quantidade; i++) {
        fprintf(arquivo,
                "%d;%s;%.1f;%d\n",
                alunos[i].matricula,
                alunos[i].nome,
                alunos[i].nota,
                alunos[i].faltas);
    }

    fclose(arquivo);
    return 1;
}

/**
 * Cria uma copia do vetor de alunos.
 * @param origem Vetor original que sera copiado.
 * @param quantidade Quantidade de alunos no vetor.
 * @return Aluno* Ponteiro para a nova copia ou NULL em caso de erro.
 */
Aluno *copiar_alunos(const Aluno *origem, int quantidade) {
    Aluno *copia;

    if (origem == NULL || quantidade <= 0) {
        return NULL;
    }

    copia = (Aluno *)malloc((size_t)quantidade * sizeof(Aluno));
    if (copia == NULL) {
        return NULL;
    }

    memcpy(copia, origem, (size_t)quantidade * sizeof(Aluno));
    return copia;
}

/**
 * Libera o vetor de alunos alocado dinamicamente e zera a quantidade.
 * @param alunos Ponteiro para o ponteiro do vetor que sera liberado.
 * @param quantidade Ponteiro para a quantidade atual de alunos.
 * @return Nao retorna valor.
 */
void liberar_alunos(Aluno **alunos, int *quantidade) {
    if (alunos != NULL && *alunos != NULL) {
        free(*alunos);
        *alunos = NULL;
    }

    if (quantidade != NULL) {
        *quantidade = 0;
    }
}
