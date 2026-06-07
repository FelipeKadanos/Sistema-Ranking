#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include "../metrics/metricas_ordenacao.h"
#include "../models/aluno.h"
#include "tipos_ordenacao.h"

void selection_sort(Aluno *alunos,
                    int quantidade,
                    tipo_ordenacao criterio,
                    metricas_ordenacao *metricas);

#endif
