#include "hashtable.h"
#define TABLE_SIZE 1024 //TODO set this in the creation

unsigned long hash(const char *str){
    unsigned long h = 5381;
    int c;
    while((c = *str++)) h = ((h << 5) + h) + c;
    return h;
}

void *get(Hashtable* table, const char* key){
    unsigned long i = hash(key) % table->size;
    while(table->buckets[i].key && strcmp(table->buckets[i].key, key) != 0){
        i = (i + 1) % table->size;
    }

    return table->buckets[i].value;
}