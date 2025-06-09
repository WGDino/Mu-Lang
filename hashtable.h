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

unsigned long hash(const char *str);

void* get(const char* key);

//TODO key needs to be a string
//TODO value NodeExpr, NodeStmnt or NodeFunction
#endif