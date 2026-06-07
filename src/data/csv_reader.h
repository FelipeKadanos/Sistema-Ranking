#ifndef CSV_READER_H
#define CSV_READER_H

#include "../models/aluno.h"

int carregar_alunos_csv(const char *nome_arquivo, Aluno **alunos, int *quantidade);

#endif
