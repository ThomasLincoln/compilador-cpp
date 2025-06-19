#include <stdio.h>
#include <stdbool.h>
#include "lexer.h"
#include "parser.h"

// Estrutura para o parser saber onde ele está e o próximo token, além de alguns
// campos para lidarmos com erro
typedef struct
{
  Token current;
  Token previous;
  bool hadError;
  bool panicMode;
} Parser;

Parser parser;

// Função para avançar para o próximo Token
void advance() {
  parser.previous = parser.current;
  for(;;){
    parser.current = scanToken();
    if(parser.current.type != TOKEN_ERROR) break;
  }
}

void parser_init(){
  parser.hadError = false;
  parser.panicMode = false;
  advance();
}

Token peek(){
  return parser.current;
}

Token previous(){
  return parser.previous;
}

bool check(TokenType type){
  if(peek().type == TOKEN_EOF) return false;
  return peek().type == type;
}

bool match(TokenType type){
  if(!check(type)) return false;
  advance();
  return true;
}

void consume (TokenType type, const char* mensagem){
  if(check(type)){
    advance();
    return;
  }
}

static void parse_declaracao(){
  parse_declaracao_variavel();
}

static void parse_declaracao_variavel(){
  // precisamos do int
  consume(TOKEN_INT, "Esperava 'int' para iniciar a declaracao da variavel");

  // precisamos do nome da variavel
  consume(TOKEN_IDENTIFIER, "Esperava o nome da variavel");

  // Verificar a parte opcional
  if(match(TOKEN_EQUAL)){
    parse_expressao();
  }
  consume(TOKEN_SEMICOLON, "Esperava o ';' apos a declaracao da variavel");
}

static void parse_expressa(){
  consume(TOKEN_NUMBER, "Esperava um numero como expressao");
}