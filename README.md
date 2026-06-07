# Sistema de Ranking de Desempenho Academico

Projeto academico em C, compativel com `GCC` e `Dev-C++`, voltado para testes de desempenho de algoritmos de ordenacao aplicados a registros de alunos.

## Visao Geral

O sistema le registros de alunos a partir de arquivos CSV, permite ordenacoes por multiplos criterios e exibe metricas de desempenho da ordenacao executada.

Neste esqueleto:

- a arquitetura e modular;
- apenas o `Quick Sort` esta implementado por completo;
- `Bubble Sort`, `Insertion Sort`, `Selection Sort` e `Merge Sort` possuem placeholder com `TODO`;
- o projeto compila sem erros e esta pronto para expansao futura.

## Estrutura do Projeto

```text
src/
|-- main.c
|-- models/
|   |-- aluno.h
|   `-- aluno.c
|-- data/
|   |-- csv_reader.h
|   `-- csv_reader.c
|-- ui/
|   |-- menu.h
|   `-- menu.c
|-- metrics/
|   |-- metricas_ordenacao.h
|   `-- metricas_ordenacao.c
|-- sorting/
|   |-- tipos_ordenacao.h
|   |-- comparador.h
|   |-- comparador.c
|   |-- gerenciador_ordenacao.h
|   |-- gerenciador_ordenacao.c
|   |-- quick_sort.h
|   |-- quick_sort.c
|   |-- bubble_sort.h
|   |-- bubble_sort.c
|   |-- insertion_sort.h
|   |-- insertion_sort.c
|   |-- selection_sort.h
|   |-- selection_sort.c
|   |-- merge_sort.h
|   `-- merge_sort.c
`-- generators/
    |-- dataset_generator.h
    `-- dataset_generator.c

datasets/
|-- alunos_100.csv
|-- alunos_1000.csv
`-- alunos_10000.csv
```

## Estrutura do Aluno

```c
typedef struct {
    int matricula;
    char nome[50];
    float nota;
    int faltas;
} Aluno;
```

## Metricas

O projeto utiliza a estrutura:

```c
typedef struct {
    long comparacoes;
    long movimentacoes;
    double tempo_execucao_ms;
} metricas_ordenacao;
```

Funcoes auxiliares implementadas:

- resetar metricas;
- iniciar temporizacao;
- finalizar temporizacao.

## Tipos de Ordenacao

```c
typedef enum {
    NOTA_CRESCENTE,
    NOTA_DECRESCENTE,
    NOME,
    FALTAS,
    COMBINADO
} tipo_ordenacao;
```

## Comparador Generico

Todos os algoritmos utilizam um comparador centralizado com os criterios:

- `NOTA_CRESCENTE`: menor nota primeiro;
- `NOTA_DECRESCENTE`: maior nota primeiro;
- `NOME`: ordem alfabetica;
- `FALTAS`: menor numero de faltas primeiro;
- `COMBINADO`: maior nota, depois menor numero de faltas e, em novo empate, ordem alfabetica.

## Gerenciador de Ordenacao

O modulo `gerenciador_ordenacao` despacha a execucao para o algoritmo selecionado:

```c
void executar_ordenacao(
    algoritmo_ordenacao algoritmo,
    Aluno *alunos,
    int quantidade,
    tipo_ordenacao criterio,
    metricas_ordenacao *metricas
);
```

## CSV

Formato esperado:

```text
matricula;nome;nota;faltas
```

Exemplo:

```text
1;Joao Silva;8.5;2
2;Maria Souza;9.0;1
```

O leitor CSV faz apenas leitura. Escrita nao foi implementada no modulo de importacao, apenas no gerador de datasets.

## Menu

O menu funcional oferece:

```text
1 - Carregar CSV
2 - Escolher criterio de ordenacao
3 - Escolher algoritmo
4 - Executar ordenacao
5 - Mostrar Top 10 alunos
6 - Mostrar metricas
0 - Sair
```

