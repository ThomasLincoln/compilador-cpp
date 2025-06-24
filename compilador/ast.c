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

AstNode *criar_no_expressao_binaria(Token operador, AstNode *esquerda, AstNode *direita){
  ExpressaoBinariaNode *node = (ExpressaoBinariaNode *)
    malloc(sizeof(ExpressaoBinariaNode));
  node->base.type = NODE_EXPR_BINARIA;
  node->base.irmao = NULL;
  node->esquerda = esquerda;
  node->direita = direita;
  node->operador = operador;
  return (AstNode *)node;
}