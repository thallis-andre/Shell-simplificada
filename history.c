// history.c

#include "history.h"
#include <limits.h>  // Para a constante PATH_MAX
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Para a função getcwd

void addToHistory(CommandHistory *history, const char *command, const char *initialPath) {
    // Adiciona ao histórico em memória
    if (history->count < MAX_HISTORY_SIZE) {
        strncpy(history->commands[history->count], command, MAX_COMMAND_LENGTH - 1);
        history->commands[history->count][MAX_COMMAND_LENGTH - 1] = '\0';  // Garante terminação nula
        history->count++;
    } else {
        // Desloca os comandos existentes para abrir espaço para o novo comando
        for (int i = 0; i < MAX_HISTORY_SIZE - 1; i++) {
            strncpy(history->commands[i], history->commands[i + 1], MAX_COMMAND_LENGTH - 1);
            history->commands[i][MAX_COMMAND_LENGTH - 1] = '\0';  // Garante terminação nula
        }
        // Adiciona o novo comando no final
        strncpy(history->commands[MAX_HISTORY_SIZE - 1], command, MAX_COMMAND_LENGTH - 1);
        history->commands[MAX_HISTORY_SIZE - 1][MAX_COMMAND_LENGTH - 1] = '\0';  // Garante terminação nula
    }

    // Constrói o caminho completo do arquivo usando o caminho inicial
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/.meushell.hst", initialPath);

    // Adiciona ao histórico no arquivo
    FILE *file = fopen(filePath, "a");
    if (file != NULL) {
        fprintf(file, "%s\n", command);
        fclose(file);
        // Adicionando uma instrução printf para depuração
        // printf("Adicionado ao histórico e salvo no arquivo: %s\n", command);
    } else {
        perror("Erro ao abrir o arquivo de histórico para gravação");
    }
}

void loadHistoryFromFile(CommandHistory *history, const char *initialPath) {
    // Construa o caminho completo do arquivo de histórico
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/.meushell.hst", initialPath);

    FILE *file = fopen(filePath, "r");
    if (file != NULL) {
        char buffer[MAX_COMMAND_LENGTH];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0'; // Remover o caractere de nova linha
            }
            addToHistory(history, buffer, initialPath);
        }
        fclose(file);
    } else {
        perror("Erro ao abrir o arquivo de histórico para leitura");
    }
}



void printHistory(const CommandHistory *history) {
    printf("Histórico de comandos:\n");
    for (int i = 0; i < history->count; i++) {
        printf("%d: %s\n", i + 1, history->commands[i]);
    }
}