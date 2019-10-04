
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

        // Tokenize
        list* toks = tokenize(line);
        print_list(toks);

        calc_ast* ast = parse(toks);
        print_ast(ast);

        int answer = ast_eval(ast);
        printf(" => %d\n", answer);

        free_list(toks);
    }

    return 0;
}
