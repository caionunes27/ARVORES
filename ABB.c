#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;
    struct no *esq, *dir;
} no;

no* criaNo(int valor) {
    no *novo = (no*) calloc(1, sizeof(no));
    if (!novo) {
        printf("Erro de alocacao\n");
        exit(1);
    }
    novo->chave = valor;
    return novo;
}

// Função de inserção na árvore binária de busca
no* insere(no* T, int valor) {
    if (T == NULL) {
        return criaNo(valor);  // Se a árvore estiver vazia, cria um novo nó.
    }
    
    if (valor < T->chave) {
        T->esq = insere(T->esq, valor);  // Insere na subárvore esquerda
    } else if (valor > T->chave) {
        T->dir = insere(T->dir, valor);  // Insere na subárvore direita
    }
    // Se o valor já existir na árvore, não faz nada (não permite valores repetidos).
    return T;
}

// Função de remoção de um nó na árvore
no* remove(no* T, int valor) {
    if (T == NULL) return NULL;  // Árvore vazia, nada a fazer.

    if (valor < T->chave) {
        T->esq = remove(T->esq, valor);  // Recursivamente remove na subárvore esquerda.
    } else if (valor > T->chave) {
        T->dir = remove(T->dir, valor);  // Recursivamente remove na subárvore direita.
    } else {
        // Caso o nó a ser removido tenha 0 ou 1 filho:
        if (T->esq == NULL) {
            no* temp = T->dir;
            free(T);
            return temp;
        } else if (T->dir == NULL) {
            no* temp = T->esq;
            free(T);
            return temp;
        }

        // Caso o nó a ser removido tenha 2 filhos:
        no* sucessor = T->dir;
        while (sucessor->esq != NULL) {
            sucessor = sucessor->esq;  // Encontra o sucessor (menor valor na subárvore direita)
        }

        T->chave = sucessor->chave;  // Substitui o valor do nó a ser removido pelo valor do sucessor.
        T->dir = remove(T->dir, sucessor->chave);  // Remove o sucessor da árvore.
    }

    return T;
}

// Função de busca
no* busca(no* T, int valor) {
    no *aux = T;
    if (!T) return NULL;  // Se a árvore estiver vazia, retorna NULL.
    while (aux != NULL) {
        if (aux->chave == valor) return aux;  // Valor encontrado
        else if (aux->chave < valor) aux = aux->esq;  // Vai para a subárvore esquerda
        else aux = aux->dir;  // Vai para a subárvore direita
    }
    return NULL;  // Valor não encontrado
}

// Função para exibir o menu
void exibirMenu() {
    printf("\nEscolha uma opcao:\n");
    printf("0. Sair\n");
    printf("1. Inserir valor\n");
    printf("2. Buscar valor\n");
    printf("3. Remover valor\n");
}

int main() {
    no *raiz = NULL;
    int opcao, valor;
    no *resultado;

    while (1) {
        exibirMenu();
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                exit(0); 

            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                raiz = insere(raiz, valor);
                printf("Valor %d inserido na árvore.\n", valor);
                break;

            case 2:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                resultado = busca(raiz, valor);
                if (resultado != NULL) {
                    printf("Valor %d encontrado na árvore.\n", valor);
                } else {
                    printf("Valor %d não encontrado na árvore.\n", valor);
                }
                break;

            case 3:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                raiz = remove(raiz, valor);
                printf("Valor %d removido da árvore, se existia.\n", valor);
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
    return 0;
}
