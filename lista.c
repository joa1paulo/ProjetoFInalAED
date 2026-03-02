#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void exibirMenu(){
    printf("\nMenu:\n");
    printf("1. Cadastrar Receita\n");
    printf("2. Remover Receita\n");
    printf("3. Listar Receitas\n");
    printf("4. Cadastrar Ingrediente em uma Receita\n");
    printf("5. Listar Ingredientes de uma Receita\n");
    printf("6. Listar Receitas por Ingrediente\n");
    printf("7. Menor Preco\n");
    printf("8. Ingrediente Mais Usado\n");
    printf("9. Ingredientes em Comum\n");
    printf("10. Sair\n");
}

Lista* criarLista(){
    Lista* novaLista = (Lista*)malloc(sizeof(Lista));
    if(novaLista != NULL){
        novaLista->inicio = NULL;
        novaLista->tamanho = 0;
    }
    return novaLista;
}

void cadastrarReceita(Lista* lista){
    if(lista == NULL) return;
    No* novoNo = (No*)malloc(sizeof(No));
    if(novoNo == NULL) return;
    int escolha;
    printf("Digite o nome do prato: ");
    fgets(novoNo->Nome, 100, stdin);
    novoNo->Nome[strcspn(novoNo->Nome, "\n")] = '\0';
    printf("Digite o preco do prato: ");
    scanf("%f", &novoNo->preco);
    printf("Digite o numero de ingredientes: ");
    scanf("%d", &escolha);
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    novoNo->ingredientes = NULL;
    for(int i = 0; i < escolha; i++){
        char buffer[100];
        printf("Digite o ingrediente %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        Receita* novoIng = (Receita*)malloc(sizeof(Receita));
        if(novoIng == NULL) continue;
        novoIng->ingrediente = strdup(buffer);
        novoIng->proxima = NULL;
        if(novoNo->ingredientes == NULL){
            novoNo->ingredientes = novoIng;
        }else{
            Receita* p = novoNo->ingredientes;
            while(p->proxima != NULL){
                p = p->proxima;
            }
            p->proxima = novoIng;
        }
    }
    novoNo->proximo = lista->inicio;
    novoNo->anterior = NULL;
    if(lista->inicio != NULL){
        lista->inicio->anterior = novoNo;
    }
    lista->inicio = novoNo;
    lista->tamanho++;
}
void cadastrarIngredienteReceita(Lista* lista, char* nomePrato){
    if(lista == NULL || lista->inicio == NULL) return;
    No* atual = lista->inicio;
    while(atual != NULL){
        if(strcmp(atual->Nome, nomePrato) == 0){
            char buffer[100];
            printf("Digite o novo ingrediente: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            Receita* novoIng = (Receita*)malloc(sizeof(Receita));
            if(novoIng != NULL){
                novoIng->ingrediente = strdup(buffer);
                novoIng->proxima = NULL;
                if(atual->ingredientes == NULL){
                    atual->ingredientes = novoIng;
                }else{
                    Receita* p = atual->ingredientes;
                    while(p->proxima != NULL){
                        p = p->proxima;
                    }
                    p->proxima = novoIng;
                }
            }
            break;
        }
        atual = atual->proximo;
    }
}

void listarIngredientesReceita(Lista* lista, char* nomePrato){
    if(lista == NULL || lista->inicio == NULL) return;
    No* atual = lista->inicio;
    while(atual != NULL){
        if(strcmp(atual->Nome, nomePrato) == 0){
            Receita* ingAtual = atual->ingredientes;
            while(ingAtual != NULL){
                printf("- %s\n", ingAtual->ingrediente);
                ingAtual = ingAtual->proxima;
            }
            return;
        }
        atual = atual->proximo;
    }
}

void MenorPreco(Lista* lista){
    if(lista == NULL || lista->inicio == NULL) return;
    No* atual = lista->inicio;
    No* menorPrato = atual;
    float menor = atual->preco;
    while(atual != NULL){
        if(atual->preco < menor){
            menor = atual->preco;
            menorPrato = atual;
        }
        atual = atual->proximo;
    }
    printf("Nome: %s\nPreco: %.2f\n", menorPrato->Nome, menorPrato->preco);
}

typedef struct Freq{
    char nome[100];
    int contagem;
    struct Freq* proximo;
} Freq;

void registrarIngrediente(Freq** listaFreq, char* nomeIngrediente){
    Freq* atual = *listaFreq;
    while(atual != NULL){
        if(strcmp(atual->nome, nomeIngrediente) == 0){
            atual->contagem++;
            return;
        }
        atual = atual->proximo;
    }
    Freq* novo = (Freq*)malloc(sizeof(Freq));
    if(novo != NULL){
        strcpy(novo->nome, nomeIngrediente);
        novo->contagem = 1;
        novo->proximo = *listaFreq;
        *listaFreq = novo;
    }
}

void liberarFreq(Freq* listaFreq){
    Freq* atual = listaFreq;
    while(atual != NULL){
        Freq* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

void IngredienteMaisUsado(Lista* lista){
    if(lista == NULL || lista->inicio == NULL) return;
    Freq* contagem = NULL;
    No* pratoAtual = lista->inicio;
    while(pratoAtual != NULL){
        Receita* ingAtual = pratoAtual->ingredientes;
        while(ingAtual != NULL){
            registrarIngrediente(&contagem, ingAtual->ingrediente);
            ingAtual = ingAtual->proxima;
        }
        pratoAtual = pratoAtual->proximo;
    }
    int maiorFreq = 0;
    Freq* fAtual = contagem;
    while(fAtual != NULL){
        if(fAtual->contagem > maiorFreq){
            maiorFreq = fAtual->contagem;
        }
        fAtual = fAtual->proximo;
    }
    fAtual = contagem;
    while(fAtual != NULL){
        if(fAtual->contagem == maiorFreq){
            printf("- %s\n", fAtual->nome);
        }
        fAtual = fAtual->proximo;
    }
    liberarFreq(contagem);
}

void IngredientesEmComum(Lista* lista){
    if(lista == NULL || lista->inicio == NULL) return;
    Freq* contagem = NULL;
    No* pratoAtual = lista->inicio;
    while(pratoAtual != NULL){
        Receita* ingAtual = pratoAtual->ingredientes;
        while(ingAtual != NULL){
            registrarIngrediente(&contagem, ingAtual->ingrediente);
            ingAtual = ingAtual->proxima;
        }
        pratoAtual = pratoAtual->proximo;
    }
    Freq* fAtual = contagem;
    while(fAtual != NULL){
        if(fAtual->contagem > 1){
            printf("- %s\n", fAtual->nome);
        }
        fAtual = fAtual->proximo;
    }
    liberarFreq(contagem);
}
