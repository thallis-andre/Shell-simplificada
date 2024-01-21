#include "meushell.h"
#include "history.h"  // Adicionando o cabeçalho do history.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __unix__
#include <sys/wait.h>
#endif

#define MAX_ARGS 50
#define ARG_LENGTH 100
#define MAX_ENV_VARS 100
#define MAX_VAR_NAME 50
#define MAX_VAR_VALUE 100

void ajuda() {
    printf("Comandos internos disponíveis:\n");
    printf("ajuda - Mostra esta mensagem de ajuda\n");
    printf("amb - Lista ou define variáveis de ambiente\n");
    printf("cd <diretorio> - Muda o diretório atual\n");
    printf("limpa - Limpa a tela do terminal\n");
    printf("sair - Sai do shell\n");
    printf("historico - Mostra o histórico de comandos\n");  // Adicionando o comando historico
}
// void amb(char **args, int arg_count) {
//     if (arg_count == 1) {
//         // Lista todas as variáveis de ambiente
//         for (char **env = environ; *env != 0; env++) {
//             char *thisEnv = *env;
//             printf("%s\n", thisEnv);
//         }
//     } else if (arg_count == 3 && strcmp(args[1], "=") == 0) {
//         // Define uma nova variável de ambiente
//         setenv(args[0], args[2], 1);
//     } else {
//         printf("Uso: amb <var> = <valor> para definir uma variável de ambiente, ou amb para listar todas.\n");
//     }
// }
ShellVar shellVars[MAX_ENV_VARS];
int shellVarCount = 0;

void initializeShellVars()
{
    // Inicializa as variáveis de ambiente padrão
    strcpy(shellVars[shellVarCount].name, "CAMINHO");
    strcpy(shellVars[shellVarCount++].value, "/bin:/usr/bin");

    strcpy(shellVars[shellVarCount].name, "DTA");
    getcwd(shellVars[shellVarCount++].value, MAX_VAR_VALUE);

    strcpy(shellVars[shellVarCount].name, "PRONTO");
    sprintf(shellVars[shellVarCount++].value, "%s >", shellVars[shellVarCount - 1].value);

#ifdef _WIN32
    // Windows-specific code
    strcpy(shellVars[shellVarCount].name, "HOST");
    DWORD size = MAX_VAR_VALUE;
    GetComputerName(shellVars[shellVarCount++].value, &size);
#else
    // Unix-specific code
    strcpy(shellVars[shellVarCount].name, "HOST");
    gethostname(shellVars[shellVarCount++].value, MAX_VAR_VALUE);
#endif

    strcpy(shellVars[shellVarCount].name, "SHELL");
    strcpy(shellVars[shellVarCount++].value, "meushell");
}

void updatePrompt()
{
    for (int i = 0; i < shellVarCount; i++)
    {
        if (strcmp(shellVars[i].name, "DTA") == 0)
        {
            for (int j = 0; j < shellVarCount; j++)
            {
                if (strcmp(shellVars[j].name, "PRONTO") == 0)
                {
                    sprintf(shellVars[j].value, "%s >", shellVars[i].value);
                    break;
                }
            }
            break;
        }
    }
}

