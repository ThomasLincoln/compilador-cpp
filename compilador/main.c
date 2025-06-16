#include <stdio.h>
#include <string.h>
#include "lexer.h"

void runTest(const char* testName, const char* source){
  printf("--- Rodando Teste: %s ---\n", testName);
  initLexer(source);

  Token token;
  for(;;) {
    token = scanToken();
    printf(" Linha %d | Tipo: %d | Lexema: '%.*s'\n", 
      token.line, token.type, token.length, token.start);
    if (token.type == TOKEN_EOF){
      break;
    }
  }
  printf("\n");
}

int main() {
  // Teste 1: Uma única palavra-chave
  runTest("Palavra-chave 'if'", "if");
  runTest("Identificador 'soma'", "soma");
  runTest("Espacos em branco", "   while   return   ");

  runTest("Sequencia mista", "if variavel_x else");
  runTest("Sequencia mista com variavel comecando com numero", "if 2variavel2_x else");
  runTest("Sequencia mista com numero no meio da variavel", "if variavel2_x else");
  runTest("Sequencia mista com numero no fim da variavel", "if variavel_2 else");
}