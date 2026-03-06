#ifndef INGREDIENTES_H
#define INGREDIENTES_H

typedef struct Receita {
    char *ingrediente;
    struct Receita *proxima;
} Receita;

#endif