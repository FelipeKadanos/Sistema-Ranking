#ifndef TIPOS_ORDENACAO_H
#define TIPOS_ORDENACAO_H

typedef enum {
    NOTA_CRESCENTE = 1,
    NOTA_DECRESCENTE,
    NOME,
    FALTAS,
    COMBINADO
} tipo_ordenacao;

typedef enum {
    QUICK_SORT = 1,
    BUBBLE_SORT,
    INSERTION_SORT,
    SELECTION_SORT,
    MERGE_SORT
} algoritmo_ordenacao;

const char *obter_nome_criterio(tipo_ordenacao criterio);
const char *obter_nome_algoritmo(algoritmo_ordenacao algoritmo);

#endif
