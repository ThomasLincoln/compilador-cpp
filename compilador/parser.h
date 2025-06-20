#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Esta será a única função pública do seu parser por enquanto.
// O main.c vai chamá-la para iniciar a análise sintática.
// Ela recebe o código-fonte como entrada.
// No futuro, ela retornará a raiz da sua AST (ex: AstNode* parse(...))
void parse(const char* source);
#endif