#ifndef ALUNO_H
#define ALUNO_H

#define ALUNO_NOME_TAMANHO 50

typedef struct {
    int matricula;
    char nome[ALUNO_NOME_TAMANHO];
    float nota;
    int faltas;
} Aluno;

void imprimir_aluno(const Aluno *aluno);

#endif
