#include "receita.h"
#include "ingredientes.h"
#include "no.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ============================================
// FUNÇÕES DO MENU
// ============================================

void exibirMenu() {
    printf("\n\n");
    printf("----------------Menu----------------\n");    
    printf("\n\n");
    printf("1. Cadastrar Receita\n");
    printf("2. Remover Receita\n");
    printf("3. Listar Receitas\n");
    printf("4. Cadastrar Ingrediente em uma Receita\n");
    printf("5. Listar Ingredientes de uma Receita\n");
    printf("6. Listar Receitas por Ingrediente\n");
    printf("7. Encontrar Prato com Menor Preço\n");
    printf("8. Encontrar Ingrediente Mais Usado\n");
    printf("9. Encontrar Ingredientes em Comum entre Receitas\n");
    printf("10. Sair");
    printf("\n\n-----------------------------------------");
}

// ============================================
// FUNÇÕES DE CRIAÇÃO E LIMPEZA
// ============================================

Lista* criarLista() {
    Lista* novaLista = (Lista*)malloc(sizeof(Lista));
    if (novaLista != NULL) {
        novaLista->inicio = NULL;
        novaLista->fim = NULL;
        novaLista->tamanho = 0;
    }
    return novaLista;
}

void liberarLista(Lista* lista) {
    if (lista == NULL) return;

    No* atual = lista->inicio;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        liberarIngredientesInterno(&temp->ingredientes);
        free(temp);
    }
    free(lista);
}

// ============================================
// FUNÇÕES DE CADASTRO - COM I/O INTEGRADA
// ============================================

void cadastrarReceita(Lista* lista) {
    if (lista == NULL) return;

    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    // I/O: Leitura de dados da receita
    printf("\nDigite o nome do prato: ");
    fgets(novoNo->Nome, 100, stdin); 
    novoNo->Nome[strcspn(novoNo->Nome, "\n")] = '\0';

    printf("Digite o preço do prato: ");
    scanf("%f", &novoNo->preco);

    printf("Digite o número de ingredientes: ");
    int numIngredientes;
    scanf("%d", &numIngredientes);

    // Limpeza do buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Inicialização do descritor de ingredientes
    novoNo->ingredientes.inicio = NULL;
    novoNo->ingredientes.fim = NULL;
    novoNo->ingredientes.tamanho = 0;

    // Loop interno: adicionar ingredientes (função interna)
    for (int i = 0; i < numIngredientes; i++) {
        char buffer[100];
        printf("Digite o ingrediente %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        adicionarIngredienteInterno(&novoNo->ingredientes, buffer);
    }

    // Inicialização dos ponteiros de ligação
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;

    // Inserção na lista de receitas (loop externo)
    if (lista->inicio == NULL) {
        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else {
        lista->fim->proximo = novoNo;
        novoNo->anterior = lista->fim;
        lista->fim = novoNo;
    }
    lista->tamanho++;

    printf("Receita '%s' cadastrada com sucesso!\n", novoNo->Nome);
}

void removerReceita(Lista* lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    // I/O: Ler nome da receita
    char nome[100];
    printf("Digite o nome da receita a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    // Loop externo: encontrar receita
    No* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->Nome, nome) == 0) {
            // Ajuste de encadeamento para exclusão em lista dupla
            if (atual->anterior != NULL)
                atual->anterior->proximo = atual->proximo;
            else
                lista->inicio = atual->proximo;

            if (atual->proximo != NULL)
                atual->proximo->anterior = atual->anterior;
            else
                lista->fim = atual->anterior;

            // Libera ingredientes (loop interno)
            liberarIngredientesInterno(&atual->ingredientes);

            free(atual);
            lista->tamanho--;
            printf("Receita '%s' removida com sucesso.\n", nome);
            return;
        }
        atual = atual->proximo;
    }
    printf("Receita '%s' não encontrada.\n", nome);
}

void cadastrarIngredienteReceita(Lista* lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Lista de receitas vazia.\n");
        return;
    }

    // I/O: Ler nome da receita
    char nomePrato[100];
    printf("Digite o nome da receita: ");
    fgets(nomePrato, sizeof(nomePrato), stdin);
    nomePrato[strcspn(nomePrato, "\n")] = '\0';

    // Loop externo: encontrar receita
    No* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->Nome, nomePrato) == 0) {
            // I/O: Ler nome do ingrediente
            char buffer[100];
            printf("Digite o novo ingrediente: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';

            // Loop interno: adicionar ingrediente (função interna)
            adicionarIngredienteInterno(&atual->ingredientes, buffer);
            printf("Ingrediente adicionado com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Receita '%s' não encontrada.\n", nomePrato);
}

// ============================================
// FUNÇÕES DE LISTAGEM - COM I/O INTEGRADA
// ============================================

void listarReceitas(Lista* lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Nenhuma receita cadastrada.\n");
        return;
    }

    // Loop externo: percorrer receitas
    No* atual = lista->inicio;
    while (atual != NULL) {
        printf("\n--- Receita: %s ---\n", atual->Nome);
        printf("Preço: R$ %.2f\n", atual->preco);
        printf("Ingredientes:\n");
        
        // Loop interno: listar ingredientes (função interna)
        listarIngredientesInterno(&atual->ingredientes);
        
        atual = atual->proximo;
    }
}

