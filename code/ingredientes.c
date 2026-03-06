#include "ingredientes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Função interna: adiciona um ingrediente ao descritor
void adicionarIngredienteInterno(DescritorIngredientes* descritor, char* nomeIngrediente) {
    if (descritor == NULL || nomeIngrediente == NULL) return;

    NoIngrediente* novoNo = (NoIngrediente*)malloc(sizeof(NoIngrediente));
    if (novoNo == NULL) return;

    novoNo->ingrediente = strdup(nomeIngrediente);
    novoNo->proxima = NULL;
    novoNo->anterior = NULL;

    if (descritor->inicio == NULL) {
        // Lista vazia
        descritor->inicio = novoNo;
        descritor->fim = novoNo;
    } else {
        // Adiciona no final da lista
        descritor->fim->proxima = novoNo;
        novoNo->anterior = descritor->fim;
        descritor->fim = novoNo;
    }
    descritor->tamanho++;
}

// Função interna: lista ingredientes do descritor
void listarIngredientesInterno(DescritorIngredientes* descritor) {
    if (descritor == NULL || descritor->inicio == NULL) {
        printf("  Nenhum ingrediente.\n");
        return;
    }
    
    NoIngrediente* atual = descritor->inicio;
    while (atual != NULL) {
        printf("  - %s\n", atual->ingrediente);
        atual = atual->proxima;
    }
}

// Função interna: libera memória dos ingredientes
void liberarIngredientesInterno(DescritorIngredientes* descritor) {
    if (descritor == NULL) return;

    NoIngrediente* atual = descritor->inicio;
    while (atual != NULL) {
        NoIngrediente* temp = atual;
        atual = atual->proxima;
        free(temp->ingrediente);
        free(temp);
    }
    descritor->inicio = NULL;
    descritor->fim = NULL;
    descritor->tamanho = 0;
}

// Função interna: encontra um ingrediente específico
int encontrarIngredienteInterno(DescritorIngredientes* descritor, char* nomeIngrediente) {
    if (descritor == NULL || descritor->inicio == NULL) return 0;

    NoIngrediente* atual = descritor->inicio;
    while (atual != NULL) {
        if (strcmp(atual->ingrediente, nomeIngrediente) == 0) {
            return 1;
        }
        atual = atual->proxima;
    }
    return 0;
}

