
#include <stdlib.h>
#include <string.h>

#include "map.h"

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

map*
make_map()
{
    map* mm = malloc(sizeof(map));
    mm->size = 0;
    mm->capacity = 4;
    mm->data = calloc(mm->capacity, sizeof(pair*));
    return mm;
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
    pair** data = mm->data;
    long   cap  = mm->capacity;

    mm->capacity *= 2;
    mm->data = calloc(mm->capacity, sizeof(pair*));
    mm->size = 0;

    for (long ii = 0; ii < cap; ++ii) {
        for (pair* curr = data[ii]; curr; curr = curr->next) {
            map_put(mm, curr->key, curr->val);
        }
        free_pair(data[ii]);
    }

    free(data);
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
alist_get(pair* pp, const char* key)
{
    if (pp) {
        if (strcmp(pp->key, key) == 0) {
            return pp->val;
        }
        else {
            return alist_get(pp->next, key);
        }
    }
    else {
        return 0;
    }
}

char*
map_get(map* mm, const char* key)
{
    long ii = hash(key, mm->capacity);
    return alist_get(mm->data[ii], key);
}

pair*
alist_del(pair* pp, const char* key, map* mm)
{
    if (!pp) {
        return 0;
    }

    if (strcmp(pp->key, key) == 0) {
        mm->size -= 1;
        pair* tmp = pp->next;
        pp->next = 0;
        free_pair(pp);
        return tmp;
    }
    else {
        pp->next = alist_del(pp->next, key, mm);
        return pp;
    }
}

void
map_del(map* mm, const char* key)
{
    long ii = hash(key, mm->capacity);
    mm->data[ii] = alist_del(mm->data[ii], key, mm);
}

map_it
iterate(map* mm)
{
    map_it it;
    it.mm = mm;
    it.ii = 0;
    it.item = mm->data[0];
    if (!it.item) {
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
    return it;
}

