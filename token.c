#include "token.h"

Token *token_create(void){
    Token *t = malloc(sizeof(Token));
    t->type = NULL;
    t->data = NULL;

    return t;
}

void update_token_type(Token *t, char *type, int length){
    t->type = calloc(length, sizeof(char));
    strcpy(t->type, type);
}

void update_token_data(Token *t, char *data, int length){
    t->data = calloc(length, sizeof(char));
    strcpy(t->data, data);
}

char *get_type(Token *t){
    return t->type;
}

char *get_data(Token *t){
    return t->data;
}