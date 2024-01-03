#define _GNU_SOURCE

#include "meushell.h"
#include "functions.c"

// Tabela de mapeamento de comandos
CommandMap commandTable[] = {
    {"ajuda", ajuda},
    {"sair", sair},
    {NULL, NULL} // Terminador da tabela
};

int main()
{
    while (1)
    {
        printf("> "); // Prompt do shell
        fgets(input, CMD_MAX_LENGTH, stdin);

        // Remover a nova linha (\n) do final da entrada
        if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
        {
            input[strlen(input) - 1] = '\0';
        }

        // Procurar na tabela de comandos
        for (int i = 0; commandTable[i].commandName != NULL; ++i)
        {
            if (strcmp(input, commandTable[i].commandName) == 0)
            {
                // Chamar a função correspondente
                commandTable[i].func();
                break;
            }
        }
    }

    return 0;
}

