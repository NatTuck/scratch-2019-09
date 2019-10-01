
#include <stdio.h>
#include <stdlib.h>

// A Linked list is one of:
// - A null pointer
// - A pointer to a int_list
typedef struct int_list {
    int head;
    struct int_list* tail;
    int refs; // todo: reference counting
} int_list;

int_list*
cons(int xx, int_list* xs)
{
    int_list* ys = malloc(sizeof(int_list));
    ys->head = xx;
    ys->tail = xs;
    return ys;
}

void
free_list(int_list* xs)
{
    while (xs) {
        int_list* next = xs->tail;
        free(xs);
        xs = next;
    }
}

int_list*
reverse(int_list* xs)
{
    int_list* ys = 0;
    for (int_list* curr = xs; curr; curr = curr->tail) {
        ys = cons(curr->head, ys);
    }
    return ys;
}

int_list*
read_ints(int nn)
{
    int_list* ys = 0;
    for (int ii = 0; ii < nn; ++ii) {
        int xx;
        scanf("%d", &xx);
        ys = cons(xx, ys);
    }
    int_list* zs = reverse(ys);
    free_list(ys);
    return zs;
}

int_list*
copy_list(int_list* xs)
{
    if (xs) {
        return cons(xs->head, copy_list(xs->tail));
    }
    else {
        return 0;
    }
}

int_list*
insert(int xx, int_list* ys)
{
    if (ys) {
        if (xx < ys->head) {
            return cons(xx, copy_list(ys));
        }
        else {
            return cons(ys->head, insert(xx, ys->tail));
        }
    }
    else {
        return cons(xx, 0);
    }
}

int_list*
isort(int_list* xs)
{
    // create new empty list ys
    // insert items from xs into ys, maintaining
    // ys as a sorted list
    // return ys.

    int_list* ys = 0;

    for (int_list* curr = xs; curr; curr = curr->tail) {
        // insert xs->head into ys
        int_list* zs = insert(curr->head, ys);
        free_list(ys);
        ys = zs;
    }

    return ys;
}

int
add1(int x)
{
    return x + 1;
}

int_list*
map(int_list* xs, int (*fn)(int))
{
    if (xs) {
        return cons(
                fn(xs->head),
                map(xs->tail, fn));
    }
    else {
        return 0;
    }
}

int
main(int _ac, char* _argv[])
{
    int nn;
    
    puts("How many ints?");
    scanf("%d", &nn);

    puts("enter that many ints:");
    int_list* xs = read_ints(nn);

    int_list* ys = isort(xs);

    // map :: List Function -> List
    int_list* zs = map(ys, add1);

    puts("your input:");
    for (int_list* curr = xs; curr; curr = curr->tail) {
        printf("%d ", curr->head);
    }
    printf("\n");

    puts("sorted list");
    for (int_list* curr = ys; curr; curr = curr->tail) {
        printf("%d ", curr->head);
    }
    printf("\n");

    puts("inc list");
    for (int_list* curr = zs; curr; curr = curr->tail) {
        printf("%d ", curr->head);
    }
    printf("\n");


    free_list(xs);
    free_list(ys);
    return 0;
}



