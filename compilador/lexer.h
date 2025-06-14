#ifndef C_MINUS_MINUS_LEXER_H
#define C_MINUS_MINUS_LEXER_H

// Tipos de token que o nosso lexer pode reconhecer
typedef enum {
  // Tokens de caracter único
  // ( )
  TOKEN_LPAREN, TOKEN_RPAREN,
  // { }
  TOKEN_LBRACE, TOKEN_RBRACE,
  // , ; 
  TOKEN_COMMA, TOKEN_SEMICOLON,
  // + -
  TOKEN_PLUS, TOKEN_MINUS,
  // * /
  TOKEN_MULT, TOKEN_SLASH,

  // Tokens de um ou dois caracteres
  // ! !=
  TOKEN_EXCL, TOKEN_EXCL_EQUAL,
  //  = == 
  TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
  // < <=
  TOKEN_LESS, TOKEN_LESS_EQUAL,
  // >, >=
  TOKEN_GREATER, TOKEN_GREATER_EQUAL,

  // Literais
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER,

  // palavras-chave
  TOKEN_IF, TOKEN_ELSE,
  TOKEN_WHILE,
  TOKEN_INT,
  TOKEN_RETURN,
  
  // Controle
  TOKEN_ERROR, TOKEN_EOF
} TokenType;

typedef struct{
  TokenType type;
  const char* start;
  int length;
  int line;
} Token;

void initLexer(const char * source);
Token scanToken();
#endif