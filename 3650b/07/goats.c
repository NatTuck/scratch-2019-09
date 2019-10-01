
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct goat {
    char* name;
    float mass; // kilos
} goat;

goat*
make_goat(char* name, float mass)
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
fattest_goat(goat** goats, int nn)
{
    if (nn == 0) {
        abort();
    }

    goat* max_goat = goats[0];
    for (int ii = 1; ii < nn; ++ii) {
        if (goats[ii]->mass > max_goat->mass) {
            max_goat = goats[ii];
        }
    }
    return max_goat;
}

int
main(int _ac, char* _av[])
{
    goat* herd[4];
    herd[0] = make_goat("Alice", 50);
    herd[1] = make_goat("Bob", 75);
    herd[2] = make_goat("Carol", 60);
    herd[3] = make_goat("Dave", 55);

    goat* gg = fattest_goat(herd, 4);
    printf("The fattest goat is: %s\n", gg->name);

    for (int ii = 0; ii < 4; ++ii) {
        free_goat(herd[ii]);
    }
    return 0;
}
