# Cenário da linguagem c-- mínima

- Palavras-chave: if, else, while, int, return
- Identificadores: nomes de variáveis e funções (main, soma, x)
- Números: apenas números inteiros
- Operadores: +, -, *, /, =, ==, !=, <, >
- Separadadores: `(`, `)`, `{`, `}`, `,`, `;`
- Fim do arquivo: um token especial para indicar que o código fonte terminou (ainda não decidido)
- Comentários: Apenas uma linha única, contendo `//`.

# Passos
- [x] Definir os tokens
- [x] Construir o lexer.h com a definição dos tokens e um struct para armazenar as informações de um token
- [x] Constuir o Lexer.c, para se como o nosso scanner, para ler o código e dividir ele em uma sequência de "partes"(tokens) que fazem sentido para a linguagem de programação.
  - [x] Falta verificar os identifadores e descobrir se é uma palavra chave ou um identificador
  - [x] Verificar se é um digito
  - [x] Verificar se são os outros símbolos
