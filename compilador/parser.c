#include <stdio.h>
#include <stdbool.h>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

// ===================================================================
// 1. DECLARAÇÕES ANTECIPADAS (FORWARD DECLARATIONS)
// ===================================================================
// Esta seção informa ao compilador sobre TODAS as funções estáticas
// antes que qualquer uma delas seja usada. Isso resolve os erros de
// "implicit declaration" e "conflicting types".

// Funções da infraestrutura do parser
static void advance();
static bool check(TokenType type);
static void consume(TokenType type, const char *mensagem);
static bool match(TokenType type);
static Token peek();
static Token previous();

// Funções de parsing (uma para cada regra da gramática)
static AstNode *parse_declaracao();
static AstNode *parse_declaracao_variavel();
static AstNode *parse_expressao(); // Corrigido de "parse_expressaO"

// ===================================================================
// 2. ESTRUTURA E ESTADO DO PARSER
// ===================================================================

typedef struct
{
  Token current;
  Token previous;
  bool hadError;
  bool panicMode;
} Parser;
Parser parser;

AstNode* parse(const char *source)
{
  initLexer(source);
  advance();
  if (!check(TOKEN_EOF))
  {
    return parse_declaracao();
  }
  return NULL;
}

// Função para avançar para o próximo Token
void advance()
{
  parser.previous = parser.current;
  for (;;)
  {
    parser.current = scanToken();
    if (parser.current.type != TOKEN_ERROR)
      break;
      // * no futuro teremos um tratamento de erro mais robusto
  }
}

void parser_init()
{
  parser.hadError = false;
  parser.panicMode = false;
  advance();
}

Token peek()
{
  return parser.current;
}

Token previous()
{
  return parser.previous;
}

bool check(TokenType type)
{
  if (peek().type == TOKEN_EOF)
    return false;
  return peek().type == type;
}

bool match(TokenType type)
{
  if (!check(type))
    return false;
  advance();
  return true;
}

void consume(TokenType type, const char *mensagem)
{
  if (check(type))
  {
    advance();
    return;
  }
}

static AstNode *parse_declaracao()
{
  return parse_declaracao_variavel();
}

static AstNode *parse_declaracao_variavel()
{
  // precisamos do int
  consume(TOKEN_INT, "Esperava 'int' para iniciar a declaracao da variavel");

  // precisamos do nome da variavel
  consume(TOKEN_IDENTIFIER, "Esperava o nome da variavel");
  Token nome_da_variavel = previous();
  AstNode *inicializador = NULL;

  // Verificar a parte opcional
  if (match(TOKEN_EQUAL))
  {
    inicializador = parse_expressao();
  }
  consume(TOKEN_SEMICOLON, "Esperava o ';' apos a declaracao da variavel");
  return criar_no_declaracao_variavel(nome_da_variavel, inicializador);
}

static AstNode *parse_expressao()
{
  consume(TOKEN_NUMBER, "Esperava um numero como expressao");
  return criar_no_literal(previous());
}