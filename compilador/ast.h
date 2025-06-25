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
  NODE_EXPR_UNARIA,
  NODE_EXPR_VARIAVEL,
  NODE_IF,
  NODE_EXPRESSAO_STATEMENT,
  NODE_ATRIBUICAO,
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
  Token nome;
  AstNode *valor;
} AtribuicaoNode;

typedef struct
{
  AstNode base;
  AstNode *expressao;
} ExpressaoStatementNode;

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

typedef struct
{
  AstNode base;
  Token operador;
  AstNode *direita;
} UnaryExprNode;

typedef struct
{
  AstNode base;
  Token nome;
} VariavelExprNode;

typedef struct
{
  AstNode base;
  AstNode *condicao;
  AstNode *ramo_then;
  AstNode *ramo_else;
} IfNode;

AstNode *criar_no_declaracao_variavel(Token nome, AstNode *inicializador);
AstNode *criar_no_literal(Token numero);
AstNode *criar_no_programa();
AstNode *criar_no_expressao_binaria(Token operador, AstNode *esquerda, AstNode *direita);
AstNode *criar_no_expressao_unaria(Token operador, AstNode *direita);
AstNode *criar_no_expressao_variavel(Token nome);
AstNode *criar_no_if(AstNode *condicao, AstNode *filho, AstNode *filho_else);
AstNode *criar_no_expressao_statement(AstNode *expressao);
AstNode *criar_no_atribuicao(Token nome, AstNode* valor);
#endif