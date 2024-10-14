//Lista duplamente encadeada

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da lista 
struct no {
    int chave; // Armazena a chave
    int elem;  // Armazena a informação
    struct no *prox; // Ponteiro do próximo nó
    struct no *ant;  // Ponteiro do nó anterior
};

// Criar um novo nó
struct no* criaNo(int chave, int elem) {
    struct no* novo = (struct no*)malloc(sizeof(struct no)); //Aloca a meméria para o nó
    novo->chave = chave; //Define a chave 
    novo->elem = elem; //Define o valor do elemento
    novo->prox = NULL; // Como é o primeiro nó adicionado não tem proximo
    novo->ant = NULL; //Como é o primeiro nó adicionado não tem proximo
    return novo; //Retorna o nó que foi criado
}

//Função de busca

struct no* buscar(struct no* inicio, int chave) {
    struct no* atual = inicio;  // Começa no início da lista
    while (atual != NULL && atual->chave != chave) { //Compara a chave do nó atual com a chave que estamos procurando
        atual = atual->prox;    // Avança para o próximo nó
    }
    return atual;  // Retorna o nó encontrado ou NULL se não encontra
}

//Funções de inserir

//a) Inserir no inicio da lista

void inserirInicio(struct no** inicio, int chave, int elem) {
    struct no* novo = criaNo(chave, elem);  // Cria um novo nó
    novo->prox = *inicio;   // O próximo do novo nó será o nó que era antes o primeiro

    if (*inicio != NULL) {
        (*inicio)->ant = novo;  // O antigo primeiro nó agora aponta para o novo como "anterior"
    }
    *inicio = novo;  // Atualiza o ponteiro de início para o novo nó
}

//b) Inserir no final da lista

void inserirFinal(struct no** inicio, int chave, int elem) {
    struct no* novo = criaNo(chave, elem);  // Cria um novo nó

    if (*inicio == NULL) {
        *inicio = novo;  // Se a lista estiver vazia, o novo nó será o primeiro
        return;
    }

    struct no* temp = *inicio;
    while (temp->prox != NULL) {
        temp = temp->prox;  // Percorre até o último nó
    }
    temp->prox = novo;      // O último nó agora aponta para o novo nó
    novo->ant = temp;       // O novo nó aponta para o último nó como "anterior"
}

//Função para remover da lista

void removerNo(struct no** inicio, int chave) {
    struct no* temp = buscar(*inicio, chave);  // Busca o nó usando a chave

    if (temp == NULL) {
        printf("O nó com chave %d não foi encontrado.\n", chave);
        return;
    }
//Podemos ter vários casos

//a) Caso o nó seja o primeiro da lista
    if (temp->ant == NULL) {
        *inicio = temp->prox;  // O segundo nó se torna o primeiro
    } else {
        temp->ant->prox = temp->prox;  // O nó anterior aponta para o próximo
    }

//  b) Caso o nó não seja o último da lista
    if (temp->prox != NULL) {
        temp->prox->ant = temp->ant;  // O nó seguinte aponta para o anterior
    }

    free(temp);  // Libera a memória
    printf("O nó com chave %d foi removido.\n", chave);
}

//Imprimir

void imprimirLista(struct no* inicio) {
    struct no* atual = inicio;
    printf("Lista atual: ");
    while (atual != NULL) {
        printf("[Chave: %d, Elem: %d] ", atual->chave, atual->elem);
        atual = atual->prox;
    }
    printf("\n");
}

//Função para execução - Main

int main() {
    struct no* inicio = NULL;  // Ponteiro para o início da lista
    int opcao, chave, elem;
    
    do {
        printf("\nMenu:\n");
        printf("1. Inserir nó\n");
        printf("2. Remover nó\n");
        printf("3. Buscar nó\n");
        printf("4. Imprimir lista\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:  // Inserir nó
                printf("Digite a chave do nó: ");
                scanf("%d", &chave);
                printf("Digite o valor do elemento: ");
                scanf("%d", &elem);
                inserirInicio(&inicio, chave, elem);
                printf("O nó foi inserido com sucesso!\n");
                break;
                
            case 2:  // Remover nó
                printf("Digite a chave do nó a ser removido: ");
                scanf("%d", &chave);
                removerNo(&inicio, chave);
                break;
                
            case 3:  // Buscar nó
                printf("Digite a chave do nó a ser buscado: ");
                scanf("%d", &chave);
                struct no* resultado = buscar(inicio, chave);
                if (resultado != NULL) {
                    printf("O nó foi encontrado: chave = %d, elem = %d\n", resultado->chave, resultado->elem);
                } else {
                    printf("O nó com chave %d não foi encontrado.\n", chave);
                }
                break;
                
            case 4:  // Imprimir lista
                imprimirLista(inicio);
                break;
                
            case 5:  // Sair
                printf("Programa finalizado :P5\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);

    return 0;
}
