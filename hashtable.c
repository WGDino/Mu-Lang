#include "hashtable.h"

unsigned long hash(const char *str){
    unsigned long h = 5381;
    int c;
    while((c = *str++)) h = ((h << 5) + h) + c;
    return h;
}

Hashtable *create_hashtable(size_t size){
    Hashtable *table = malloc(sizeof(Hashtable));
    table->size = size;
    table->buckets = calloc(size, sizeof(Bucket));

    return table;
}

bool contains(Hashtable* table, const char* key) {
    unsigned long i = hash(key) % table->size;
    while (table->buckets[i].key) {
        if (strcmp(table->buckets[i].key, key) == 0) {
            return true;  
        }
        i = (i + 1) % table->size;
    }
    return false;  
}

void insert(Hashtable* table, const char* key, void* value) {
    unsigned long i = hash(key) % table->size;

    //If key already exists
    while (table->buckets[i].key != NULL) {
        if (strcmp(table->buckets[i].key, key) == 0) {
            table->buckets[i].value = value;
        }
        i = (i + 1) % table->size;
    }

    //if key does not exist
    table->buckets[i].key = strdup(key);
    table->buckets[i].value = value;
}

void *get(Hashtable* table, const char* key){
    unsigned long i = hash(key) % table->size;
    while(table->buckets[i].key && strcmp(table->buckets[i].key, key) != 0){
        i = (i + 1) % table->size;
    }

    return table->buckets[i].value;
}