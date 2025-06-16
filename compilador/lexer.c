#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "lexer.h"

/*
Dicionário

Lexer = Scanner que vai transformar o código fonte em um amontoado de tokens
*/
typedef struct{
  const char* start; // ponteiro para o início da palavra atual
  const char* current; // para onde o código está apontando agora
  int line;
} Lexer;

Lexer lexer;

// Métod para iniciar o lexer
void initLexer(const char* source){
  lexer.start = source;
  lexer.current = source;
  lexer.line = 1;
}
Token scanToken();


static void pularEspacoEmBranco(){
  for(;;){
    char c = getCurrentChar();
    switch (c)
    {
    case ' ':
    case '\r':
    case '\t':
      nextChar();
      break;
    case '\n':
      lexer.line++;
      nextChar();
      break;
    case '/':
      if(lexer.current[1] == '/'){
        while(getCurrentChar() != '\n' && !detectEnd()){
          nextChar();
        }
      } else{
        return;
      }
    default:
      return;
    }
  }
}
static char getCurrentChar(){
  return *lexer.current;
}

static char nextChar(){
  lexer.current++;
  return lexer.current[-1];
}
static bool detectEnd(){
  return *lexer.current == '\0';
}

static Token createToken(TokenType type){
  Token token;
  token.type = type;
  token.start = lexer.start;
  token.length = (int)(lexer.current - lexer.start);
  token.line = lexer.line;
  return token;
}

static Token identificador(){
  while(isalnum(getCurrentChar()) || getCurrentChar() == '_')
    nextChar();
  return createToken(identificadorDeTipo());
}

static TokenType identificadorDeTipo(){
  switch (lexer.start[0])
  {
  case 'e': return verificaPalavraChave(1, 3, "lse", TOKEN_ELSE);
  case 'i':
    if(lexer.current - lexer.start > 1){
      switch (lexer.start[1])
      {
      case 'f': return verificaPalavraChave(2, 0, "", TOKEN_IF);
      case 'n': return verificaPalavraChave(2, 1, "t", TOKEN_INT);
      }
    }
    break;
  case 'w': return verificaPalavraChave(1, 4, "hile", TOKEN_WHILE);
  case 'r': return verificaPalavraChave(1, 5, "eturn", TOKEN_RETURN);  
  }
  return TOKEN_IDENTIFIER;
}

static TokenType verificaPalavraChave(int start, int lenght, const char* resto, TokenType type){
  if(lexer.current - lexer.start == start + lenght &&
      memcmp(lexer.start + start, resto, lenght) == 0){
        return type;
  }
  return TOKEN_IDENTIFIER;
}

static Token errorToken(const char* message){
  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = (int)strlen(message);
  token.line = lexer.line;
  return token;
}

Token scanToken(){
  // Lidar com espaços em branco
  pularEspacoEmBranco();

  // Começamos a analise do próximo token, atualizando o começo
  lexer.start = lexer.current;
  
  // Se já estiver no fim, retornamos um token final
  if(detectEnd())
    return createToken(TOKEN_EOF);

  // Pegamos um caracter e avançamos o current
  char c = nextChar();

  // Verificamos se é o começo de uma palavra, seja identificador ou 
  // palavra-chave
  if(isalpha(c) || c == '_'){
    return identificador();
  }

  return errorToken("Caractere inesperado.");
}

