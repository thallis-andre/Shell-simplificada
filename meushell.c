#include "meushell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char input[CMD_MAX_LENGTH];
    char *parsedArgs[50]; // Supondo um máximo de 50 argumentos
    int arg_count;
    int run = 1;
    initializeShellVars();

    while (run)
    {

        printf("> "); // Prompt do shell
        fgets(input, CMD_MAX_LENGTH, stdin);

        // Remover a nova linha (\n) do final da entrada
        if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
        {
            input[strlen(input) - 1] = '\0';
        }

        // Aqui você pode adicionar a lógica para dividir a entrada em um array de argumentos
        parseInput(input, parsedArgs, &arg_count);

        // Por exemplo, usando strtok ou uma função similar

        // Procurar na tabela de comandos
        for (int i = 0; commandTable[i].commandName != NULL; ++i)
        {
            if (strcmp(input, commandTable[i].commandName) == 0)
            {
                if (strcmp(parsedArgs[0], "cd") == 0)
                {
                    // Chamar 'cd' com o argumento apropriado
                    cd(parsedArgs[1]);
                }
                else
                {
                    // Chamar outras funções normalmente
                    commandTable[i].func(parsedArgs, arg_count);
                }

                break;
            }
        }
    }

    return 0;
}
