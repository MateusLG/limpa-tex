## limpa-tex
Um utilitário de linha de comando em C para limpar e organizar diretórios de projetos LaTeX.

## Como funciona
O programa, escrito em **C**, escaneia o diretório atual em busca de arquivos. Ele classifica os arquivos em três categorias:

1.  **Arquivos a serem mantidos:** `.tex`, `.pdf` e o próprio `limpatex`.
2.  **Arquivos de lixo conhecidos:** Extensões comuns geradas pelo LaTeX, como `.log`, `.aux`, `.toc`, etc.
3.  **Arquivos desconhecidos:** Qualquer outro tipo de arquivo que não se encaixe nas categorias acima.

Ele então exibe uma lista de todos os arquivos que serão excluídos (conhecidos e desconhecidos) e **pede sua confirmação**. Se você concordar, ele remove os arquivos e, por fim, move todos os `.tex` para uma pasta chamada `Arquivos LaTeX`.

## Como usar
Primeiro, compile o programa usando o `gcc`. Depois, basta executá-lo na pasta do seu projeto LaTeX.

1. Compile o código-fonte
```bash
gcc -o limpatex limpatex.c
```

2. Execute o programa
```bash
./limpatex
```

## Dicas
Para usar o limpatex como um comando global em seu terminal, você pode movê-lo para um diretório de binários e criar um alias.

1. Mova o executável:
É uma boa prática mover o arquivo compilado para ~/.local/bin, uma pasta que geralmente já está no PATH do sistema.

```bash
# Cria o diretorio se ele não existir
mkdir -p ~/.local/bin
# Move o executavel para lá
mv limpatex ~/.local/bin/
```

2. Crie o Alias (Atalho)
Para usuarios Bash:
1. Abra o arquivo ~/.bashrc com seu editor de texto e adicione o comando
2. Adicione a seguinte linha
```bash
alias limpatex='~/.local/bin/limpatex'
```

Para usuarios Zsh:
1. Abra o arquivo ~/.zshrc com seu editor de texto e adicione o comando
2. Adicione a seguinte linha
```bash
alias limpatex='~/.local/bin/limpatex'
```

3. Após salvar o arquivo, recarregue as configurações do seu terminal.
```bash
# Para Bash
source ~/.bashrc

# Ou para Zsh
source ~/.zshrc
```
