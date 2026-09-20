# 🔀 Pipex — 42 School

Reimplementação em C do comportamento de pipes do shell (`cmd1 | cmd2`), usando `fork`, `pipe`, `dup2` e `execve` diretamente, sem passar pelo shell.

## 🧠 Conceitos aplicados
- Criação de processos (`fork`, `wait`/`waitpid`)
- Comunicação entre processos via pipes (`pipe`, `dup2`)
- Resolução de executáveis via `PATH` (`execve`)
- Redirecionamento de file descriptors
- Tratamento de erros de sistema (`perror`, códigos de saída)

## ⚙️ Compilação
```bash
make            # compila o projeto principal (pipex)
make bonus      # compila a versão bonus (pipexb)
make clean      # remove .o
make fclean     # remove .o e binários
make re         # recompila do zero
```

## ▶️ Uso
```bash
./pipex file1 cmd1 cmd2 file2
```

Exemplo:
```bash
./pipex infile "cat" "wc -l" outfile
# equivalente a: < infile cat | wc -l > outfile
```

### Bonus
```bash
./pipexb file1 cmd1 cmd2 cmd3 ... file2
# suporta múltiplos comandos encadeados em pipe
```

## 🏗️ Estrutura
```
src/
├── main.c     # ponto de entrada e validação de argumentos
├── files.c    # abertura/criação dos arquivos de entrada e saída
├── cmds.c     # parsing e execução dos comandos
└── utils.c    # funções auxiliares
```

## 📌 Aprendizados
Este projeto aprofundou meu entendimento de como o shell realmente implementa pipes por baixo dos panos, e me forçou a lidar com gerenciamento cuidadoso de file descriptors e processos filhos.
