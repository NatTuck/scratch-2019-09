
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

calc_ast*
make_ast_value(int vv)
{
    calc_ast* ast = calloc(1, sizeof(calc_ast));
    ast->op = '=';
    ast->value = vv;
    ast->arg0 = 0; // don't need zeros with calloc
    ast->arg1 = 0;
    return ast;
}

calc_ast*
make_ast_op(char op, calc_ast* a0, calc_ast* a1)
{
    calc_ast* ast = malloc(sizeof(calc_ast));
    ast->op = op;
    ast->arg0 = a0;
    ast->arg1 = a1;
    return ast;
}

void
free_ast(calc_ast* ast)
{
    if (ast) {
        if (ast->arg0) {
            free_ast(ast->arg0);
        }

        if (ast->arg1) {
            free_ast(ast->arg1);
        }

        free(ast);
    }
}

char*
ast_string(calc_ast* ast)
{
    if (ast->op == '=') {
        char* tmp = malloc(16);
        sprintf(tmp, "%d", ast->value);
        return tmp;
    }

    char* aa = ast_string(ast->arg0);
    char* bb = ast_string(ast->arg1);
    char* cc = malloc(128);
    sprintf(cc, "(%s %c %s)", aa, ast->op, bb);
    free(aa);
    free(bb);
    return cc;
}

void
print_ast(calc_ast* ast)
{
    char* text = ast_string(ast);
    printf("%s\n", text);
    free(text);
}

int
ast_eval(calc_ast* ast)
{
    if (ast->op == '=') {
        return ast->value;
    }

    int aa = ast_eval(ast->arg0);
    int bb = ast_eval(ast->arg1);

    switch (ast->op) {
        case '+':
            return aa + bb;
        case '-':
            return aa - bb;
        case '*':
            return aa * bb;
        case '/':
            return aa / bb;
        default:
            abort();
    }
}
