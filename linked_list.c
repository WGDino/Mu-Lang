#include "linked_list.h"

//TODO list_insert o List_remove

Linked_list *create_list(){
    Linked_list *lst = malloc(sizeof(Linked_list));
    lst->head->next = &lst->head;
    lst->head->previous = &lst->head;
    return lst;
}

struct Node *add_node(void *data){
    struct Node *the_node = calloc(1, sizeof(struct Node *));
    the_node->data = data;

    return the_node;
}

struct Node *get_first(Linked_list *lst){
    return lst->head->next;
}

struct Node *get_last(Linked_list *lst){
    return lst->head->previous;
}