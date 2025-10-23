#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#define MAX_ITENS 10 // Capacidade do Vetor

struct Item {
    char nome[30];
    char tipo[20]; 
    int quantidade;
};

struct Item mochilaVetor[MAX_ITENS];
int contador_itens_vetor = 0;
long comparacoes_sequencial_vetor = 0;
long comparacoes_binaria_vetor = 0;


struct No {
    struct Item dados; 
    struct No* proximo;
};

struct No* inicioLista = NULL;
long comparacoes_sequencial_lista = 0;

void limparTela() {
    for (int i = 0; i < 30; i++) {
        printf("\n");
    }
}

void exibirMenuPrincipal() {
    limparTela();
    printf("================================================================\n");
    printf("= DESAFIO DE COMPARACAO: VETOR (SEQUENCIAL) vs LISTA (DINAMICA) =\n");
    printf("================================================================\n");
    printf("Vetor (Itens: %d/%d) | Lista (Nós alocados)\n", contador_itens_vetor, MAX_ITENS);
    printf("----------------------------------------------------------------\n");
    printf("1. Usar MODO VETOR (Suporta Ordenacao e Busca Binaria)\n");
    printf("2. Usar MODO LISTA (Operacoes Dinamicas)\n");
    printf("0. Sair\n");
    printf("----------------------------------------------------------------\n");
}

void listarItensVetor() {
    printf("\n--- VETOR: LISTAGEM DE ITENS ---\n");
    if (contador_itens_vetor == 0) {
        printf("O vetor esta vazio.\n");
        return;
    }

    printf("%-4s | %-25s | %-15s | %s\n", "ID", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------------------------\n");
    
    for (int i = 0; i < contador_itens_vetor; i++) {
        printf("%-4d | %-25s | %-15s | %d\n", 
               i, 
               mochilaVetor[i].nome, 
               mochilaVetor[i].tipo, 
               mochilaVetor[i].quantidade);
    }
    printf("---------------------------------------------------------------\n");
}

void inserirItemVetor() {
    if (contador_itens_vetor >= MAX_ITENS) {
        printf("ERRO: Vetor cheio! Limite de %d.\n", MAX_ITENS);
        return;
    }

    struct Item novo_item;
    printf("\n--- VETOR: INSERIR NOVO ITEM ---\n");
    
    printf("Nome: ");
    while (getchar() != '\n'); 
    fgets(novo_item.nome, sizeof(novo_item.nome), stdin);
    novo_item.nome[strcspn(novo_item.nome, "\n")] = 0; 

    printf("Tipo: ");
    scanf("%19s", novo_item.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo_item.quantidade);
    
    if (novo_item.quantidade <= 0) {
        printf("Quantidade invalida.\n");
        return;
    }
    
    mochilaVetor[contador_itens_vetor] = novo_item;
    contador_itens_vetor++;
    
    printf("Item '%s' adicionado ao vetor.\n", novo_item.nome);
    listarItensVetor();
}

void removerItemVetor() {
    char nome_remover[30];
    printf("\n--- VETOR: REMOVER ITEM ---\n");
    printf("Nome para remover: ");
    
    while (getchar() != '\n'); 
    fgets(nome_remover, sizeof(nome_remover), stdin);
    nome_remover[strcspn(nome_remover, "\n")] = 0;

    int indice_remover = -1;

    for (int i = 0; i < contador_itens_vetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome_remover) == 0) {
            indice_remover = i;
            break;
        }
    }

    if (indice_remover == -1) {
        printf("ERRO: Item '%s' nao encontrado no vetor.\n", nome_remover);
        return;
    }

    for (int i = indice_remover; i < contador_itens_vetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }
    
    contador_itens_vetor--;
    
    printf("Item '%s' removido do vetor com sucesso.\n", nome_remover);
    listarItensVetor();
}


