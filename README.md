# UAIBank - Banco Digital em C

Simulação de um banco digital via terminal, desenvolvida em C como
trabalho final da disciplina Laboratório de ICC 1 (USP/ICMC).

## Funcionalidades
- Cadastro de usuário (individual e em lote), com validação de nome, idade e saldo
- Busca de usuário por ID
- Transferência entre usuários, com validação de saldo
- Exclusão de usuário por ID
- Persistência dos dados em arquivo (arqq.txt)

## Conceitos aplicados
- Structs e ponteiros
- Alocação dinâmica de memória (malloc/realloc)
- Manipulação de arquivos
- Modularização em funções

## Como compilar e executar
gcc uai.c -o banco
./banco
