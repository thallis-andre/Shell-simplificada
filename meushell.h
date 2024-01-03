#ifndef MEUSHELL_H
#define MEUSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "globaldef.h"
#include "globalvar.h"

// Definição de um tipo de função de comando
typedef void (*CommandFunc)();

// Estrutura para mapear string para função
typedef struct
{
    char *commandName;
    CommandFunc func;
} CommandMap;

// Declaração externa da commandTable
extern CommandMap commandTable[];

// Protótipos de funções para comandos internos
void ajuda();
void cd(char *path);
void limpa();
void sair();

#endif // MEUSHELL_H
