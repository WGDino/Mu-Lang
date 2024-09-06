#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    struct Node *next;
    struct Node *previous;
    void *data;
} Node;

typedef struct linked_list{
    struct Node *head;
} Linked_list;

Linked_list *create_list();

struct Node *add_node();

#endif /* LINKED_LIST_H */