
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct goat {
    char* name;
    float mass;   // kilos
} goat;

goat*
make_goat(const char* name, float mass)
{
    goat* gg = malloc(sizeof(goat));
    gg->name = strdup(name);
    gg->mass = mass;
    return gg;
}

void
free_goat(goat* gg)
{
    free(gg->name);
    free(gg);
}

goat*
fattest_goat(goat** xs, int nn)
{
    goat* winner = xs[0];

    for (int ii = 1; ii < nn; ++ii) {
        if (xs[ii]->mass > winner->mass) {
            winner = xs[ii];
        }
    }

    return winner;
}

int
main(int argc, char* argv[])
{
    goat* herd[4];
    herd[0] = make_goat("Alice", 50);
    herd[1] = make_goat("Bob", 75);
    herd[2] = make_goat("Carol", 60);
    herd[3] = make_goat("Dave", 55);

    goat* ff = fattest_goat(herd, 4);
    printf("The fattest goat is %s\n", ff->name);

    for (int ii = 0; ii < 4; ++ii) {
        free_goat(herd[ii]);
    }
}
