#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"

struct Node{
    struct Node *next;
    struct Node *previous;
    Token *data;
};

typedef struct linked_list{
    struct Node head;
} Linked_list;

Linked_list *create_list();

struct Node *add_node();

struct Node *get_last(Linked_list *lst);

struct Node *get_first(Linked_list *lst);

struct Node *list_insert(Token *data, struct Node *pos);

struct Node *get_head(Linked_list *lst);

void print_list(Linked_list *lst);

void list_remove(Linked_list *lst);

struct Node *remove_node(struct Node *node);

#endif /* LINKED_LIST_H */