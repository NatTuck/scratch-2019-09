
/*
typedef struct calc_ast {
    char op;
    // Op is either:
    //  one of: +, -, *, / for an operation
    //      or: '=' for value
    struct calc_ast* arg0;
    struct calc_ast* arg1;
    int value;
} calc_ast;
*/

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

calc_ast*
make_ast_value(int vv)
{
    calc_ast_val* ast = malloc(sizeof(calc_ast_val));
    ast->op    = '=';
    ast->value = vv;
    return (calc_ast*) ast;
}

calc_ast*
make_ast_op(char op, calc_ast* a0, calc_ast* a1)
{
    calc_ast_op* ast = malloc(sizeof(calc_ast_op));
    // TODO: Check valid input
    ast->op = op;
    ast->arg0 = a0;
    ast->arg1 = a1;
    return (calc_ast*) ast;
}

void
free_ast(calc_ast* ast)
{
    if (ast->op == '=') {
        free(ast);
    }
    else {
        calc_ast_op* op = (calc_ast_op*) ast;
        free_ast(op->arg0);
        free_ast(op->arg1);
        free(op);
    }
}

int
ast_eval(calc_ast* ast)
{
    if (ast->op == '=') {
        calc_ast_val* astv = (calc_ast_val*) ast;
        return astv->value;
    }

    calc_ast_op* op = (calc_ast_op*) ast;

    if (op->op == '+') {
        return ast_eval(op->arg0) + ast_eval(op->arg1);
    }

    if (op->op == '-') {
        return ast_eval(op->arg0) - ast_eval(op->arg1);
    }

    if (op->op == '*') {
        return ast_eval(op->arg0) * ast_eval(op->arg1);
    }

    if (op->op == '/') {
        return ast_eval(op->arg0) / ast_eval(op->arg1);
    }

    abort();
}

char*
ast_string(calc_ast* ast)
{
    if (ast->op == '=') {
        char* tmp = malloc(16);
        sprintf(tmp, "%d", ((calc_ast_val*)ast)->value);
        return tmp;
    }
    else {
        calc_ast_op* op = (calc_ast_op*) ast;
        char* aa = ast_string(op->arg0);
        char* bb = ast_string(op->arg1);
        char* cc = malloc(128);
        sprintf(cc, "(%s %c %s)", aa, ast->op, bb);
        free(aa);
        free(bb);
        return cc;
    }
}

void
print_ast(calc_ast* ast)
{
    char* text = ast_string(ast);
    printf("%s\n", text);
    free(text);
}
