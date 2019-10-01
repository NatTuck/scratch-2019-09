
#include <stdio.h>

#include "map.h"

void
debug_print(map* mm)
{
    printf("map: size = %ld, capacity = %ld\n", mm->size, mm->capacity);
    for (long ii = 0; ii < mm->capacity; ++ii) {
        printf("slot = %ld\n", ii);
        for (pair* curr = mm->data[ii]; curr; curr = curr->next) {
            printf("  pair = {%s, %s, %lx}\n",
                   curr->key, curr->val, curr->next);
        }
    }
}

int
main(int _ac, char* _av[])
{
    map* noises = make_map();
    map_put(noises, "chicken", "bawk");
    map_put(noises, "cow", "meow");
    map_put(noises, "elephant", "yahoo");
    map_put(noises, "dog", "row");
    map_put(noises, "cat", "meow");

    debug_print(noises);

    printf("The cow says %s\n", map_get(noises, "cow"));
    map_del(noises, "cow");

    debug_print(noises);

    printf("Map size is: %ld\n", noises->size);
    for (map_it it = iterate(noises); it.item; it = next(it)) {
        printf("The %s says %s\n", it.item->key, it.item->val);
    }

    return 0;
}
