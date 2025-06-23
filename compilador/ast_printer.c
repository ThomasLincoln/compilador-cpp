#include <stdio.h>
#include "ast.h"

static void imprimir_no_com_indentacao(AstNode *no, int indentacao);

void imprimir_ast(AstNode *no)
{
    imprimir_no_com_indentacao(no, 0);
}

static void imprimir_no_com_indentacao(AstNode *no, int indentacao)
{
    for (int i = 0; i < indentacao; i++)
    {
        printf("  ");
    }

    if (no == NULL)
    {
        printf("└── (NULL)\n");
        return;
    }

    switch (no->type)
    {
    case NODE_PROG:
    {
        ProgramaNode *prog = (ProgramaNode *)no;
        printf("Programa\n");

        AstNode *declaracao_atual = prog->filho;
        while (declaracao_atual != NULL)
        {
            imprimir_no_com_indentacao(declaracao_atual, indentacao + 1);
            declaracao_atual = declaracao_atual->irmao;
        }
        break;
    }
    case NODE_DECL_VARIAVEL:
    {
        DeclaracaoVariavelNode *decl = (DeclaracaoVariavelNode *)no;
        printf("└── DeclaracaoVariavel (nome: %.*s)\n", decl->nome.length, decl->nome.start);

        imprimir_no_com_indentacao(decl->inicializador, indentacao + 1);
        break;
    }
    case NODE_LITERAL:
    {
        LiteralNode *literal = (LiteralNode *)no;
        printf("└── Literal (valor: %d)\n", literal->valor);
        break;
    }
    default:
        printf("└── Nó Desconhecido (tipo: %d)\n", no->type);
        break;
    }
}