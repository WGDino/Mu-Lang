#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>

typedef struct Arena{
    char *ptr;
    size_t used;
    size_t capacity;
}Arena;

Arena arena_create(size_t cap);

void *arena_alloc(Arena *a, size_t size);

void arena_reset(Arena *a);

void arena_free(Arena *a);

#endif