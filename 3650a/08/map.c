
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "map.h"

map*
make_map()
{
    map* mm = malloc(sizeof(map));
    mm->size = 0;
    mm->capacity = 4;
    mm->data = calloc(mm->capacity, sizeof(pair*));
    return mm;
}

pair*
make_pair(const char* key, const char* val, pair* next)
{
    pair* pp = malloc(sizeof(pair));
    pp->key = strdup(key);
    pp->val = strdup(val);
    pp->next = next;
    return pp;
}

void
free_pair(pair* pp)
{
    if (pp) {
        free_pair(pp->next);
        free(pp->key);
        free(pp->val);
        free(pp);
    }
}

void
free_map(map* mm)
{
    for (long ii = 0; ii < mm->capacity; ++ii) {
        free_pair(mm->data[ii]);
    }
    free(mm->data);
    free(mm);
}

long
hash(const char* text, long nn)
{
    long hh = 0;
    for (long ii = 0; text[ii]; ++ii) {
        hh = hh * 67 + text[ii];
    }
    return hh & (nn - 1);
}

void
map_grow(map* mm)
{
    // do nothing
}

void
map_put(map* mm, const char* key, const char* val)
{
    if (mm->size >= mm->capacity) {
        map_grow(mm);
    }

    long ii = hash(key, mm->capacity);
    mm->data[ii] = make_pair(key, val, mm->data[ii]);
    mm->size += 1;
}

char*
map_get(map* mm, const char* key)
{
    long ii = hash(key, mm->capacity);
    for (pair* curr = mm->data[ii]; curr; curr = curr->next) {
        if (strcmp(curr->key, key) == 0) {
            return curr->val;
        }
    }
    return 0;
}

void
map_del(map* mm, const char* key)
{
    long ii = hash(key, mm->capacity);

    pair* curr = mm->data[ii];
    if (curr && strcmp(mm->data[ii]->key, key) == 0) {
        mm->data[ii] = curr->next;
        free_pair(curr);
        curr = 0;
    }

    for (; curr; curr = curr->next) {
        if (curr->next && strcmp(curr->next->key, key) == 0) {
            pair* dead = curr->next;
            curr->next = curr->next->next;
            free_pair(dead);
        }
    }
}

map_it
iterate(map* mm)
{
    map_it it;
    it.mm = mm;
    it.ii = 0;
    it.item = mm->data[0];
    if (it.item == 0) {
        it = next(it);
    }
    return it;
}

int
has_next(map_it it)
{
    it = next(it);
    return it.item != 0;
}

map_it
next(map_it it)
{
    if (it.item) {
        it.item = it.item->next;
    }

    while (it.item == 0) {
        it.ii += 1;
        if (it.ii < it.mm->capacity) {
            it.item = it.mm->data[it.ii];
        }
        else {
            it.item = 0;
            break;
        }
    }

    printf("ii = %ld, item* = %lx\n", it.ii, it.item);

    return it;
}
