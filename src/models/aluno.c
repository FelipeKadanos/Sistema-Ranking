#include "aluno.h"

#include <stdio.h>

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
