#include "lista.h"
#include "ingredientes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void exibirMenu() {
    printf("Menu:\n");
    printf("1. Cadastrar Receita\n");
    printf("2. Remover Receita\n");
    printf("3. Listar Receitas\n");
    printf("4. Cadastrar Ingrediente em uma Receita\n");
    printf("5. Listar Ingredientes de uma Receita\n");
    printf("6. Sair\n");
}

Lista* criarLista() {
    Lista* novaLista = (Lista*)malloc(sizeof(Lista));
    if (novaLista != NULL) {
        novaLista->inicio = NULL;
        novaLista->tamanho = 0;
    }
    return novaLista;
}

void cadastrarReceita(Lista* lista) {
    if (lista == NULL) return;

    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) return;

    int escolha;

    printf("Digite o nome do prato: ");
    fgets(novoNo->Nome, 100, stdin); // fgets para nao ter stack overflow
    novoNo->Nome[strcspn(novoNo->Nome, "\n")] = '\0'; // remove '\n' se houver

    printf("Digite o preço do prato: ");
    scanf("%f", &novoNo->preco);

    printf("digite o numero de ingredientes: ");
    scanf("%d", &escolha);
    // consumir o '\n' que ficou no buffer após scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // inicializa lista de ingredientes vazia
    novoNo->ingredientes = NULL;

    for (int i = 0; i < escolha; i++) {
        char buffer[100];
        printf("Digite o ingrediente %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        // remove a nova linha que o fgets deixa
        buffer[strcspn(buffer, "\n")] = '\0';

        Receita* novoIng = (Receita*)malloc(sizeof(Receita));
        if (novoIng == NULL) continue; // sem memória, pula
        novoIng->ingrediente = strdup(buffer);
        novoIng->proxima = NULL;

        // anexa na cauda da lista de ingredientes
        if (novoNo->ingredientes == NULL) {
            novoNo->ingredientes = novoIng;
        } else {
            Receita* p = novoNo->ingredientes;
            while (p->proxima != NULL) {
                p = p->proxima;
            }
            p->proxima = novoIng;
        }
    }

    novoNo->proximo = lista->inicio;
    novoNo->anterior = NULL;

    if (lista->inicio != NULL) {
        lista->inicio->anterior = novoNo;
    }
    
    lista->inicio = novoNo;
    lista->tamanho++;
}

