#include <stdio.h>

#include "ast.h"
#include "tokens.h"
#include "parse.h"

int
main(int _ac, char* _av[])
{
    char line[100];

    while (1) {
        char* rv = fgets(line, 100, stdin);
        if (!rv) {
            break;
        }

        list* toks = tokenize(line);
        for (list* it = toks; it; it = it->tail) {
            printf("- '%s'\n", it->head);
        }
        calc_ast* ast = parse(toks);
        print_ast(ast);
        int vv = ast_eval(ast);
        printf(" => %d\n", vv);
        free_list(toks);
    }

    return 0;
}
