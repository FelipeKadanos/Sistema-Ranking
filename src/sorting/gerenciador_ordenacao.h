#ifndef GERENCIADOR_ORDENACAO_H
#define GERENCIADOR_ORDENACAO_H

#include "../metrics/metricas_ordenacao.h"
#include "../models/aluno.h"
#include "tipos_ordenacao.h"

void executar_ordenacao(algoritmo_ordenacao algoritmo,
                        Aluno *alunos,
                        int quantidade,
                        tipo_ordenacao criterio,
                        metricas_ordenacao *metricas);

#endif