void buscarSequencialVetor() {
    char nome_busca[30];
    printf("\n--- VETOR: BUSCA SEQUENCIAL ---\n");
    printf("Nome para buscar: ");
    
    while (getchar() != '\n'); 
    fgets(nome_busca, sizeof(nome_busca), stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    comparacoes_sequencial_vetor = 0;
    int indice_encontrado = -1;

    for (int i = 0; i < contador_itens_vetor; i++) {
        comparacoes_sequencial_vetor++; 
        if (strcmp(mochilaVetor[i].nome, nome_busca) == 0) {
            indice_encontrado = i;
            break; 
        }
    }

    if (indice_encontrado != -1) {
        printf("\n[VETOR] ENCONTRADO (Sequencial) na posicao: %d\n", indice_encontrado);
        printf("Detalhes: Tipo=%s, Qtd=%d\n", mochilaVetor[indice_encontrado].tipo, mochilaVetor[indice_encontrado].quantidade);
    } else {
        printf("\n[VETOR] Item '%s' nao encontrado.\n", nome_busca);
    }
    printf("[METRICA] Comparações na Busca Sequencial (Vetor): %ld\n", comparacoes_sequencial_vetor);
}

void ordenarVetor() {
    printf("\n--- VETOR: ORDENANDO POR NOME (Bubble Sort) ---\n");
    comparacoes_sequencial_vetor = 0; 
    
    time_t inicio = time(NULL); 

    for (int i = 0; i < contador_itens_vetor - 1; i++) {
        for (int j = 0; j < contador_itens_vetor - i - 1; j++) {
            comparacoes_sequencial_vetor++; // Contabiliza comparação do sort
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                struct Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    
    time_t fim = time(NULL);
    printf("[METRICA] Tempo de Ordenacao: %ld segundos (Aproximado).\n", fim - inicio);
    printf("[METRICA] Comparações na Ordenação: %ld\n", comparacoes_sequencial_vetor);
    listarItensVetor();
}

void buscarBinariaVetor() {
    printf("\n--- VETOR: BUSCA BINARIA (Requer ORDENACAO PREVIA) ---\n");
    char nome_busca[30];
    printf("Nome para busca rapida: ");
    
    while (getchar() != '\n'); 
    fgets(nome_busca, sizeof(nome_busca), stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;
    
    comparacoes_binaria_vetor = 0;
    time_t inicio = time(NULL);
    
    int inicio = 0;
    int fim = contador_itens_vetor - 1;
    int encontrado = -1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        comparacoes_binaria_vetor++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome_busca);

        if (cmp == 0) {
            encontrado = meio;
            break;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    time_t fim = time(NULL);

    printf("\n[METRICA] Tempo de Busca Binaria: %ld segundos (Aproximado).\n", fim - inicio);
    printf("[METRICA] Comparações na Busca Binaria (Vetor): %ld\n", comparacoes_binaria_vetor);
    
    if (encontrado != -1) {
        printf("[VETOR] ITEM ENCONTRADO RAPIDAMENTE na posicao: %d\n", encontrado);
    } else {
        printf("[VETOR] Item '%s' nao localizado.\n", nome_busca);
    }
}

void menuVetor() {
    int op;
    do {
        limparTela();
        printf("====================================================\n");
        printf("= MODO VETOR (SEQUENCIAL) \n");
        printf("====================================================\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. ORDENAR por Nome (Bubble Sort) -> Habilita Busca Binaria\n");
        printf("5. Buscar Sequencial (Medir Comparações)\n");
        printf("6. Buscar BINARIA (Medir Tempo e Comparações)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("----------------------------------------------------\n");
        
        printf("Escolha: ");
        scanf("%d", &op);
        
        switch(op) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: ordenarVetor(); break;
            case 5: buscarSequencialVetor(); break;
            case 6: buscarBinariaVetor(); break;
            case 0: break;
            default: printf("\nOpcao invalida.\n"); getchar(); getchar();
        }
        if (op != 0 && op != 3) { getchar(); getchar(); }
    } while (op != 0);
}

void listarItensLista() {
    struct No* atual = inicioLista;
    int count = 0;
    
    printf("\n--- LISTA ENCADEADA: LISTAGEM ---\n");
    if (atual == NULL) {
        printf("A lista esta vazia.\n");
    } else {
        printf("%-4s | %-25s | %-15s | %s\n", "ID", "NOME", "TIPO", "QUANTIDADE");
        while (atual != NULL) {
            printf("%-4d | %-25s | %-15s | %d\n", 
                   count++,
                   atual->dados.nome,
                   atual->dados.tipo,
                   atual->dados.quantidade);
            atual = atual->proximo;
        }
    }
}

void inserirItemLista() {
    struct No* novoNo = (struct No*) malloc(sizeof(struct No));
    if (!novoNo) {
        printf("\n[LISTA] ERRO de alocacao de memoria.\n");
        return;
    }
    
    printf("\n--- LISTA: INSERIR NOVO ITEM ---\n");
    
    printf("Nome: ");
    while (getchar() != '\n'); 
    fgets(novoNo->dados.nome, sizeof(novoNo->dados.nome), stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = 0; 

    printf("Tipo: ");
    scanf("%19s", novoNo->dados.tipo);
    
    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    
    novoNo->proximo = inicioLista;
    inicioLista = novoNo;

    printf("\n[LISTA] Item inserido no cabecalho com sucesso.\n");
}

void removerItemLista() {
    char nome[30];
    printf("\n--- LISTA: REMOVER ITEM ---\n");
    printf("Nome do item a remover: ");
    while (getchar() != '\n');
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    struct No* atual = inicioLista;
    struct No* anterior = NULL;
    
    // Busca sequencial (O(n))
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual == NULL) {
        printf("\n[LISTA] Item '%s' nao encontrado.\n", nome);
    } else {
        if (anterior == NULL) { 
            inicioLista = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
        free(atual); 
        printf("\n[LISTA] Item '%s' removido com sucesso.\n", nome);
    }
}

void buscarSequencialLista() {
    char nome[30];
    printf("\n--- LISTA: BUSCA SEQUENCIAL ---\n");
    printf("Nome do item a buscar: ");
    while (getchar() != '\n');
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    struct No* atual = inicioLista;
    int pos = 0;
    comparacoes_sequencial_lista = 0;
    
    while (atual != NULL) {
        comparacoes_sequencial_lista++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\n[LISTA] ENCONTRADO (Sequencial) na posicao %d.\n", pos);
            printf("Detalhes: Tipo=%s, Qtd=%d\n", atual->dados.tipo, atual->dados.quantidade);
            printf("[METRICA] Comparações na Busca Sequencial (Lista): %ld\n", comparacoes_sequencial_lista);
            return;
        }
        atual = atual->proximo;
        pos++;
    }
    printf("\n[LISTA] Item '%s' nao encontrado.\n", nome);
    printf("[METRICA] Comparações na Busca Sequencial (Lista): %ld\n", comparacoes_sequencial_lista);
}


void menuLista() {
    int op;
    do {
        limparTela();
        printf("====================================================\n");
        printf("= MODO LISTA ENCADEADA (DINAMICA) \n");
        printf("====================================================\n");
        printf("1. Inserir Item (Rapido, no inicio)\n");
        printf("2. Remover Item (por nome)\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Sequencial (Medir Comparações)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("----------------------------------------------------\n");
        
        printf("Escolha: ");
        scanf("%d", &op);
        
        switch(op) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarSequencialLista(); break;
            case 0: break;
            default: printf("\nOpcao invalida.\n"); getchar(); getchar();
        }
        if (op != 0 && op != 3) { getchar(); getchar(); }
    } while (op != 0);
}


int main() {
    int opcao_principal;
    
    strcpy(mochilaVetor[0].nome, "Pistola Laser");
    strcpy(mochilaVetor[0].tipo, "Arma");
    mochilaVetor[0].quantidade = 1;
    contador_itens_vetor = 1;
    
    struct No* novo = (struct No*) malloc(sizeof(struct No));
    strcpy(novo->dados.nome, "Kit Primeiros Socorros");
    strcpy(novo->dados.tipo, "Cura");
    novo->dados.quantidade = 2;
    novo->proximo = NULL;
    inicioLista = novo;

    do {
        exibirMenuPrincipal();
        printf("Escolha o MODO: ");
        
        if (scanf("%d", &opcao_principal) != 1) {
            printf("Entrada de comando invalida.\n");
            while (getchar() != '\n');
            opcao_principal = -1; 
            continue;
        }

        switch (opcao_principal) {
            case 1:
                menuVetor(); 
                break;
            case 2:
                menuLista(); 
                break;
            case 0:
                printf("\nSaindo do sistema. Analise comparativa concluida.\n");
                break;
            default:
                printf("\nOpcao de modo invalida.\n");
                getchar(); getchar();
        }
    } while (opcao_principal != 0);

    return 0;
}
