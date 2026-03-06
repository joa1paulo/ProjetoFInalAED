#ifndef RECEITA_H
#define RECEITA_H

#include "no.h"

// Tipo abstrato opaco - definido em no.h, mas não exposto ao main
// Apenas o typedef do no.h é usado

// Funções de menu
void exibirMenu();

// Funções de gerenciamento de receitas (com I/O integrada)
Lista* criarLista();
void cadastrarReceita(Lista* lista);
void removerReceita(Lista* lista);
void listarReceitas(Lista* lista);

// Funções de gerenciamento de ingredientes
void cadastrarIngredienteReceita(Lista* lista);
void listarIngredientesReceita(Lista* lista);
void listarReceitasPorIngrediente(Lista* lista);

// Funções de análise
void MenorPreco(Lista* lista);
void IngredienteMaisUsado(Lista* lista);
void IngredientesEmComum(Lista* lista);

// Função de limpeza
void liberarLista(Lista* lista);

#endif