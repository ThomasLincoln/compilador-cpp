#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "ast_printer.h"

// Esta função converte um TokenType (int) para uma string legível.
const char* tokenTypeToString(TokenType type) {
    switch (type) {
        // Tokens de caracter único
        case TOKEN_LPAREN: return "TOKEN_LPAREN";
        case TOKEN_RPAREN: return "TOKEN_RPAREN";
        case TOKEN_LBRACE: return "TOKEN_LBRACE";
        case TOKEN_RBRACE: return "TOKEN_RBRACE";
        case TOKEN_COMMA: return "TOKEN_COMMA";
        case TOKEN_SEMICOLON: return "TOKEN_SEMICOLON";
        case TOKEN_PLUS: return "TOKEN_PLUS";
        case TOKEN_MINUS: return "TOKEN_MINUS";
        case TOKEN_MULT: return "TOKEN_MULT";
        case TOKEN_SLASH: return "TOKEN_SLASH";

        // Tokens de um ou dois caracteres
        case TOKEN_EXCL: return "TOKEN_EXCL";
        case TOKEN_EXCL_EQUAL: return "TOKEN_EXCL_EQUAL";
        case TOKEN_EQUAL: return "TOKEN_EQUAL";
        case TOKEN_EQUAL_EQUAL: return "TOKEN_EQUAL_EQUAL";
        case TOKEN_LESS: return "TOKEN_LESS";
        case TOKEN_LESS_EQUAL: return "TOKEN_LESS_EQUAL";
        case TOKEN_GREATER: return "TOKEN_GREATER";
        case TOKEN_GREATER_EQUAL: return "TOKEN_GREATER_EQUAL";

        // Literais
        case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";
        case TOKEN_NUMBER: return "TOKEN_NUMBER";

        // Palavras-chave
        case TOKEN_IF: return "TOKEN_IF";
        case TOKEN_ELSE: return "TOKEN_ELSE";
        case TOKEN_WHILE: return "TOKEN_WHILE";
        case TOKEN_INT: return "TOKEN_INT";
        case TOKEN_RETURN: return "TOKEN_RETURN";

        // Controle
        case TOKEN_ERROR: return "TOKEN_ERROR";
        case TOKEN_EOF: return "TOKEN_EOF";

        default: return "TOKEN_DESCONHECIDO";
    }
}

void runTest(const char *testName, const char *source)
{
  printf("--- Rodando Teste Unitario: %s ---\n", testName);
  initLexer(source);

  Token token;
  for (;;)
  {
    token = scanToken();
    printf("  Linha %d | Tipo: %d | Lexema: '%.*s'\n",
           token.line, token.type, token.length, token.start);

    if (token.type == TOKEN_EOF)
    {
      break;
    }
  }
  printf("\n");
}

static char *readFile(const char *path)
{
  FILE *file = fopen(path, "rb");
  if (file == NULL)
  {
    fprintf(stderr, "ERRO: Nao foi possivel abrir o arquivo \"%s\".\n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char *buffer = (char *)malloc(fileSize + 1);
  if (buffer == NULL)
  {
    fprintf(stderr, "ERRO: Nao ha memoria suficiente para ler \"%s\".\n", path);
    exit(74);
  }

  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);

  if (bytesRead < fileSize)
  {
    fprintf(stderr,
            "AVISO: Nao foi possivel ler o arquivo \"%s\" completamente.\n", path);
  }

  buffer[bytesRead] = '\0';
  fclose(file);
  return buffer;
}

int main(int argc, const char *argv[])
{
  if (argc < 2)
  {
    printf("INFO: Nenhum arquivo fornecido para analise. Encerrando.\n");
    printf("Modo de uso: %s [caminho_para_o_arquivo]\n", argv[0]);
    return 0;
  }

  const char *nomeDoArquivo = argv[1];

  printf("--- Iniciando analise do arquivo: %s ---\n", nomeDoArquivo);

  char *codigoDoArquivo = readFile(nomeDoArquivo);
  parse(codigoDoArquivo);  

  free(codigoDoArquivo);
  return 0;
}