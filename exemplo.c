#include <stdio.h>
#include <string.h>

/* Quantidade maxima de paginas que cada pilha consegue armazenar. */
#define MAX 100

/* Quantidade maxima de caracteres no nome de cada pagina. */
#define MAX_TEXTO 80

/**
 * Representa uma pilha de paginas do historico.
 * paginas guarda os nomes acessados e topo indica a pagina mais recente da pilha.
 */
typedef struct {
    char paginas[MAX][MAX_TEXTO];
    int topo;
} Pilha;

/**
 * Define uma pilha de paginas como vazia antes do primeiro uso.
 * @param pilha Ponteiro para a pilha que sera inicializada.
 * @return Nao retorna valor.
 */
void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

/**
 * Verifica se a pilha nao possui paginas armazenadas.
 * @param pilha Pilha que sera consultada.
 * @return int|bool 1|true se a pilha estiver vazia ou 0|false caso contrario.
 */
int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

/**
 * Verifica se a pilha atingiu a capacidade maxima de paginas.
 * @param pilha Pilha que sera consultada.
 * @return int|bool 1|true se a pilha estiver cheia ou 0|false caso contrario.
 */
int pilhaCheia(Pilha *pilha) {
    return pilha->topo == MAX - 1;
}

/**
 * Empilha uma pagina no topo do historico informado.
 * @param pilha Pilha que recebera a pagina.
 * @param pagina Texto com o nome da pagina.
 * @return int|bool 1|true se a insercao ocorrer ou 0|false se a pilha estiver cheia.
 */
int empilhar(Pilha *pilha, char pagina[]) {
    if (pilhaCheia(pilha)) {
        return 0;
    }

    pilha->topo++;
    strcpy(pilha->paginas[pilha->topo], pagina);
    return 1;
}

/**
 * Remove a pagina que esta no topo do historico informado.
 * @param pilha Pilha de onde a pagina sera removida.
 * @param pagina Vetor que recebera o nome da pagina removida.
 * @return int|bool 1|true se a remocao ocorrer ou 0|false se a pilha estiver vazia.
 */
int desempilhar(Pilha *pilha, char pagina[]) {
    if (pilhaVazia(pilha)) {
        return 0;
    }

    strcpy(pagina, pilha->paginas[pilha->topo]);
    pilha->topo--;
    return 1;
}

/**
 * Limpa os caracteres restantes da entrada padrao apos a leitura de numeros.
 * @return Nao retorna valor.
 */
void limparEntrada(void) {
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

/**
 * Le um texto com espacos e remove a quebra de linha final.
 * @param texto Vetor que recebera o texto lido.
 * @param tamanho Tamanho maximo do vetor de texto.
 * @return Nao retorna valor.
 */
void lerTexto(char texto[], int tamanho) {
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0';
}

/**
 * Exibe o menu da questao 5 e simula voltar e avancar usando duas pilhas.
 * @return int Codigo de encerramento do programa.
 */
int main(void) {
    Pilha voltar;
    Pilha avancar;
    char atual[MAX_TEXTO] = "";
    char pagina[MAX_TEXTO];
    int opcao;

    inicializarPilha(&voltar);
    inicializarPilha(&avancar);

    do {
        printf("\n--- Questao 5: Historico de navegacao ---\n");
        printf("Pagina atual: %s\n", strlen(atual) == 0 ? "nenhuma" : atual);
        printf("1 - VISITAR pagina\n");
        printf("2 - VOLTAR\n");
        printf("3 - AVANCAR\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparEntrada();

        switch (opcao) {
            case 1:
                printf("\nDigite o nome da pagina: ");
                lerTexto(pagina, MAX_TEXTO);

                if (strlen(atual) > 0) {
                    /* A pagina atual vai para a pilha "voltar" antes da nova visita. */
                    empilhar(&voltar, atual);
                }

                strcpy(atual, pagina);
                /* Ao visitar uma pagina nova, o historico de avancar deixa de valer. */
                inicializarPilha(&avancar);
                printf("Pagina visitada: %s\n", atual);
                break;
            case 2:
                if (strlen(atual) == 0 || pilhaVazia(&voltar)) {
                    printf("\nNao ha pagina anterior.\n");
                    break;
                }

                /* Ao voltar, a pagina atual vai para a pilha avancar e a pagina
                   anterior sai do topo da pilha voltar. */
                empilhar(&avancar, atual);
                desempilhar(&voltar, atual);
                printf("\nVoltou para: %s\n", atual);
                break;
            case 3:
                if (pilhaVazia(&avancar)) {
                    printf("\nNao ha proxima pagina.\n");
                    break;
                }

                /* Ao avancar, a pagina atual volta para a pilha de retorno. */
                empilhar(&voltar, atual);
                desempilhar(&avancar, atual);
                printf("\nAvancou para: %s\n", atual);
                break;
            case 0:
                printf("\nEncerrando questao 5.\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}