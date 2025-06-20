// Código para definir os nós da AST
#ifndef AST_H
#define AST_H

#include "lexer.h"
typedef struct AstNode AstNode;

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

// -- Nós especificos --
typedef struct
{
  AstNode base;
  int valor;
} LiteralNode;

typedef struct
{
  AstNode base;
  AstNode *esquerda;
  AstNode *direita;
  Token operador;
} ExpressaoBinariaNode;

typedef struct
{
  AstNode base;
  Token nome;
  AstNode *inicializador;
} DeclaracaoVariavelNode;

AstNode *criar_no_declaracao_variavel(Token nome, AstNode *inicializador);
AstNode *criar_no_literal(Token numero);
#endif