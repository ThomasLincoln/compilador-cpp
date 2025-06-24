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
  NODE_DECL_VARIAVEL,
  NODE_PROG,
} NodeType;

// Base para os nós
typedef struct AstNode
{
  NodeType type;
  AstNode *irmao;
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

typedef struct
{
  AstNode base;
  AstNode *filho;
} ProgramaNode;

AstNode *criar_no_declaracao_variavel(Token nome, AstNode *inicializador);
AstNode *criar_no_literal(Token numero);
AstNode *criar_no_programa();
AstNode *criar_no_expressao_binaria(Token operador, AstNode *esquerda, AstNode *direita);
#endif