#ifndef INGREDIENTES_H
#define INGREDIENTES_H

#include "no.h"

// Tipo abstrato para operações com ingredientes
// Não expõe a estrutura interna

// Funções de manipulação interna de ingredientes
void adicionarIngredienteInterno(DescritorIngredientes* descritor, char* nomeIngrediente);
void listarIngredientesInterno(DescritorIngredientes* descritor);
void liberarIngredientesInterno(DescritorIngredientes* descritor);
int encontrarIngredienteInterno(DescritorIngredientes* descritor, char* nomeIngrediente);

#endif