// Código para definir os nós da AST
#ifndef AST_H
#define AST_H

#include "lexer.h"
struct Expr;

// Etiquetas para os nós
typedef enum
{
  NODE_LITERAL,
  NODE_EXPR_BINARIA,
  NODE_DECL_VARIAVEL
} NodeType;

// Base para os nós
typedef struct AstNode
{
  NodeType type;
} AstNode;

// Nós especificos
typedef struct
{
  AstNode base;
  int valor;
} LiteralNode;

// Expressão binária
typedef struct
{
  AstNode base;
  struct Expr *esquerda;
  struct Expr *direita;
  Token operador;
} ExpressaoBinariaNode;

// Declaração de variável
typedef struct
{
  AstNode base;
  Token nome;
  struct Expr* inicializador;
}DeclaracaoVariavelNode;

#endif