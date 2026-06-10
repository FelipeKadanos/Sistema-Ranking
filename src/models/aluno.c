#include <stdio.h>

#define ALUNO_NOME_TAMANHO 50

typedef struct {
    int matricula;
    char nome[ALUNO_NOME_TAMANHO];
    float nota;
    int faltas;
} Aluno;

void imprimir_aluno(const Aluno *aluno) {
    if (aluno == NULL) {
        return;
    }

    printf("%6d | %-30s | %4.1f | %2d\n",
           aluno->matricula,
           aluno->nome,
           aluno->nota,
           aluno->faltas);
}
