# Sistema de Ranking de Desempenho Acadêmico
## Data Processing

> Atividade a ser realizada em grupo (até 3 pessoas).
>
> Deve ser utilizada a linguagem de programação C.
>
> O código deve ser postado no Blackboard como entregável e a nota será concedida juntamente com a defesa de código em sala de aula.

---

## 🎯 Contexto

Uma universidade está desenvolvendo um sistema para analisar o desempenho dos alunos em diferentes disciplinas. O sistema precisa:

- Processar grandes volumes de dados
- Ordenar alunos com base em diferentes critérios
- Permitir análises flexíveis e comparações de desempenho

Sua equipe foi contratada para desenvolver um módulo de ordenação altamente eficiente, capaz de lidar com diferentes cenários de ordenação.

Desenvolver um programa em C que manipule registros de alunos e permita ordenações complexas utilizando múltiplos algoritmos.

---

## 🗃️ Estrutura dos Dados

Cada aluno deve ser representado por uma `struct`:

```c
typedef struct {
    int matricula;
    char nome[50];
    float nota;
    int faltas;
} Aluno;
```

---

## ⚙️ Requisitos Funcionais

### 1. Entrada de dados

Leitura a partir de:

- Arquivo `.txt` ou `.csv`
- Geração automática (`100`, `1000`, `10000` alunos)

Os dados devem incluir:

- Matrícula única
- Nome
- Nota (`0` a `10`)
- Número de faltas

### 2. Ordenações MULTICRITÉRIO

O sistema deve permitir ordenar por:

- Nota (crescente e decrescente)
- Nome (ordem alfabética)
- Faltas
- Critério combinado:
  Maior nota
  Em caso de empate → menor número de faltas
  Persistindo empate → ordem alfabética

### 3. Algoritmos obrigatórios

- Bubble Sort
- Selection Sort
- Insertion Sort
- Quick Sort
- Merge Sort

### 4. Análise de desempenho avançada

Para cada algoritmo:

- Tempo de execução
- Número de comparações
- Número de movimentações

### 5. Interface mais rica

Menu exemplo:

```text
1 - Carregar dados de arquivo
2 - Gerar dados aleatórios
3 - Escolher critério de ordenação
4 - Executar algoritmo específico
5 - Comparar todos os algoritmos
6 - Mostrar Top 10 alunos
7 - Salvar resultados em arquivo
0 - Sair
```

### 6. Saída

- Exibir ranking completo ou parcial (Top N)
- Exportar resultado ordenado para arquivo
- Mostrar métricas de desempenho
