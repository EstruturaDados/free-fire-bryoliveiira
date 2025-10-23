#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20 // Capacidade de componentes

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

typedef enum {
    CRITERIO_NOME,
    CRITERIO_TIPO,
    CRITERIO_PRIORIDADE
} CriterioOrdenacao;

Componente torre[MAX_COMPONENTES];
int numComponentes = 0;
long comparacoes_algoritmo = 0;
clock_t inicio_tempo, fim_tempo;


void limparTela() {
    for (int i = 0; i < 40; i++) {
        printf("\n");
    }
}

void exibirMenu() {
    limparTela();
    printf("================================================================\n");
    printf("= MODULO DE ORGANIZACAO DA TORRE DE FUGA (NIVEL MESTRE) =\n");
    printf("================================================================\n");
    printf("COMPONENTES ATUAIS: %d/%d\n", numComponentes, MAX_COMPONENTES);
    printf("----------------------------------------------------------------\n");
    printf("1. Cadastrar Componente\n");
    printf("2. Remover Componente (por nome)\n");
    printf("3. Listar Componentes\n");
    printf("4. ORDENAR Componentes (Escolha o Criterio)\n");
    printf("5. Buscar Binaria por Nome (Requer ORDEM por NOME)\n");
    printf("0. Encerrar Modulo\n");
    printf("----------------------------------------------------------------\n");
}

void mostrarComponentes(Componente componentes[], int tamanho) {
    if (tamanho == 0) {
        printf("\n[LISTAGEM] O inventario da torre esta vazio.\n");
        return;
    }
    printf("\n--- ESTADO ATUAL DOS COMPONENTES (%d Itens) ---\n", tamanho);
    printf("%-4s | %-25s | %-15s | %s\n", "ID", "NOME", "TIPO", "PRIORIDADE");
    printf("------------------------------------------------------------------\n");
    
    for (int i = 0; i < tamanho; i++) {
        printf("%-4d | %-25s | %-15s | %d\n", 
               i, 
               componentes[i].nome, 
               componentes[i].tipo, 
               componentes[i].prioridade);
    }
    printf("------------------------------------------------------------------\n");
}

void medirTempo(void (*algoritmo)(), CriterioOrdenacao criterio) {
    comparacoes_algoritmo = 0;
    inicio_tempo = clock();
    
    algoritmo(criterio); 
    
    fim_tempo = clock();
    
    printf("\n[DESEMPENHO] Tempo de execucao: %.6f segundos.\n", (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC);
    printf("[DESEMPENHO] Comparações totais realizadas: %ld\n", comparacoes_algoritmo);
}


void cadastrarComponente() {
    if (numComponentes >= MAX_COMPONENTES) {
        printf("\nERRO: Limite de %d componentes alcancado. Nao e possivel coletar mais.\n", MAX_COMPONENTES);
        return;
    }

    printf("\n--- CADASTRAR NOVO COMPONENTE ---\n");
    
    printf("Nome do Componente: ");
    while (getchar() != '\n'); 
    fgets(torre[numComponentes].nome, 30, stdin);
    torre[numComponentes].nome[strcspn(torre[numComponentes].nome, "\n")] = 0;

    printf("Tipo (ex: controle, propulsao): ");
    scanf("%19s", torre[numComponentes].tipo);
    
    printf("Prioridade (1 a 10): ");
    scanf("%d", &torre[numComponentes].prioridade);

    if (torre[numComponentes].prioridade < 1 || torre[numComponentes].prioridade > 10) {
        printf("\nPrioridade invalida. Componente nao cadastrado.\n");
        return;
    }
    
    numComponentes++;
    printf("\nComponente '%s' cadastrado com sucesso.\n", torre[numComponentes - 1].nome);
}

void removerComponente() {
    char nome[30];
    printf("\n--- REMOVER COMPONENTE ---\n");
    printf("Nome do componente a remover: ");
    while (getchar() != '\n');
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    int idx = -1;
    for (int i = 0; i < numComponentes; i++) {
        if (strcmp(torre[i].nome, nome) == 0) {
            idx = i;
            break;
        }
    }

    if (idx != -1) {
        for (int i = idx; i < numComponentes - 1; i++) {
            torre[i] = torre[i + 1];
        }
        numComponentes--;
        printf("\nComponente '%s' removido.\n", nome);
    } else {
        printf("\nComponente '%s' nao encontrado para remocao.\n", nome);
    }
}


void bubbleSortNome(CriterioOrdenacao criterio) {
    for (int i = 0; i < numComponentes - 1; i++) {
        for (int j = 0; j < numComponentes - i - 1; j++) {
            comparacoes_algoritmo++;
            if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
                Componente temp = torre[j];
                torre[j] = torre[j + 1];
                torre[j + 1] = temp;
            }
        }
    }
}

void insertionSortTipo(CriterioOrdenacao criterio) {
    Componente chave;
    int i, j;

    for (i = 1; i < numComponentes; i++) {
        chave = torre[i];
        j = i - 1;

        while (j >= 0) {
            comparacoes_algoritmo++;
            if (strcmp(torre[j].tipo, chave.tipo) > 0) {
                torre[j + 1] = torre[j];
                j = j - 1;
            } else {
                break;
            }
        }
        torre[j + 1] = chave;
    }
}

