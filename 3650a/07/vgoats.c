
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct goat {
    char* name;
    float mass;   // kilos
} goat;

void
init_goat(goat* gg, char* name, float mass)
{
    gg->name = strdup(name);
    gg->mass = mass;
}

void
cleanup_goat(goat* gg)
{
    free(gg->name);
}

goat
fattest_goat(goat* xs, int nn)
{
    goat winner = xs[0];

    for (int ii = 1; ii < nn; ++ii) {
        if (xs[ii].mass > winner.mass) {
            winner = xs[ii];
        }
    }

    return winner;
}

int
main(int argc, char* argv[])
{
    goat herd[4];
    init_goat(&(herd[0]), "Alice", 50);
    init_goat(&(herd[1]), "Bob", 75);
    init_goat(&(herd[2]), "Carol", 60);
    init_goat(&(herd[3]), "Dave", 55);

    goat ff = fattest_goat(herd, 4);
    printf("The fattest goat is %s\n", ff.name);

    for (int ii = 0; ii < 4; ++ii) {
        cleanup_goat(&(herd[ii]));
    }
}
