
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "ast.h"
#include "parse.h"
#include "list.h"

int
streq(const char* aa, const char* bb)
{
    return !strcmp(aa, bb);
}

int
find_first_index_helper(list* toks, const char* tt, int ii)
{
    if (toks == 0) {
        return -1;
    }
    else {
        if (streq(toks->head, tt)) {
            return ii;
        }
        else {
            return find_first_index_helper(toks->tail, tt, ii + 1);
        }
    }
}

int
find_first_index(list* toks, const char* tt)
{
    // return first (0-based) index containing equal
    // string, or -1 on faiure to find
    return find_first_index_helper(toks, tt, 0);
}

int
contains(list* toks, const char* tt)
{
    return find_first_index(toks, tt) != -1;
}

list*
slice(list* xs, int i0, int i1)
{
    // return a copy of the sublist starting at index i0
    // and ending at index (i1-1)
    if (i0 > 0) {
        return slice(xs->tail, i0 - 1, i1 - 1);
    }

    if (i1 > 0) {
        list* ys = slice(xs->tail, i0, i1 - 1);
        return cons(xs->head, ys);
    }

    return 0;
}

calc_ast*
parse(list* toks)
{
    if (length(toks) == 1) {
        // TODO error handling
        int vv = atoi(toks->head);
        return make_ast_value(vv);
    }

    // find the operator
    // split the text around operator
    // build a op node with recursive calls to parse

    const char* ops[] = {"+", "-", "*", "/"};

    for (int ii = 0; ii < 4; ++ii) {
        const char* op = ops[ii];

        if (contains(toks, op)) {
            int jj = find_first_index(toks, op);
            list* xs = slice(toks, 0, jj);
            list* ys = slice(toks, jj + 1, length(toks));
            calc_ast* ast = make_ast_op(op[0], parse(xs), parse(ys));
            free_list(xs);
            free_list(ys);
            return ast;
        }
    }

    fprintf(stderr, "Invalid token stream");
    abort();
}
