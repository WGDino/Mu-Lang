#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct bucket{
    char* key;
    void* value;
} Bucket;

typedef struct hashtable{
    Bucket *buckets;
    size_t size;
}Hashtable;

Hashtable *create_hashtable(size_t size);

unsigned long hash(const char *str);

bool contains(Hashtable* table, const char* key);

void *get(Hashtable* table, const char* key);

void insert(Hashtable* table, const char* key, void* value);

//TODO key needs to be a string
//TODO value NodeExpr, NodeStmnt or NodeFunction
#endif