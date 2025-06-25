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
    case NODE_ATRIBUICAO:
    {
        AtribuicaoNode *node = (AtribuicaoNode *)no;
        printf("└── Atribuicao (var: %.*s)\n", node->nome.length, node->nome.start);
        imprimir_no_com_indentacao(node->valor, indentacao + 1);
        break;
    }
    case NODE_EXPRESSAO_STATEMENT:
    {
        ExpressaoStatementNode *stmt = (ExpressaoStatementNode *)no;
        printf("└── Stmt.Expressao\n");
        imprimir_no_com_indentacao(stmt->expressao, indentacao + 1);
        break;
    }
        // ast_printer.c (case NODE_IF corrigido)

    case NODE_IF:
    {
        IfNode *stmt = (IfNode *)no;
        printf("└── If.Statement\n");
        // Use os novos nomes de campo para acessar os filhos
        imprimir_no_com_indentacao(stmt->condicao, indentacao + 1);
        imprimir_no_com_indentacao(stmt->ramo_then, indentacao + 1);
        imprimir_no_com_indentacao(stmt->ramo_else, indentacao + 1);
        break;
    }
    case NODE_EXPR_VARIAVEL:
    {
        VariavelExprNode *expr = (VariavelExprNode *)no;
        printf("└── Variavel (nome: %.*s)\n", expr->nome.length, expr->nome.start);
        break;
    }
    case NODE_EXPR_BINARIA:
        ExpressaoBinariaNode *expr = (ExpressaoBinariaNode *)no;
        // Imprime o nó pai (o operador) com seu "galho"
        printf("└── Expr.Binaria (op: %.*s)\n", expr->operador.length, expr->operador.start);

        // Chama a si mesma recursivamente para imprimir os filhos com mais indentação
        imprimir_no_com_indentacao(expr->esquerda, indentacao + 1);
        imprimir_no_com_indentacao(expr->direita, indentacao + 1);
        break;
    case NODE_EXPR_UNARIA: // Supondo que você crie esta etiqueta em ast.h
    {
        UnaryExprNode *expr = (UnaryExprNode *)no;
        printf("└── Expr.Unaria (op: %.*s)\n", expr->operador.length, expr->operador.start);

        imprimir_no_com_indentacao(expr->direita, indentacao + 1);
        break;
    }
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