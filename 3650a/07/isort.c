
#include <stdio.h>
#include <stdlib.h>

// Empty list is just a null pointer.
typedef struct int_list {
    int head;
    struct int_list* tail;
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
    if (xs) {
        free_list(xs->tail);
        free(xs);
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
read_list(int nn)
{
    int_list* ys = 0;
    for (int ii = 0; ii < nn; ++ii) {
        int xx;
        scanf("%d", &xx);
        ys = cons(xx, ys);
    }

    int_list* tmp = reverse(ys);
    free_list(ys);
    return tmp;
}

void
insert(int_list* xs, int xx)
{
    for (int_list* curr = xs; curr; curr = curr->tail) {
        if (curr->tail && curr->tail->head > xx) {
            curr->tail = cons(xx, curr->tail);
        }
    }
}

int_list*
isort(int_list* xs)
{
    int_list* ys = 0;
    // for each element in xs
    // insert into ys in sorted positoin

    for (int_list* curr = xs; curr; curr = curr->tail) {
        insert(ys, curr->head);
    }

    return ys;
}

int
main(int _ac, char* _av)
{
    printf("How many ints?\n");

    int nn;
    scanf("%ld", &nn);

    printf("Enter that many ints.\n");

    int_list* xs = read_list(nn);

    int_list* ys = isort(xs);

    printf("Your list:\n");
    for (int_list* curr = xs; curr; curr = curr->tail) {
        printf("%d ", curr->head);
    }
    printf("\n");

    printf("Sorted list:\n");
    for (int_list* curr = ys; curr; curr = curr->tail) {
        printf("%d ", curr->head);
    }
    printf("\n");

    free_list(xs);
    free_list(ys);



    return 0;
}
