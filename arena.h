#ifndef ARENA_H
#define ARENA_H
/*
    An arena in this context is a large chunk of memory which is allocated and then used to allocate from for the compiler

    @author Christoffer Eriksson
    @date 2026-01-06
    @version 0.1
*/

#include <stdlib.h>

typedef struct Arena{
    char *ptr;
    size_t used;
    size_t capacity;
}Arena;

/*
    Creates an arena object with size cap.

    @param cap Capacity of the arena in bytes
    @return The arena object
*/
Arena arena_create(size_t cap);

/*
    Allocates memory from the arena

    @param a The arena
    @param size Number of bytes being allocated.
    @return A pointer to the allocated memory
*/
void *arena_alloc(Arena *a, size_t size);

/*
    Resets the arena object.

    @param a The arena.
*/
void arena_reset(Arena *a);

/*
    Frees the arena.

    @param a The arena object.
*/
void arena_free(Arena *a);

#endif