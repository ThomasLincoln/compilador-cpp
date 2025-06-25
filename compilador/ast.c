// Código para definir os construtores de nós definidos em ast.h
#include <stdlib.h>
#include "ast.h"

// Construir o nó da declaração de variável
AstNode *criar_no_declaracao_variavel(Token nome, AstNode *inicializador)
{
  DeclaracaoVariavelNode *node =
      (DeclaracaoVariavelNode *)malloc(sizeof(DeclaracaoVariavelNode));
  node->base.type = NODE_DECL_VARIAVEL;
  node->base.irmao = NULL;
  node->nome = nome;
  node->inicializador = inicializador;
  return (AstNode *)node;
}

// Construir um nó de literal
AstNode *criar_no_literal(Token numero)
{
  LiteralNode *node = (LiteralNode *)malloc(sizeof(LiteralNode));
  node->base.type = NODE_LITERAL;
  node->base.irmao = NULL;
  node->valor = numero.value.integer;
  return (AstNode *)node;
}

AstNode *criar_no_programa()
{
  ProgramaNode *node = (ProgramaNode *)malloc(sizeof(ProgramaNode));
  node->base.type = NODE_PROG;
  node->base.irmao = NULL;
  node->filho = NULL;
  return (AstNode *)node;
}

AstNode *criar_no_expressao_binaria(Token operador, AstNode *esquerda, AstNode *direita)
{
  ExpressaoBinariaNode *node = (ExpressaoBinariaNode *)
      malloc(sizeof(ExpressaoBinariaNode));
  node->base.type = NODE_EXPR_BINARIA;
  node->base.irmao = NULL;
  node->esquerda = esquerda;
  node->direita = direita;
  node->operador = operador;
  return (AstNode *)node;
}

AstNode *criar_no_expressao_unaria(Token operador, AstNode *direita)
{
  UnaryExprNode *node = (UnaryExprNode *)malloc(sizeof(UnaryExprNode));
  node->base.type = NODE_EXPR_UNARIA;
  node->base.irmao = NULL;
  node->operador = operador;
  node->direita = direita;
  return (AstNode *)node;
}

AstNode *criar_no_expressao_variavel(Token nome)
{
  VariavelExprNode *node = (VariavelExprNode *)malloc(sizeof(VariavelExprNode));
  node->base.type = NODE_EXPR_VARIAVEL;
  node->base.irmao = NULL;
  node->nome = nome;
  return (AstNode *)node;
}

AstNode *criar_no_if(AstNode *condicao, AstNode *filho, AstNode *filho_else)
{
  IfNode *node = (IfNode *)malloc(sizeof(IfNode));
  node->base.type = NODE_IF;
  node->base.irmao = NULL;

  node->condicao = condicao;
  node->ramo_then = filho;
  node->ramo_else = filho_else;

  return (AstNode *)node;
}

AstNode *criar_no_expressao_statement(AstNode *expressao)
{
  ExpressaoStatementNode *node = (ExpressaoStatementNode *)malloc(sizeof(ExpressaoStatementNode));
  node->base.type = NODE_EXPRESSAO_STATEMENT;
  node->base.irmao = NULL;
  node->expressao = expressao;
  return (AstNode *)node;
}

AstNode *criar_no_atribuicao(Token nome, AstNode *valor)
{
  AtribuicaoNode *node = (AtribuicaoNode *)malloc(sizeof(AtribuicaoNode));
  node->base.type = NODE_ATRIBUICAO;
  node->base.irmao = NULL;
  node->nome = nome;
  node->valor = valor;
  return (AstNode *)node;
}