#include "csv_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSV_LINHA_TAMANHO 256

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

int carregar_alunos_csv(const char *nome_arquivo, Aluno **alunos, int *quantidade) {
    FILE *arquivo;
    Aluno *vetor = NULL;
    int capacidade = 0;
    int total = 0;
    char linha[CSV_LINHA_TAMANHO];

    if (nome_arquivo == NULL || alunos == NULL || quantidade == NULL) {
        return 0;
    }

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *token;
        Aluno aluno;

        remover_quebra_linha(linha);
        if (linha[0] == '\0') {
            continue;
        }

        token = strtok(linha, ";");
        if (token == NULL) {
            continue;
        }
        aluno.matricula = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) {
            continue;
        }
        strncpy(aluno.nome, token, ALUNO_NOME_TAMANHO - 1);
        aluno.nome[ALUNO_NOME_TAMANHO - 1] = '\0';

        token = strtok(NULL, ";");
        if (token == NULL) {
            continue;
        }
        aluno.nota = (float)atof(token);

        token = strtok(NULL, ";");
        if (token == NULL) {
            continue;
        }
        aluno.faltas = atoi(token);

        if (total == capacidade) {
            Aluno *novo_vetor;
            capacidade = (capacidade == 0) ? 128 : capacidade * 2;
            novo_vetor = (Aluno *)realloc(vetor, (size_t)capacidade * sizeof(Aluno));
            if (novo_vetor == NULL) {
                free(vetor);
                fclose(arquivo);
                return 0;
            }
            vetor = novo_vetor;
        }

        vetor[total++] = aluno;
    }

    fclose(arquivo);
    *alunos = vetor;
    *quantidade = total;
    return 1;
}