void selectionSortPrioridade(CriterioOrdenacao criterio) {
    int i, j, indiceMin;

    for (i = 0; i < numComponentes - 1; i++) {
        indiceMin = i;
        for (j = i + 1; j < numComponentes; j++) {
            comparacoes_algoritmo++;
            if (torre[j].prioridade < torre[indiceMin].prioridade) {
                 indiceMin = j;
            }
        }
        if (indiceMin != i) {
            Componente temp = torre[i];
            torre[i] = torre[indiceMin];
            torre[indiceMin] = temp;
        }
    }
}

void menuOrdenacao() {
    int escolha;
    
    printf("\n--- ESCOLHA ESTRATEGIA DE ORDENACAO ---\n");
    printf("1. Bubble Sort (Ordem por NOME)\n");
    printf("2. Insertion Sort (Ordem por TIPO)\n");
    printf("3. Selection Sort (Ordem por PRIORIDADE)\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    void (*funcao_sort)();
    CriterioOrdenacao criterio_sort = CRITERIO_NOME;

    switch (escolha) {
        case 1:
            funcao_sort = (void (*)())bubbleSortNome;
            break;
        case 2:
            funcao_sort = (void (*)())insertionSortTipo;
            break;
        case 3:
            funcao_sort = (void (*)())selectionSortPrioridade;
            break;
        default:
            printf("\nEstrategia invalida.\n");
            return;
    }

    medirTempo(funcao_sort, criterio_sort);
    mostrarComponentes(torre, numComponentes);
}

void buscaBinariaPorNome(Componente componentes[], int tamanho, char nome_chave[]) {
    
    comparacoes_algoritmo = 0; 
    inicio_tempo = clock();
    
    int inicio = 0;
    int fim = tamanho - 1;
    int encontrado = -1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        comparacoes_algoritmo++;
        int cmp = strcmp(componentes[meio].nome, nome_chave);

        if (cmp == 0) {
            encontrado = meio;
            break;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    fim_tempo = clock();

    printf("\n--- RESULTADO DA BUSCA BINARIA (POR NOME) ---\n");
    printf("[METRICA] Tempo de Execucao: %.6f segundos.\n", (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC);
    printf("[METRICA] Comparações realizadas: %ld\n", comparacoes_algoritmo);
    
    if (encontrado != -1) {
        printf("[SUCESSO] COMPONENTE-CHAVE ENCONTRADO na posicao %d (Requisito 6).\n", encontrado);
        printf("Detalhes: Tipo=%s, Prioridade=%d\n", componentes[encontrado].tipo, componentes[encontrado].prioridade);
    } else {
        printf("[FALHA] Componente-chave '%s' nao localizado.\n", nome_chave);
    }
}

void executarBuscaBinaria() {
    if (numComponentes == 0) {
        printf("\nImpossivel buscar. A torre nao possui componentes.\n");
        return;
    }
    
    char chave[30];
    printf("\n--- BUSCA BINARIA ---\n");
    printf("Digite o NOME do COMPONENTE-CHAVE para ativar a torre: ");
    while (getchar() != '\n');
    fgets(chave, 30, stdin);
    chave[strcspn(chave, "\n")] = 0;

    buscaBinariaPorNome(torre, numComponentes, chave);
}


void menuVetor() {
    int op;
    do {
        limparTela();
        printf("====================================================\n");
        printf("= MODO VETOR (Sequencial) \n");
        printf("====================================================\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. ORDENAR (Visualiza Desempenho)\n");
        printf("5. Buscar Binaria (Visualiza Desempenho)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("----------------------------------------------------\n");
        
        printf("Escolha: ");
        scanf("%d", &op);
        
        switch(op) {
            case 1: cadastrarComponente(); break; 
            case 2: removerComponente(); break; 
            case 3: mostrarComponentes(torre, numComponentes); break;
            case 4: menuOrdenacao(); break;
            case 5: executarBuscaBinaria(); break;
            case 0: break;
            default: printf("\nOpcao invalida.\n"); getchar(); getchar();
        }
        if (op != 0 && op != 3) { getchar(); getchar(); }
    } while (op != 0);
}

void menuLista() {
    printf("\n-- MODO LISTA --\n");
    printf("Implementacao de Listas Encadeadas (Inserir, Remover, Listar, Busca Sequencial) para comparacao em desenvolvimento.\n");
    printf("Retornando ao menu principal.\n");
    getchar(); getchar();
}


int main() {
    int opcao;
    
    strcpy(torre[0].nome, "Chip Central"); torre[0].tipo[0] = 'C'; torre[0].prioridade = 1;
    strcpy(torre[1].nome, "Propulsor A"); torre[1].tipo[0] = 'P'; torre[1].prioridade = 5;
    strcpy(torre[2].nome, "Bateria Aux"); torre[2].tipo[0] = 'S'; torre[2].prioridade = 8;
    numComponentes = 3;

    do {
        exibirMenu();
        printf("Escolha aACAO: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            while (getchar() != '\n');
            opcao = -1; 
            continue;
        }

        switch (opcao) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 0:
                printf("\nModulo de organizacao encerrado. Fuga garantida!\n");
                break;
            default:
                printf("\nComando invalido.\n");
                getchar(); getchar();
        }
    } while (opcao != 0);

    return 0;
}
