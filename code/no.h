#ifndef NO_H
#define NO_H

// Estrutura para um nó de ingrediente (lista duplamente encadeada)
typedef struct NoIngrediente {
    char *ingrediente;
    struct NoIngrediente *proxima;
    struct NoIngrediente *anterior;
} NoIngrediente;

// Descritor da lista de ingredientes (com início e fim)
typedef struct {
    NoIngrediente *inicio;
    NoIngrediente *fim;
    int tamanho;
} DescritorIngredientes;

// Estrutura para um nó da lista de receitas (duplamente encadeada)
typedef struct No {
    char Nome[100];         
    DescritorIngredientes ingredientes;
    float preco;
    struct No* proximo;
    struct No* anterior;
} No;

// Descritor da lista de receitas (com início e fim)
typedef struct {
    No* inicio;
    No* fim;
    int tamanho;
} Lista;

#endif
