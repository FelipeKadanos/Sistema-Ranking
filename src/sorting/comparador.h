#ifndef COMPARADOR_H
#define COMPARADOR_H

#include "../metrics/metricas_ordenacao.h"
#include "../models/aluno.h"
#include "tipos_ordenacao.h"

int comparar_alunos(const Aluno *a,
                    const Aluno *b,
                    tipo_ordenacao criterio,
                    metricas_ordenacao *metricas);

#endif
