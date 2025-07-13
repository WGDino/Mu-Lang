#include "arena.h"

Arena arena_create(size_t cap){
    Arena a;
    a.ptr = malloc(cap);
    a.used = 0;
    a.capacity = cap;
    return a;
}

void *arena_alloc(Arena *a, size_t size){
    if(a->used + size > a->capacity){
        return NULL;
    }
    void *result = a->ptr + a->used;
    a->used += size;
    return result;
}

void arena_reset(Arena *a){
    a->used = 0;
}

void arena_free(Arena *a){
    free(a->ptr);
}