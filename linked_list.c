#include "linked_list.h"
#include <stdio.h>

Linked_list *create_list(){
    Linked_list *lst = malloc(sizeof(Linked_list));
    lst->head.next = &lst->head;
    lst->head.previous = &lst->head;
    return lst;
}

struct Node *add_node(Token *data){
    struct Node *the_node = malloc(sizeof(struct Node));
    the_node->data = malloc(sizeof(Token));
    the_node->data = data;
    
    return the_node;
}

struct Node *get_first(Linked_list *lst){
    return lst->head.next;
}

struct Node *get_last(Linked_list *lst){
    return lst->head.previous;
}

struct Node *next(struct Node *node){
    return node->next;
}

struct Node *list_insert(Token *data, struct Node *pos){
    struct Node *node = add_node(data);
    
    struct Node *before = pos->previous;
    struct Node *after = pos;
    
    node->previous = before;
    before->next = node;

    node->next = after;
    after->previous = node;

    return node;
}

void list_remove(Linked_list *lst){
    //TODO
}

struct Node *remove_node(struct Node *node){
    //TODO
}

struct Node *get_head(Linked_list *lst){
    return &lst->head;
}

void print_list(Linked_list *lst){
    struct Node *node = get_first(lst);
    
    while (node != get_head(lst)){
        printf("%s\n%s\n\n", get_data(node->data), get_type(node->data));
        node = node->next;
    }
}