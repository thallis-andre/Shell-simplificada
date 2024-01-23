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



## Instruções para Execução de Comandos a Partir de Arquivos no Shell Personalizado

Para executar comandos a partir de um arquivo em seu shell personalizado, siga os passos abaixo:

## Preparação do Arquivo de Comandos:

- Crie um arquivo de texto contendo uma série de comandos que você deseja executar. Cada comando deve estar em uma linha separada.
- Para comandos que requerem um pipe, use o símbolo | entre os comandos.

## Execução do Arquivo de Comandos:
No seu shell, execute a função executarComandosDeArquivo, passando o caminho do arquivo de comandos como argumento.
## Exemplo: executarComandosDeArquivo("caminho/para/comandos_teste.txt");
## Observações Importantes:
O shell processará cada linha do arquivo como um comando individual. Comandos com pipes serão processados adequadamente.

O shell também suporta todos os comandos implementados pelo Linux.
## Redirecionamentos de entrada/saída



