#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10 

struct Item {
    char nome[30];
    char tipo[20]; 
    int quantidade;
};

struct Item mochila[MAX_ITENS];
int contador_itens = 0; 

void listarItens();
void inserirItem();
void removerItem();
void buscarItem();

void listarItens() {
    printf("\n--- Mochila (Itens Atuais: %d/%d) ---\n", contador_itens, MAX_ITENS);
    if (contador_itens == 0) {
        printf("A mochila esta vazia. Colete recursos essenciais!\n");
        return;
    }

    printf("%-4s | %-25s | %-15s | %s\n", "ID", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------------------------\n");
    
    for (int i = 0; i < contador_itens; i++) {
        printf("%-4d | %-25s | %-15s | %d\n", 
               i, 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    printf("---------------------------------------------------------------\n");
}

void inserirItem() {
    if (contador_itens >= MAX_ITENS) {
        printf("ERRO: A mochila esta cheia! Limite de %d itens alcancado.\n", MAX_ITENS);
        return;
    }

    struct Item novo_item;
    printf("\n--- Cadastro de Novo Item ---\n");
    
    printf("Digite o NOME do item: ");
    while (getchar() != '\n'); 
    fgets(novo_item.nome, sizeof(novo_item.nome), stdin);
    novo_item.nome[strcspn(novo_item.nome, "\n")] = 0; 

    printf("Digite o TIPO do item (ex: arma, cura): ");
    scanf("%19s", novo_item.tipo);

    printf("Digite a QUANTIDADE: ");
    scanf("%d", &novo_item.quantidade);

    if (novo_item.quantidade <= 0) {
        printf("A quantidade deve ser maior que zero. Item nao cadastrado.\n");
        return;
    }
    
    mochila[contador_itens] = novo_item;
    contador_itens++;
    
    printf("Item '%s' adicionado com sucesso!\n", novo_item.nome);
    listarItens();
}

void removerItem() {
    char nome_remover[30];
    printf("\n--- Remocao de Item ---\n");
    printf("Digite o NOME do item a ser REMOVIDO: ");
    
    while (getchar() != '\n'); 
    fgets(nome_remover, sizeof(nome_remover), stdin);
    nome_remover[strcspn(nome_remover, "\n")] = 0;

    int indice_remover = -1;

    for (int i = 0; i < contador_itens; i++) {
        if (strcmp(mochila[i].nome, nome_remover) == 0) {
            indice_remover = i;
            break;
        }
    }

    if (indice_remover == -1) {
        printf("ERRO: Item '%s' nao encontrado para remocao.\n", nome_remover);
        return;
    }

    for (int i = indice_remover; i < contador_itens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    
    contador_itens--;
    
    printf("Item '%s' removido com sucesso!\n", nome_remover);
    listarItens();
}

void buscarItem() {
    char nome_busca[30];
    printf("\n--- Busca de Item ---\n");
    printf("Digite o NOME do item para buscar: ");
    
    while (getchar() != '\n'); 
    fgets(nome_busca, sizeof(nome_busca), stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    int indice_encontrado = -1;

    for (int i = 0; i < contador_itens; i++) {
        if (strcmp(mochila[i].nome, nome_busca) == 0) {
            indice_encontrado = i;
            break;
        }
    }

    if (indice_encontrado != -1) {
        printf("\nItem ENCONTRADO na posicao (ID): %d\n", indice_encontrado);
        printf("Detalhes:\n");
        printf("  Nome: %s\n", mochila[indice_encontrado].nome);
        printf("  Tipo: %s\n", mochila[indice_encontrado].tipo);
        printf("  Quantidade: %d\n", mochila[indice_encontrado].quantidade);
    } else {
        printf("Item '%s' nao encontrado na mochila.\n", nome_busca);
    }
}

int main() {
    int opcao;
    printf("****************************************************\n");
    printf("* BEM-VINDO AO GERENCIADOR DE MOCHILA (NIVEL 1) *\n");
    printf("****************************************************\n");

    do {
        printf("\n--- MENU DO JOGO ---\n");
        printf("1. Inserir Item (Coletar Loot)\n");
        printf("2. Remover Item (Descartar/Usar)\n");
        printf("3. Listar Itens (Checar Inventario)\n");
        printf("4. Buscar Item (Procurar Recurso)\n");
        printf("5. Sair do Sistema\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n');
            opcao = 0;
            continue;
        }

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("\nSalvando progresso e saindo do gerenciador. Boa sorte na aventura!\n");
                break;
            default:
                printf("Opcao invalida. Por favor, escolha entre 1 e 5.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}
