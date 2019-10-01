
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct goat {
    char* name;
    float mass; // kilos
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
fattest_goat(goat* goats, int nn)
{
    if (nn == 0) {
        abort();
    }

    goat max_goat = goats[0];
    for (int ii = 1; ii < nn; ++ii) {
        if (goats[ii].mass > max_goat.mass) {
            max_goat = goats[ii];
        }
    }
    return max_goat;
}

int
main(int _ac, char* _av[])
{
    goat herd[4];
    init_goat(&(herd[0]), "Alice", 50);
    init_goat(&(herd[1]), "Bob", 75);
    init_goat(&(herd[2]), "Carol", 60);
    init_goat(&(herd[3]), "Dave", 55);

    goat gg = fattest_goat(herd, 4);
    printf("The fattest goat is: %s\n", gg.name);

    for (int ii = 0; ii < 4; ++ii) {
        cleanup_goat(&(herd[ii]));
    }
    return 0;
}
