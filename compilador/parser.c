#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "ast_printer.h"

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
static AstNode *parse_expressao();
static AstNode *parse_primario();
static AstNode *parse_fator();
static AstNode *parse_unario();
static AstNode *parse_termo();

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

void parse(const char *source)
{
  initLexer(source);
  advance();
  AstNode *programa_generico = criar_no_programa();
  ProgramaNode *programa = (ProgramaNode *)programa_generico;
  AstNode *cabeca = NULL;
  AstNode *cauda = NULL;
  while (!check(TOKEN_EOF))
  {
    AstNode *declaracao_atual = parse_declaracao();

    if(cabeca == NULL && cauda == NULL){
      cabeca = cauda = declaracao_atual;
    } else {
      cauda->irmao = declaracao_atual;
      cauda = declaracao_atual;
    }
    if (parser.hadError)
      break;
  }
  programa->filho = cabeca;
  imprimir_ast(programa_generico);
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
  return peek().type == type;
}

bool match(TokenType type)
{
  if (!check(type))
    return false;
  advance();
  return true;
}
static void error(Token *token, const char *mensagem)
{
  if (parser.panicMode)
    return;
  parser.panicMode = true;
  fprintf(stderr, "[linha %d] Erro", token->line);

  if (token->type == TOKEN_EOF)
  {
    fprintf(stderr, " no final do arquivo");
  }
  else if (token->type == TOKEN_ERROR)
  {
  }
  else
  {
    fprintf(stderr, ": %.*s", token->length, token->start);
  }
  fprintf(stderr, ": %s\n", mensagem);
  parser.hadError = true;
  exit(EXIT_FAILURE);
}

void consume(TokenType type, const char *mensagem)
{
  if (check(type))
  {
    advance();
    return;
  }

  error(&parser.current, mensagem);
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

  if (match(TOKEN_EQUAL))
  {
    inicializador = parse_expressao();
  }
  consume(TOKEN_SEMICOLON, "Esperava o ';' apos a declaracao da variavel");
  return criar_no_declaracao_variavel(nome_da_variavel, inicializador);
}

static AstNode *parse_expressao()
{
  return parse_termo();
}

static AstNode *parse_termo(){
  AstNode *expr = parse_fator();
  while(match(TOKEN_PLUS) || match(TOKEN_MINUS)){
    Token operador = previous();
    AstNode *direita = parse_fator();
    expr = criar_no_expressao_binaria(operador, expr, direita);
  }
  return expr;
}

static AstNode *parse_fator(){
  AstNode *expr = parse_unario();
  while(match(TOKEN_SLASH) || match(TOKEN_MULT)){
    Token operador = previous();
    AstNode *direita = parse_unario();
    expr = criar_no_expressao_binaria(operador, expr, direita);
  }
  return expr;
}

static AstNode *parse_unario(){
  if(match(TOKEN_MINUS)){
    Token operador = previous();
    AstNode *direita = parse_unario();
    return criar_no_expressao_unaria(operador, direita);
  }
  return parse_primario();
}

static AstNode *parse_primario(){
  if(match(TOKEN_NUMBER)){
    return criar_no_literal(previous());
  }
  if(match(TOKEN_IDENTIFIER)){
    return criar_no_expressao_variavel(previous());
  }
  if(match(TOKEN_LPAREN)){
    AstNode *expr = parse_expressao();
    consume(TOKEN_RPAREN, "Tentando consumir o segundo parenteses");
    return expr;
  }

  return NULL;
}