🧹 limpa-tex
Um utilitário de linha de comando, escrito em C, para limpar e organizar diretórios de projetos LaTeX de forma rápida e segura.

Sobre o Projeto
Este projeto nasceu de uma simples agonia: a bagunça de arquivos auxiliares (.aux, .log, .toc, etc.) que poluem a pasta de um projeto toda vez que um arquivo .tex é compilado.

Alternativas como o comando :Cleantex em editores como o Neovim são funcionais, mas muitas vezes exigem mais configuração ou passos do que o desejado. A ideia do limpa-tex é ser uma solução de um único comando, executado diretamente no terminal, que limpa o desnecessário e organiza o essencial.

✅ Funcionalidades
Exclusão Inteligente: Remove apenas os arquivos auxiliares gerados pelo LaTeX, preservando seus arquivos .tex e .pdf.

Segurança: Antes de apagar qualquer coisa, o script exibe uma lista de arquivos que serão removidos e pede sua confirmação. Um aviso especial é emitido para arquivos de tipo desconhecido, evitando a exclusão acidental de algo importante.

Organização: Após a limpeza, move todos os seus arquivos .tex para um subdiretório chamado Arquivos LaTeX, deixando o diretório principal limpo.

Autoproteção: O script é programado para não excluir a si mesmo (o executável limpatex e o código-fonte limpatex.c).

⚙️ Instalação e Configuração
Para usar o limpa-tex como um comando em qualquer diretório, siga estes passos:

Pré-requisitos
Você precisa ter um compilador C, como o gcc, instalado. Na maioria das distribuições Linux, ele pode ser instalado com o gerenciador de pacotes (ex: sudo apt install build-essential no Debian/Ubuntu ou sudo pacman -S base-devel no Arch Linux).

Passo 1: Compilar o Código
Navegue até a pasta do projeto e execute o seguinte comando para compilar o programa:

Bash

gcc -o limpatex limpatex.c
Isso criará um arquivo executável chamado limpatex.

Passo 2: Tornar o Comando Acessível
Para poder executar limpatex de qualquer lugar, mova o executável para um diretório que esteja no PATH do seu sistema. Uma boa prática é usar ~/.local/bin.

Bash

# Cria o diretório se ele não existir
mkdir -p ~/.local/bin

# Move o executável para lá
mv limpatex ~/.local/bin/
Passo 3: Criar um Alias (Atalho)
Para finalizar, adicione um alias ao arquivo de configuração do seu shell.

Para usuários Bash:

Abra o arquivo ~/.bashrc com seu editor de texto (ex: nano ~/.bashrc).

Adicione a seguinte linha ao final do arquivo:

Bash

alias limpatex='~/.local/bin/limpatex'
Para usuários Zsh:

Abra o arquivo ~/.zshrc com seu editor de texto (ex: nano ~/.zshrc).

Adicione a seguinte linha ao final do arquivo:

Bash

alias limpatex='~/.local/bin/limpatex'
Após salvar o arquivo, recarregue a configuração do seu terminal:

Bash

# Para Bash
source ~/.bashrc

# Ou para Zsh
source ~/.zshrc
▶️ Como Usar
Com a instalação concluída, o uso é muito simples.

Abra seu terminal.

Navegue até o diretório do seu projeto LaTeX que você deseja limpar.

Execute o comando:

Bash

limpatex
O programa irá analisar a pasta, mostrar os arquivos que serão removidos e pedir sua confirmação. Digite y para prosseguir.

Exemplo de Saída
$ limpatex
Os seguintes arquivos serão EXCLUÍDOS:
----------------------------------------
Arquivos auxiliares do LaTeX:
  - relatorio.aux
  - relatorio.log
  - relatorio.toc
----------------------------------------
!! ATENÇÃO: Arquivos DESCONHECIDOS !!
  - notas.txt
----------------------------------------
Deseja continuar? (y/n): y

Iniciando limpeza...
  [DELETADO] relatorio.aux
  [DELETADO] relatorio.log
  [DELETADO] relatorio.toc
  [DELETADO] notas.txt

Movendo arquivos .tex...
  [MOVIDO] relatorio.tex

Limpeza concluída!
