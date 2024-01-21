# Shell simplificada

Membros:
- Thallis André Faria Moreira
- Otávio Camargo Marciano
- Mariana Inacia Xavier Borges
- Isabella Beatriz da Silva

Este projeto consiste em um shell ou interpretador de linha simplificado para aplicação dos conhecimentos adiquiridos na disciplina de sistemas operacionais. Abrange a execução de alguns comandos implementados internamente, a possibilidade de usar comandos externos e trabalhar com arquivos.

## Execução

Para utilizar a shell, primeiramente, será necessário compilar. Para isso, certifique de possuir o compilador GCC instalado e digite o seguinte comando dentro da pasta do projeto:

    `gcc meushell.c history.c functions.c -o meushell

Então, digite:

    `./meushell

### Comandos internos

Comandos internos disponíveis:
- ajuda - Exibe mensagem com os comandos internos disponíveis e seus parâmetros
- amb - Lista ou define variáveis de ambiente
- cd <diretorio> - Muda o diretório atual
- limpa - Limpa a tela do terminal
- historico - Mostra o histórico de comandos
- sair - Sai do shell

O shell também suporta todos os comandos implementados pelo Linux.

## Redirecionamentos de entrada/saída