void amb(char **args, int arg_count) {
    if (arg_count == 1) {
        // Listar todas as variáveis de ambiente
        for (int i = 0; i < shellVarCount; i++) {
            printf("%s=%s\n", shellVars[i].name, shellVars[i].value);
        }
    } else if (arg_count == 2) {
        char *arg = args[1];

        if (arg[0] == '$') {
            // Exibir o conteúdo de uma variável específica
            char *var_name = &arg[1];
            int found = 0;
            for (int i = 0; i < shellVarCount; i++) {
                if (strcmp(shellVars[i].name, var_name) == 0) {
                    printf("%s\n", shellVars[i].value);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Variável '%s' não encontrada.\n", var_name);
            }
        } else {
            // Configurar uma variável com um valor específico
            char *var_name = strtok(arg, "=");
            char *var_value = strtok(NULL, "=");

            if (var_name != NULL && var_value != NULL) {
                int found = 0;
                for (int i = 0; i < shellVarCount; i++) {
                    if (strcmp(shellVars[i].name, var_name) == 0) {
                        strcpy(shellVars[i].value, var_value);
                        found = 1;
                        break;
                    }
                }
                if (!found && shellVarCount < MAX_ENV_VARS) {
                    strcpy(shellVars[shellVarCount].name, var_name);
                    strcpy(shellVars[shellVarCount].value, var_value);
                    shellVarCount++;
                }
            } else {
                printf("Formato incorreto. Uso: amb VAR=<valor>\n");
            }
        }
    } else {
        printf("Uso incorreto. Comandos disponíveis: amb, amb $VAR, amb VAR=<valor>\n");
    }
}


#include <sys/stat.h> // Para struct stat e stat()

void cd(char *path) {

    if (path == NULL || strcmp(path, "~") == 0) {
        // Mudar para o diretório home se nenhum argumento for fornecido ou se for '~'
        path = getenv("HOME");
        if (path == NULL) {
            fprintf(stderr, "cd: diretório home não encontrado\n");
            return;
        }
    }

    struct stat statbuf;
    if (stat(path, &statbuf) != 0 || !S_ISDIR(statbuf.st_mode)) {
        // Verificar se o diretório existe e é um diretório
        fprintf(stderr, "cd: %s: No such file or directory\n", path);
        return;
    }

    if (chdir(path) != 0) {
        // Tentativa de mudar para o diretório especificado
        perror("cd");
    } else {
        // Atualiza a variável DTA
        char cwd[MAX_VAR_VALUE];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            for (int i = 0; i < shellVarCount; i++) {
                if (strcmp(shellVars[i].name, "DTA") == 0) {
                    strcpy(shellVars[i].value, cwd);
                    break;
                }
            }
        }
        // Chama updatePrompt para atualizar PRONTO
        updatePrompt();
    }
}


void limpa()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sair()
{
    exit(0);
}

void parseInput(char *input, char **args, int *arg_count)
{
    *arg_count = 0; // Reset contador de argumentos
    char *token = strtok(input, " ");

    while (token != NULL && *arg_count < MAX_ARGS)
    {
        args[*arg_count] = token;
        (*arg_count)++;
        token = strtok(NULL, " ");
    }

    args[*arg_count] = NULL; // Marcador de fim dos argumentos
}

void carregarConfiguracoes() {
    FILE *arquivo = fopen("meushell.rec", "r");
    if (arquivo == NULL) {
        perror("Arquivo de configuracoes nao encontrado");
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Processar cada linha e configurar as variáveis de ambiente
        char *chave = strtok(linha, "=");
        char *valor = strtok(NULL, "\n");

        if (chave != NULL && valor != NULL) {
            setenv(chave, valor, 1);  // 1 indica substituição se já existir
        }
    }

    fclose(arquivo);
}

void executarComandoExterno(char *comando) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Erro ao criar processo filho");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {  // Processo filho
        // O processo filho executa o comando externo
        execlp(comando, comando, (char *)NULL);

        // Se o execlp() falhar, imprima uma mensagem de erro
        perror("Erro ao executar o comando");
        exit(EXIT_FAILURE);
    } else {  // Processo pai
        // O processo pai espera pelo término do processo filho
        waitpid(pid, NULL, 0);
    }
}

// Nova função para imprimir o histórico
void imprimirHistorico(const char *initialPath) {
    CommandHistory history;
    history.count = 0;
    loadHistoryFromFile(&history, initialPath);
    printHistory(&history);
}

// Inicialização da commandTable
CommandMap commandTable[] = {
    {"ajuda", ajuda},
    {"amb", amb},
    {"cd", cd},
    {"limpa", limpa},
    {"sair", sair},
    {"historico", imprimirHistorico},  // Adicionando o comando historico
    {NULL, NULL} // Terminador da tabela
};