Fluxo esperado:

- carregar um CSV;
- escolher criterio;
- escolher algoritmo;
- executar a ordenacao;
- visualizar o resultado;
- visualizar as metricas.

## Geracao de Datasets

O projeto possui um modulo reutilizavel em `src/generators/` responsavel por:

- gerar matriculas unicas;
- gerar nomes brasileiros aleatorios;
- gerar notas entre `0` e `10`;
- gerar faltas entre `0` e `30`;
- exportar para CSV usando `;`.

Funcao principal:

```c
void gerar_dataset_csv(const char *nome_arquivo, int quantidade_registros);
```

Exemplos:

```c
gerar_dataset_csv("datasets/alunos_100.csv", 100);
gerar_dataset_csv("datasets/alunos_1000.csv", 1000);
gerar_dataset_csv("datasets/alunos_10000.csv", 10000);
```

### Geracao automatica

Ao iniciar o programa normalmente, os arquivos abaixo sao gerados automaticamente caso nao existam:

- `datasets/alunos_100.csv`
- `datasets/alunos_1000.csv`

O arquivo `datasets/alunos_10000.csv` nao e gerado automaticamente.

### Como gerar novamente os datasets

Gerar os datasets padrao:

```bash
./sistema_ranking --gerar-padrao
```

Gerar um dataset de qualquer tamanho:

```bash
./sistema_ranking --gerar datasets/meu_dataset.csv 500
```

Gerar especificamente o dataset de `10000` registros:

```bash
./sistema_ranking --gerar datasets/alunos_10000.csv 10000
```

## Compilacao com GCC

No Windows com `GCC`:

```bash
gcc -Wall -Wextra -pedantic -std=c11 ^
src/main.c ^
src/models/aluno.c ^
src/data/csv_reader.c ^
src/ui/menu.c ^
src/metrics/metricas_ordenacao.c ^
src/sorting/comparador.c ^
src/sorting/gerenciador_ordenacao.c ^
src/sorting/quick_sort.c ^
src/sorting/bubble_sort.c ^
src/sorting/insertion_sort.c ^
src/sorting/selection_sort.c ^
src/sorting/merge_sort.c ^
src/generators/dataset_generator.c ^
-o sistema_ranking.exe
```

No Linux ou macOS:

```bash
gcc -Wall -Wextra -pedantic -std=c11 \
src/main.c \
src/models/aluno.c \
src/data/csv_reader.c \
src/ui/menu.c \
src/metrics/metricas_ordenacao.c \
src/sorting/comparador.c \
src/sorting/gerenciador_ordenacao.c \
src/sorting/quick_sort.c \
src/sorting/bubble_sort.c \
src/sorting/insertion_sort.c \
src/sorting/selection_sort.c \
src/sorting/merge_sort.c \
src/generators/dataset_generator.c \
-o sistema_ranking
```

## Exemplos de Linhas dos Datasets

Exemplo ilustrativo de `alunos_100.csv`:

```text
100000;Joao Silva;8.4;3
100001;Maria Souza;9.1;1
100002;Pedro Lima;6.7;8
```

Exemplo ilustrativo de `alunos_1000.csv`:

```text
100000;Ana Costa;7.5;4
100001;Lucas Almeida;5.9;12
100002;Julia Gomes;9.8;0
```

Exemplo ilustrativo de como seria `alunos_10000.csv`:

```text
100000;Gabriel Santos;8.0;6
100001;Beatriz Rocha;7.2;11
100002;Rafael Dias;9.4;2
```

## Estado Atual

- `Quick Sort`: implementado completamente;
- `Bubble Sort`: placeholder;
- `Insertion Sort`: placeholder;
- `Selection Sort`: placeholder;
- `Merge Sort`: placeholder.

Arquitetura pronta para evolucao, testes comparativos e expansao futura.
