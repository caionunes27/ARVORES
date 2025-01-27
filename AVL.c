#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;
    struct no *esq, *dir;
    int altura;  // Altura da subárvore
} no;

// Função para criar um novo nó
no* criaNo(int valor) {
    no *novo = (no*) calloc(1, sizeof(no));
    if (!novo) {
        printf("Erro de alocacao\n");
        exit(1);
    }
    novo->chave = valor;
    novo->altura = 1;  // Altura inicial de um nó folha é 1
    return novo;
}

// Função para obter a altura de um nó
int altura(no* T) {
    return (T == NULL) ? 0 : T->altura;
}

// Função para obter o fator de balanceamento (altura da subárvore esquerda - altura da subárvore direita)
int fatorBalanceamento(no* T) {
    return (T == NULL) ? 0 : altura(T->esq) - altura(T->dir);
}

// Função para rotacionar à direita
no* rotacionaDireita(no* T) {
    no* novaRaiz = T->esq;
    T->esq = novaRaiz->dir;
    novaRaiz->dir = T;
    
    // Atualiza as alturas
    T->altura = 1 + (altura(T->esq) > altura(T->dir) ? altura(T->esq) : altura(T->dir));
    novaRaiz->altura = 1 + (altura(novaRaiz->esq) > altura(novaRaiz->dir) ? altura(novaRaiz->esq) : altura(novaRaiz->dir));

    return novaRaiz;
}

// Função para rotacionar à esquerda
no* rotacionaEsquerda(no* T) {
    no* novaRaiz = T->dir;
    T->dir = novaRaiz->esq;
    novaRaiz->esq = T;

    // Atualiza as alturas
    T->altura = 1 + (altura(T->esq) > altura(T->dir) ? altura(T->esq) : altura(T->dir));
    novaRaiz->altura = 1 + (altura(novaRaiz->esq) > altura(novaRaiz->dir) ? altura(novaRaiz->esq) : altura(novaRaiz->dir));

    return novaRaiz;
}

// Função para rotacionar à esquerda, seguida de rotação à direita (rotação dupla)
no* rotacionaEsquerdaDireita(no* T) {
    T->esq = rotacionaEsquerda(T->esq);
    return rotacionaDireita(T);
}

// Função para rotacionar à direita, seguida de rotação à esquerda (rotação dupla)
no* rotacionaDireitaEsquerda(no* T) {
    T->dir = rotacionaDireita(T->dir);
    return rotacionaEsquerda(T);
}

// Função de inserção de um novo nó, com balanceamento após a inserção
no* insere(no* T, int valor) {
    if (T == NULL) {
        return criaNo(valor);  // Cria um novo nó caso a árvore esteja vazia
    }

    // Caso da árvore binária de busca
    if (valor < T->chave) {
        T->esq = insere(T->esq, valor);
    } else if (valor > T->chave) {
        T->dir = insere(T->dir, valor);
    } else {
        return T;  // Se o valor já existe, não faz nada (não permite duplicatas)
    }

    // Atualiza a altura do nó
    T->altura = 1 + (altura(T->esq) > altura(T->dir) ? altura(T->esq) : altura(T->dir));

    // Verifica o fator de balanceamento do nó e realiza as rotações, se necessário
    int balance = fatorBalanceamento(T);

    // Caso 1: Desbalanceamento à esquerda
    if (balance > 1 && valor < T->esq->chave) {
        return rotacionaDireita(T);
    }

    // Caso 2: Desbalanceamento à direita
    if (balance < -1 && valor > T->dir->chave) {
        return rotacionaEsquerda(T);
    }

    // Caso 3: Desbalanceamento à esquerda à direita (rotação dupla)
    if (balance > 1 && valor > T->esq->chave) {
        return rotacionaEsquerdaDireita(T);
    }

    // Caso 4: Desbalanceamento à direita à esquerda (rotação dupla)
    if (balance < -1 && valor < T->dir->chave) {
        return rotacionaDireitaEsquerda(T);
    }

    return T;  // Retorna o nó atual (não foi necessário fazer nenhuma rotação)
}

// Função de busca
no* busca(no* T, int valor) {
    no *aux = T;
    while (aux != NULL) {
        if (aux->chave == valor) {
            return aux;
        } else if (aux->chave < valor) {
            aux = aux->dir;
        } else {
            aux = aux->esq;
        }
    }
    return NULL;  // Valor não encontrado
}

// Função para exibir o menu
void exibirMenu() {
    printf("\nEscolha uma opcao:\n");
    printf("0. Sair\n");
    printf("1. Inserir valor\n");
    printf("2. Buscar valor\n");
}

int main() {
    no* raiz = NULL;
    int opcao, valor;
    no* resultado;

    while (1) {
        exibirMenu();
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                exit(0);  // Encerra o programa

            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                raiz = insere(raiz, valor);
                printf("Valor %d inserido na árvore AVL.\n", valor);
                break;

            case 2:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                resultado = busca(raiz, valor);
                if (resultado != NULL) {
                    printf("Valor %d encontrado na árvore AVL.\n", valor);
                } else {
                    printf("Valor %d não encontrado na árvore AVL.\n", valor);
                }
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
    return 0;
}
