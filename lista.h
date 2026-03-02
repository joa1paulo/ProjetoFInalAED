#ifndef LISTA_H
#define LISTA_H
#include "ingredientes.h"

typedef struct No {
    char Nome[100];         
    Receita *ingredientes;  
    float preco;
    struct No* proximo;
    struct No* anterior;
} No;

typedef struct {
    No* inicio;
    int tamanho;
} Lista;

void exibirMenu();
Lista* criarLista();     
void cadastrarReceita(Lista* lista);
/*/
a função cadastrarReceita recebe somente a lista, pois o usuário informará
o nome do prato e os ingredientes,assim como o preço do prato a função irá criar um novo 
nó com essas informações e adicioná-lo à lista.
/*/

void removerReceita(Lista* lista, char* nome);
void listarReceitas(Lista* lista);
void listarReceitasPorIngrediente(Lista* lista, char* ingrediente);
void cadastrarIngredienteReceita(Lista* lista, char* nomePrato);
void listarIngredientesReceita(Lista* lista, char* nomePrato);
void MenorPreco(Lista* lista);
void IngredienteMaisUsado(Lista* lista);
void IngredientesEmComum(Lista* lista);


#endif