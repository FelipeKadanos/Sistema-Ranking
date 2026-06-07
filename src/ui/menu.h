#ifndef MENU_H
#define MENU_H

#include "../metrics/metricas_ordenacao.h"
#include "../models/aluno.h"
#include "../sorting/tipos_ordenacao.h"

void exibir_menu(void);
void exibir_criterios(void);
void exibir_algoritmos(void);
void exibir_top_alunos(const Aluno *alunos, int quantidade, int limite);
void exibir_metricas(const metricas_ordenacao *metricas);

#endif
