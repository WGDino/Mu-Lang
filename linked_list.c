#include "linked_list.h"
#include <stdio.h>

Linked_list *create_list(){
    Linked_list *lst = malloc(sizeof(Linked_list));
    lst->head.next = &lst->head;
    lst->head.previous = &lst->head;
    return lst;
}

struct Node *add_node(void *data, char *type){
    struct Node *the_node = malloc(sizeof(struct Node));
    the_node->data = data;
    
    the_node->data_type = malloc(strlen(type) + 1);
    if (the_node->data_type != NULL) {
        strcpy(the_node->data_type, type);
    }
    
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

struct Node *list_insert(void *data, char *type, struct Node *pos){
    struct Node *node = add_node(data, type);
    
    struct Node *before = pos->previous;
    struct Node *after = pos;
    
    node->previous = before;
    before->next = node;

    node->next = after;
    after->previous = node;

    return node;
}

void list_remove(Linked_list *lst){
    struct Node *node = get_first(lst);

    while (node != get_head(lst))
    {
        struct Node *nextNode = node->next;
        remove_node(node);
        node = nextNode;
    }
    
    free(lst);
}

void remove_node(struct Node *node){
    Token *temp = node->data;
    if(temp->data != NULL){
        free(temp->data);
    }
    if(temp->type != NULL){
        free(temp->type);
    }
    
    free(node->data);
    free(node->data_type);
    free(node);
}

struct Node *get_head(Linked_list *lst){
    return &lst->head;
}

void print_list(Linked_list *lst, void (*print_func)(void *, char *)) {
    struct Node *node = get_first(lst);

    while (node != get_head(lst)) {
        print_func(node->data, node->data_type); // Call the user-provided print function
        node = node->next;
    }
}

void *peek(int offset, Linked_list *lst){
    struct Node *node = get_first(lst);

    if(offset == 0){
        return node->data;
    }

    else{
        struct Node *temp;
        for (int i = 0; i < offset; i++){
            temp = node->next;
            node = temp;
        }
        return temp->data;
    }
}

int peek_until(char *find, Linked_list *lst){//TODO this needs to be fixxed
    struct Node *node = get_first(lst);
    if(node == NULL) return -1;
    
    int count = 0;
    while (node != get_head(lst)){
        Token *token = (Token *)node->data;
        if(strcmp(token->data, find) == 0){
            return count;
        }
        node = node->next;
        count++;
    }
    
    return -2;
}

/*
    Returns: The consumed node from the list
*/
struct Node *consume(int offset, Linked_list *lst){
    struct Node *node = get_first(lst);
    
    struct Node *temp;
    for (int i = 0; i < offset; i++){
        temp = node->next;
        node = temp;
    }
    
    temp = node->previous;
    temp->next = node->next;
    node->next->previous = temp;

    return node;
}