void listarIngredientesReceita(Lista* lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    // I/O: Ler nome da receita
    char nomePrato[100];
    printf("Digite o nome da receita: ");
    fgets(nomePrato, sizeof(nomePrato), stdin);
    nomePrato[strcspn(nomePrato, "\n")] = '\0';

    // Loop externo: encontrar receita
    No* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->Nome, nomePrato) == 0) {
            printf("\nIngredientes de '%s':\n", nomePrato);
            // Loop interno: listar ingredientes (função interna)
            listarIngredientesInterno(&atual->ingredientes);
            return;
        }
        atual = atual->proximo;
    }
    printf("Receita '%s' não encontrada.\n", nomePrato);
}

void listarReceitasPorIngrediente(Lista* lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    // I/O: Ler nome do ingrediente
    char ingrediente[100];
    printf("Digite o ingrediente: ");
    fgets(ingrediente, sizeof(ingrediente), stdin);
    ingrediente[strcspn(ingrediente, "\n")] = '\0';

    printf("\nReceitas com o ingrediente '%s':\n", ingrediente);
    int found = 0;

    // Loop externo: percorrer receitas
    No* atual = lista->inicio;
    while (atual != NULL) {
        // Loop interno: procurar ingrediente na receita (função interna)
        if (encontrarIngredienteInterno(&atual->ingredientes, ingrediente)) {
            printf("  - %s (R$ %.2f)\n", atual->Nome, atual->preco);
            found = 1;
        }
        atual = atual->proximo;
    }

    if (!found) {
        printf("Nenhuma receita encontrada com o ingrediente '%s'.\n", ingrediente);
    }
}

// ============================================
// FUNÇÕES DE ANÁLISE - COM I/O INTEGRADA
// ============================================

void MenorPreco(Lista* lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    // Loop externo: encontrar receita com menor preço
    No* atual = lista->inicio;
    No* menorPrato = atual;
    float menor = atual->preco;

    while (atual != NULL) {
        if (atual->preco < menor) {
            menor = atual->preco;
            menorPrato = atual;
        }
        atual = atual->proximo;
    }

    printf("\n--- Prato com Menor Preço ---\n");
    printf("Nome: %s\n", menorPrato->Nome);
    printf("Preço: R$ %.2f\n", menorPrato->preco);
    printf("Ingredientes:\n");
    
    // Loop interno: listar ingredientes (função interna)
    listarIngredientesInterno(&menorPrato->ingredientes);
}

// ============================================
// ESTRUTURA AUXILIAR PARA CONTAGEM
// ============================================

typedef struct Freq {
    char nome[100];
    int contagem;
    struct Freq* proximo;
} Freq;

void registrarIngrediente(Freq** listaFreq, char* nomeIngrediente) {
    Freq* atual = *listaFreq;
    while (atual != NULL) {
        if (strcmp(atual->nome, nomeIngrediente) == 0) {
            atual->contagem++;
            return;
        }
        atual = atual->proximo;
    }
    Freq* novo = (Freq*)malloc(sizeof(Freq));
    if (novo != NULL) {
        strcpy(novo->nome, nomeIngrediente);
        novo->contagem = 1;
        novo->proximo = *listaFreq;
        *listaFreq = novo;
    }
}

void liberarFreq(Freq* listaFreq) {
    Freq* atual = listaFreq;
    while (atual != NULL) {
        Freq* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

void IngredienteMaisUsado(Lista* lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Freq* contagem = NULL;

    // Loop externo: percorrer receitas
    No* pratoAtual = lista->inicio;
    while (pratoAtual != NULL) {
        // Loop interno: percorrer ingredientes de cada receita (função interna implícita)
        NoIngrediente* ingAtual = pratoAtual->ingredientes.inicio;
        while (ingAtual != NULL) {
            registrarIngrediente(&contagem, ingAtual->ingrediente);
            ingAtual = ingAtual->proxima;
        }
        pratoAtual = pratoAtual->proximo;
    }

    // Encontrar a maior frequência
    int maiorFreq = 0;
    Freq* fAtual = contagem;
    while (fAtual != NULL) {
        if (fAtual->contagem > maiorFreq) {
            maiorFreq = fAtual->contagem;
        }
        fAtual = fAtual->proximo;
    }

    printf("\n--- Ingrediente(s) Mais Usado(s) ---\n");
    printf("Frequência: %d\n", maiorFreq);
    fAtual = contagem;
    while (fAtual != NULL) {
        if (fAtual->contagem == maiorFreq) {
            printf("  - %s\n", fAtual->nome);
        }
        fAtual = fAtual->proximo;
    }
    liberarFreq(contagem);
}

void IngredientesEmComum(Lista* lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Freq* contagem = NULL;

    // Loop externo: percorrer receitas
    No* pratoAtual = lista->inicio;
    while (pratoAtual != NULL) {
        // Loop interno: percorrer ingredientes de cada receita
        NoIngrediente* ingAtual = pratoAtual->ingredientes.inicio;
        while (ingAtual != NULL) {
            registrarIngrediente(&contagem, ingAtual->ingrediente);
            ingAtual = ingAtual->proxima;
        }
        pratoAtual = pratoAtual->proximo;
    }

    printf("\n--- Ingredientes Comuns (em mais de uma receita) ---\n");
    int found = 0;
    Freq* fAtual = contagem;
    while (fAtual != NULL) {
        if (fAtual->contagem > 1) {
            printf("  - %s (em %d receitas)\n", fAtual->nome, fAtual->contagem);
            found = 1;
        }
        fAtual = fAtual->proximo;
    }

    if (!found) {
        printf("Nenhum ingrediente em comum entre as receitas.\n");
    }

    liberarFreq(contagem);
}
