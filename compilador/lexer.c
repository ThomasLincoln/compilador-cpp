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
typedef struct
{
  const char *start;   // ponteiro para o início da palavra atual
  const char *current; // para onde o código está apontando agora
  int line;
} Lexer;

Lexer lexer;

// Métod para iniciar o lexer
void initLexer(const char *source)
{
  lexer.start = source;
  lexer.current = source;
  lexer.line = 1;
}

static void pularEspacoEmBranco();
static char getCurrentChar();
static char nextChar();
static bool detectEnd();
static Token createToken(TokenType type);
static Token identificador();
static TokenType identificadorDeTipo();
static TokenType verificaPalavraChave(int start, int lenght, const char *resto, TokenType type);
static Token errorToken(const char *message);
static Token numero();
static int match(char expected);
Token scanToken();

Token scanToken()
{
  // Lidar com espaços em branco
  pularEspacoEmBranco();

  // Começamos a analise do próximo token, atualizando o começo
  lexer.start = lexer.current;

  // Se já estiver no fim, retornamos um token final
  if (detectEnd())
    return createToken(TOKEN_EOF);

  // Pegamos um caracter e avançamos o current
  char c = nextChar();

  // Verificamos se é o começo de uma palavra, seja identificador ou
  // palavra-chave
  if (isalpha(c) || c == '_')
  {
    return identificador();
  }

  if (isalnum(c))
  {
    return numero();
  }

  switch (c)
  {
  case '(':
    return createToken(TOKEN_LPAREN);
  case ')':
    return createToken(TOKEN_RPAREN);
  case '{':
    return createToken(TOKEN_LBRACE);
  case '}':
    return createToken(TOKEN_RBRACE);
  case ';':
    return createToken(TOKEN_SEMICOLON);
  case ',':
    return createToken(TOKEN_RPAREN);
  case '+':
    return createToken(TOKEN_PLUS);
  case '-':
    return createToken(TOKEN_MINUS);
  case '*':
    return createToken(TOKEN_MULT);
  case '!':
    return createToken(match('=') ? TOKEN_EXCL_EQUAL : TOKEN_EQUAL);
  case '=':
    return createToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
  case '<':
    return createToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
  case '>':
    return createToken(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
  case '/':
    return createToken(TOKEN_SLASH);
  }
  static char error_message[100];
  sprintf(error_message, "Caractere inesperado: '%c' (ASCII: %d)", c, c);

  return errorToken(error_message);
}

static int match(char expected)
{
  if (detectEnd())
    return 0;
  if (*lexer.current != expected)
    return 0;
  lexer.current++;
  return 1;
}
static Token numero()
{
  while (isalnum(getCurrentChar()))
  {
    nextChar();
  }
  Token token = createToken(TOKEN_NUMBER);
  token.value.integer = (int)strtol(lexer.start, NULL, 10);
  return token;
}
static void pularEspacoEmBranco()
{
  for (;;)
  {
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
      if (lexer.current[1] == '/')
      {
        while (getCurrentChar() != '\n' && !detectEnd())
        {
          nextChar();
        }
      }
      else
      {
        return;
      }
      break;
    default:
      return;
    }
  }
}
static char getCurrentChar()
{
  return *lexer.current;
}

static char nextChar()
{
  lexer.current++;
  return lexer.current[-1];
}
static bool detectEnd()
{
  return *lexer.current == '\0';
}

static Token createToken(TokenType type)
{
  Token token;
  token.type = type;
  token.start = lexer.start;
  token.length = (int)(lexer.current - lexer.start);
  token.line = lexer.line;
  return token;
}

static Token identificador()
{
  while (isalnum(getCurrentChar()) || getCurrentChar() == '_')
    nextChar();
  return createToken(identificadorDeTipo());
}

static TokenType identificadorDeTipo()
{
  switch (lexer.start[0])
  {
  case 'e':
    return verificaPalavraChave(1, 3, "lse", TOKEN_ELSE);
  case 'i':
    if (lexer.current - lexer.start > 1)
    {
      switch (lexer.start[1])
      {
      case 'f':
        return verificaPalavraChave(2, 0, "", TOKEN_IF);
      case 'n':
        return verificaPalavraChave(2, 1, "t", TOKEN_INT);
      }
    }
    break;
  case 'w':
    return verificaPalavraChave(1, 4, "hile", TOKEN_WHILE);
  case 'r':
    return verificaPalavraChave(1, 5, "eturn", TOKEN_RETURN);
  }
  return TOKEN_IDENTIFIER;
}

static TokenType verificaPalavraChave(int start, int lenght, const char *resto, TokenType type)
{
  if (lexer.current - lexer.start == start + lenght &&
      memcmp(lexer.start + start, resto, lenght) == 0)
  {
    return type;
  }
  return TOKEN_IDENTIFIER;
}

static Token errorToken(const char *message)
{
  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = (int)strlen(message);
  token.line = lexer.line;
  return token;
}