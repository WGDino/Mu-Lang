#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Node{
    struct Node *next;
    struct Node *previous;
    void *data;
} Node;

typedef struct linked_list{
    struct Node head;
} Linked_list;

Linked_list *create_list();

struct Node *add_node();

struct Node *get_last(Linked_list *lst);

struct Node *get_first(Linked_list *lst);

struct Node *list_insert(void *data, struct Node *pos);

struct Node *get_head(Linked_list *lst);

void print_list(Linked_list *lst);

#endif /* LINKED_LIST_H */