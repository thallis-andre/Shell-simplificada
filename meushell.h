#ifndef MEUSHELL_H
#define MEUSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "globaldef.h"
#include "globalvar.h"

// Protótipos de funções para comandos internos
void ajuda();
void amb(char **args, int arg_count);
void cd(char *path);
void limpa();
void sair();
void parseInput(char* input, char** args, int* arg_count);
void initializeShellVars();
void carregarConfiguracoes();
int executarComandoExterno(char *comando);
void executarComandosDeArquivo(const char *arquivoComandos);


typedef struct {
    char name[MAX_VAR_NAME];
    char value[MAX_VAR_VALUE];
} ShellVar;

extern ShellVar shellVars[MAX_ENV_VARS];
extern int shellVarCount;

// Estrutura para mapear string para função
typedef void (*CommandFunc)();
typedef struct {
    char *commandName;
    CommandFunc func;
} CommandMap;

// Declaração externa da commandTable
extern CommandMap commandTable[];

#endif // MEUSHELL_H
