#include "meushell.h"
#include "history.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char initialPath[PATH_MAX];

void clearHistory() {
    FILE *file = fopen(".meushell.hst", "w");
    if (file != NULL) {
        fclose(file);
    } else {
        perror("Erro ao abrir o arquivo de histórico para truncamento");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char input[CMD_MAX_LENGTH];
    char *parsedArgs[50];
    int arg_count;
    int run = 1;
    initializeShellVars();
    carregarConfiguracoes();
    clearHistory();  // Limpa o histórico no início do programa

    // Obtém o diretório inicial
    if (getcwd(initialPath, sizeof(initialPath)) == NULL) {
        perror("Erro ao obter o diretório inicial");
        return 1;
    }

    // Inicializa a estrutura do histórico
    CommandHistory history;
    history.count = 0;
    loadHistoryFromFile(&history, initialPath);  // Carrega o histórico existente

    while (run) {
        for (int i = 0; i < shellVarCount; i++) {
            if (strcmp(shellVars[i].name, "PRONTO") == 0) {
                printf("%s$ ", shellVars[i].value);
                break;
            }
        }

        fgets(input, CMD_MAX_LENGTH, stdin);

        if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n')) {
            input[strlen(input) - 1] = '\0';
        }

        parseInput(input, parsedArgs, &arg_count);

        if (strcmp(parsedArgs[0], "historico") == 0) {
            printHistory(&history);  // Imprime o histórico
        } else {
            int found = 0;

            if (strcmp(parsedArgs[0], "cd") == 0) {
                cd(parsedArgs[1]);
                found = 1;
            } else {
                for (int i = 0; commandTable[i].commandName != NULL; ++i) {
                    if (strcmp(input, commandTable[i].commandName) == 0) {
                        commandTable[i].func(parsedArgs, arg_count);
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    if (executarComandoExterno(input) != 0) {  // Supondo que executarComandoExterno retorne 0 em caso de sucesso
                        // Se não for um comando externo, verifique se é um arquivo
                        if (access(input, F_OK) != -1) {
                            printf("'%s' é um caminho de arquivo válido.\n", input);
                            executarComandosDeArquivo(input);
                        } else {
                            printf("Comando ou arquivo '%s' não encontrado.\n", input);
                        }
                    }
                }
            }

            // Adiciona o comando ao histórico, verificando se é diferente do último comando
            if (history.count == 0 || strcmp(history.commands[history.count - 1], input) != 0) {
                // Chama addToHistory, passando o caminho inicial
                addToHistory(&history, input, initialPath);
            }
        }
    }

    return 0;
}
