#include "meushell.h"

// Função para o comando 'ajuda'
void ajuda() {
    printf("Comandos internos disponíveis:\n");
    printf("ajuda - Mostra esta mensagem de ajuda\n");
    printf("amb - Lista ou define variáveis de ambiente\n");
    printf("cd <diretorio> - Muda o diretório atual\n");
    printf("limpa - Limpa a tela do terminal\n");
    printf("sair - Sai do shell\n");
    // Adicionar mais descrições conforme necessário
}

// Função para o comando 'amb'
void amb(char **args, int arg_count) {
    if (arg_count == 1) {
        // Listar todas as variáveis de ambiente
    } else {
        // Definir ou modificar uma variável de ambiente
    }
}

// Função para o comando 'cd'
void cd(char *path) {
    if (path == NULL) {
        fprintf(stderr, "cd: argumento esperado\n");
    } else {
        if (chdir(path) != 0) {
            perror("cd");
        }
    }
}

// Função para o comando 'limpa'
void limpa() {
    // Código para limpar a tela do terminal
    // Pode variar dependendo do sistema operacional
}

// Função para o comando 'sair'
void sair() {
    exit(0);
}
